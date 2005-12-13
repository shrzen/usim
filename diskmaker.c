/*
 * diskmaker.c
 *
 * make a disk image for the CADR simulator
 * reads template file or internal default disk partition
 *
 * NOTE:
 * Disk images are interpreted by the CADR as blocks of 32 bit values.
 * 32 bit values stored in disk images are kept in little endian
 * format.  usim will compensate when run on big endian machines.
 *
 * This program should be "byte order safe" and produce identical disk
 * images when run on big and little endian machines.
 *
 * $Id$
 */

#include "usim.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#if defined(LINUX) || defined(OSX)
#include <unistd.h>
#endif

#ifdef WIN32
typedef unsigned long off_t;
#endif

#ifdef __BIG_ENDIAN__
#define NEED_SWAP
#endif

char *template_filename;
char *img_filename;
int cyls, heads, blocks_per_track;
char *mcr_name;
char *lod_name;
char *brand;
char *text;
char *comment;

int debug;
int create;
int show;

unsigned int buffer[256];

#define MAX_PARTITIONS	16

struct part_s {
	char *name;
	int start;
	int size;
	int ptype;
	char *filename;

} parts[MAX_PARTITIONS];
int part_count;


void
_swaplongbytes(unsigned int *buf, int words)
{
	int i;
	unsigned char *p = (unsigned char *)buf;

	for (i = 0; i < words*4; i += 4) {
		unsigned char t, u, v;
		t = p[i];
		u = p[i+1];
		v = p[i+2];
		p[i] = p[i+3];
		p[i+1] = v;
		p[i+2] = u;
		p[i+3] = t;
	}
}

void
swapwords(unsigned int *buf)
{
	int i;
	unsigned short *p = (unsigned short *)buf;

	for (i = 0; i < 256*2; i += 2) {
		unsigned short t;
		t = p[i];
		p[i] = p[i+1];
		p[i+1] = t;
	}
}

int
add_partition(char *name, int start, int size, int ptype, char *filename)
{
	struct part_s *p = &parts[part_count++];
	if (part_count > MAX_PARTITIONS) {
		part_count--;
		return -1;
	}
	p->name = name;
	p->start = start;
	p->size = size;
	p->ptype = ptype;
	p->filename = filename;
	return 0;
}

unsigned long
str4(char *s)
{
	return (s[3]<<24) | (s[2]<<16) | (s[1]<<8) | s[0];
}

char *
unstr4(unsigned long s)
{
	static char b[5];
	b[3] = s >> 24;
	b[2] = s >> 16;
	b[1] = s >> 8;
	b[0] = s;
	b[4] = 0;
	return b;
}

int
make_labl(int fd)
{
	printf("making LABL...\n");

	memset((char *)buffer, 0, sizeof(buffer));

	buffer[0] = str4("LABL");	/* label LABL */
	buffer[1] = 1;			/* version = 1 */
	buffer[2] = cyls;		/* # cyls */
	buffer[3] = heads;		/* # heads */
	buffer[4] = blocks_per_track;	/* # blocks */
	buffer[5] = heads*blocks_per_track; /* heads*blocks */
	buffer[6] = str4(mcr_name);	/* name of micr part */
	buffer[7] = str4(lod_name);	/* name of load part */

	{
		int i;
		int p = 0200;
		
		printf("%d partitions\n", part_count);

		buffer[p++] = part_count; /* # of partitions */
		buffer[p++] = 7; /* words / partition */

		for (i = 0; i < part_count; i++) {
			unsigned long n;
			char *pn = parts[i].name;

			printf("%s, start %o, size %o\n",
			       pn, parts[i].start, parts[i].size);

			n = str4(pn);

			buffer[p++] = n;
			buffer[p++] = parts[i].start;
			buffer[p++] = parts[i].size;
			buffer[p++] = str4("    ");
			buffer[p++] = str4("    ");
			buffer[p++] = str4("    ");
			buffer[p++] = str4("    ");

		}
	}

//#define LABEL_PAD_CHAR '\200'
#define LABEL_PAD_CHAR '\0'
	/* pack brand text - offset 010, 32 bytes */
	memset((char *)&buffer[010], LABEL_PAD_CHAR, 32);

	/* pack text label - offset 020, 32 bytes */
	memset((char *)&buffer[020], ' ', 32);
	memcpy((char *)&buffer[020], text, strlen(text)+1);
	printf("text: '%s'\n", text);

	/* comment - offset 030, 32 bytes */
	memset((char *)&buffer[030], LABEL_PAD_CHAR, 32);
	strcpy((char *)&buffer[030], comment);
	printf("comment: '%s'\n", comment);

#ifdef NEED_SWAP
	/* don't swap the text */
	_swaplongbytes(&buffer[0], 8);
	_swaplongbytes(&buffer[0200], 128);
#endif

	write(fd, buffer, 256*4);
}

int
write_block(int fd, int block_no, unsigned char *buf)
{
	off_t offset, ret;
	int size;

	offset = block_no * (256*4);
	//printf("block_no %d (%x), offset %lld\n", block_no, block_no, offset);

	ret = lseek(fd, offset, SEEK_SET);
	//printf("lseek ret %lld\n", ret);

	if (ret != offset) {
		perror("lseek");
		return -1;
	}

	size = 256*4;
	ret = write(fd, buf, size);
	if (ret != size) {
		printf("disk write error; ret %d, size %d\n", ret, size);
		perror("write");
		return -1;
	}

	return 0;
}

int
make_one_partition(int fd, int index)
{
	int ret, count, i, fd1, offset;
	unsigned char b[256*4];

	printf("making %s... ", parts[index].name);

	count = 0;
	offset = parts[index].start;
	printf("offset %o, ", offset);
	fflush(stdout);

	if (parts[index].filename && parts[index].filename[0]) {
		fd1 = open(parts[index].filename, O_RDONLY);
		if (fd1 < 0) {
			perror(parts[index].filename);
			return -1;
		}


		printf("copy %s, ", parts[index].filename);
		fflush(stdout);
		
		while (1) {
			ret = read(fd1, b, 256*4);
			if (ret <= 0)
				break;

			if (memcmp(parts[index].name, "MCR", 3) == 0) {
				swapwords((unsigned int *)b);
			}

			if (write_block(fd, offset+count, b))
				break;
			count++;

			if (ret < 256*4)
				break;
		}

		close(fd1);
	} else {
		/* zero blocks */
		memset(b, 0, sizeof(b));

		printf("zero, ");
		fflush(stdout);

		for (count = 0; count < parts[index].size; count++) {
			if (write_block(fd, offset+count, b))
				break;
		}
	}

	printf("%d blocks\n", count);
	return 0;
}

void
make_partitions(int fd)
{
	int i;

	for (i = 0; i < part_count; i++) {
		make_one_partition(fd, i);
	}
}

/*
 * read template file, describing partitions
 */
int
parse_template(char *template)
{
	FILE *f;
	char line[256], what[256], str[256];
	int mode, start, size;

	f = fopen(template, "r");
	if (f == NULL) {
		return 0;
	}

	part_count = 0;

	while (fgets(line, sizeof(line), f)) {
		if (line[0]) {
			int l = strlen(line);
			line[l-1] = 0;
		}
		if (line[0] == '#') continue;

		if (strcmp(line, "output:") == 0) {
			mode = 1;
			continue;
		}
		if (strcmp(line, "label:") == 0) {
			mode = 2;
			continue;
		}
		if (strcmp(line, "partitions:") == 0) {
			mode = 3;
			continue;
		}

		if (0) printf("%d: %s\n", mode, line);

		switch(mode) {
		case 1:
			img_filename = strdup(line);
			break;
		case 2:
			sscanf(line, "%s\t%s", what, str);
			if (strcmp(what, "cyls") == 0)
				cyls = atoi(str);
			if (strcmp(what, "heads") == 0)
				heads = atoi(str);
			if (strcmp(what, "blockspertrack") == 0)
				blocks_per_track = atoi(str);
			if (strcmp(what, "mcr") == 0)
				mcr_name = strdup(str);
			if (strcmp(what, "lod") == 0)
				lod_name = strdup(str);
			if (strcmp(what, "brand") == 0)
				;
			if (strcmp(what, "text") == 0)
				;
			if (strcmp(what, "comment") == 0)
				;
			break;
		case 3:
			start = size = 0;
			what[0] = str[0] = 0;
			sscanf(line, "%s\t%o\t%o\t%s",
			       what, &start, &size, str);
			if (what[0] && start > 0 && size > 0) {
				add_partition(strdup(what), start, size,
					      0, strdup(str));
			}
			break;
		}
	}

	fclose(f);
	return 0;
}

int
fillout_image_file(int fd)
{
	int i, last_block_no, ret;
	off_t offset;

	/* find the highest block # + 1 */
	last_block_no = 0;
	for (i = 0; i < part_count; i++) {
		int last = parts[i].start + parts[i].size;
		if (last > last_block_no)
			last_block_no = last;
	}

	offset = (last_block_no + 1) * (256*4);
	if (0) printf("last block %d (0%o), expanding file to %lld\n",
		      last_block_no, last_block_no, offset-1);

	ret = ftruncate(fd, offset-1);
	if (0) printf("ret %d\n", ret);

	if (ret) {
		perror("ftruncate");
		return -1;
	}

#if 0
	{
		unsigned char b[256*4];

		/* zero blocks */
		memset(b, 0, sizeof(b));
		for (i = 0; i < 1000; i++) {
			if (write(fd, b, 1024))
				break;
		}
	}
#endif

	lseek(fd, (off_t)0, SEEK_SET);

	return 0;
}

int
create_disk(char *template, char *image)
{
	int fd;

	if (parse_template(template))
		return -1;

	fd = open(image, O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		perror(image);
		return -1;
	}

//#ifdef __APPLE__
//	fillout_image_file(fd);
//#endif

	make_labl(fd);
	make_partitions(fd);

	close(fd);

	return 0;
}


void
default_template(void)
{
	if (img_filename == NULL)
		img_filename = strdup("disk.img");

	/* try to look like a Trident T-300 */
	cyls = 815;
	heads = 19;
	blocks_per_track = 17;

#define DEFAULT_MCR_FILE	"ucadr.mcr.841"
#define DEFAULT_LOD_FILE	"partition-78.48.lod1"

	part_count = 0;
	add_partition("MCR1", 021,	0224,	0, DEFAULT_MCR_FILE);
	add_partition("MCR2", 0245,	0224,	0, NULL);
	add_partition("PAGE", 0524,	0100000,0, NULL);
	add_partition("LOD1", 0100524,  061400,	0, DEFAULT_LOD_FILE);
	add_partition("LOD2", 0162124,  061400,	0, NULL);
	add_partition("FILE", 0243524,  070000,	0, NULL);

	mcr_name = "MCR1";
	lod_name = "LOD1";

	brand = NULL;
	text = "CADR diskmaker image";
	comment = DEFAULT_MCR_FILE;
}

/*
 * read disk image and dump info
 */
int
show_partition_info(char *filename)
{
	int fd, ret, p, i;
	int count, size;

	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0) {
		perror(filename);
		return -1;
	}

	ret = read(fd, buffer, 256*4);
	if (ret != 256*4) {
		perror(filename);
		return -1;
	}

#ifdef NEED_SWAP
	/* don't swap the text */
	_swaplongbytes(&buffer[0], 8);
	_swaplongbytes(&buffer[0200], 128);
#endif

	if (buffer[0] != str4("LABL")) {
		fprintf(stderr, "%s: no valid disk label found\n", filename);
		return -1;
	}

	if (buffer[1] != 1) {
		fprintf(stderr, "%s: label version not 1\n", filename);
		return -1;
	}

	cyls = buffer[2];		/* # cyls */
	heads = buffer[3];		/* # heads */
	blocks_per_track = buffer[4];	/* # blocks */
	mcr_name = strdup(unstr4(buffer[6]));	/* name of micr part */
	lod_name = strdup(unstr4(buffer[7]));	/* name of load part */

	count = buffer[0200];
	size = buffer[0201];
	p = 0202;

	part_count = 0;
	for (i = 0; i < count; i++) {
		add_partition(strdup(unstr4(buffer[p+0])),
			      buffer[p+1], buffer[p+2], 0, NULL);
		
		p += size;
	}

	brand = strdup((char *)&buffer[010]);
	text = strdup((char *)&buffer[020]);
	comment = strdup((char *)&buffer[030]);

	printf("#\n");
	printf("output:\n");
	printf("%s:\n", filename);

	printf("#\n");
	printf("label:\n");
	printf("cyls\t%d\n", cyls);
	printf("heads\t%d\n", heads);
	printf("blockspertrack\t%d\n", blocks_per_track);

	if (brand[0] && (brand[0] & 0xff) != 0200) printf("brand\t%s\n", brand);
	if (text[0]) printf("text\t%s\n", text);
	if (comment[0]) printf("comment\t%s\n", comment);

	printf("mcr\t%s\n", mcr_name);
	printf("lod\t%s\n", lod_name);

	printf("#\n");
	printf("partitions:\n");

	for (i = 0; i < part_count; i++) {
		printf("%s\t0%o\t0%o\t%s\n",
		       parts[i].name,
		       parts[i].start, parts[i].size,
		       parts[i].filename ? parts[i].filename : "");
	}

	close(fd);
	return 0;
}

void
usage(void)
{
	fprintf(stderr, "CADR diskmaker\n");
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "-p	show existing disk image\n");
	fprintf(stderr, "-c	create new disk image\n");
	fprintf(stderr, "-t <template-filename>\n");
	fprintf(stderr, "-f <disk-image-filename>\n");

	exit(1);
}

extern char *optarg;

main(int argc, char *argv[])
{
	int c, fd;

	if (argc <= 1)
		usage();

	while ((c = getopt(argc, argv, "cdt:f:p")) != -1) {
		switch (c) {
		case 'c':
			create++;
			break;
		case 'd':
			debug++;
			break;
		case 'f':
			img_filename = strdup(optarg);
			break;
		case 'p':
			show++;
			break;
		case 't':
			template_filename = strdup(optarg);
			break;
		default:
			usage();
		}
	}

	default_template();

	if (show) {
		show_partition_info(img_filename);
		exit(0);
	}

	if (create) {
		create_disk(template_filename, img_filename);
		exit(0);
	}

	exit(0);
}
