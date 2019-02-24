// misc.c --- ---!!!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "misc.h"

static char
tohex(char b)
{
	b = b & 0xf;
	if (b < 10)
		return '0' + b;
	return 'a' + (b - 10);
}

void
dumpmem(char *ptr, int len)
{
	char line[80];
	char chars[80];
	char *p;
	char b;
	char *c;
	char *end;
	int j;
	int offset;

	end = ptr + len;
	offset = 0;
	while (ptr < end) {
		p = line;
		c = chars;
		printf("%04x ", offset);
		*p++ = ' ';
		for (j = 0; j < 16; j++) {
			if (ptr < end) {
				b = *ptr++;
				*p++ = tohex(b >> 4);
				*p++ = tohex(b);
				*p++ = ' ';
				*c++ = ' ' <= b && b <= '~' ? b : '.';
			} else {
				*p++ = 'x';
				*p++ = 'x';
				*p++ = ' ';
				*c++ = 'x';
			}
		}
		*p = 0;
		*c = 0;
		printf("%s %s\n", line, chars);
		offset += 16;
	}
}

uint32_t
read16(int fd)
{
	unsigned char b[2];
	int ret;

	ret = read(fd, b, 2);
	if (ret != 2) {
		fprintf(stderr, "read error; ret %d, size %d\n", (int) ret, 2);
		exit(1);
	}
	return (b[1] << 8) | b[0];
}

uint32_t
read32(int fd)
{
	unsigned char b[4];
	int ret;

	ret = read(fd, b, 4);
	if (ret != 4) {
		fprintf(stderr, "read error; ret %d, size %d\n", (int) ret, 4);
		exit(1);
	}
	return (b[1] << 24) | (b[0] << 16) | (b[3] << 8) | b[2];
}

unsigned long
str4(char *s)
{
	return (s[3] << 24) | (s[2] << 16) | (s[1] << 8) | s[0];
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
read_block(int fd, int block_no, unsigned char *buf)
{
	off_t offset;
	off_t ret;
	int size;

	offset = block_no * BLOCKSZ;
	ret = lseek(fd, offset, SEEK_SET);
	if (ret != offset) {
		perror("lseek");
		return -1;
	}

	size = BLOCKSZ;
	ret = read(fd, buf, size);
	if (ret != size) {
		fprintf(stderr, "disk read error; ret %d, size %d\n", (int) ret, size);
		perror("read");
		return -1;
	}

	return 0;
}

int
write_block(int fd, int block_no, unsigned char *buf)
{
	off_t offset;
	off_t ret;
	int size;

	offset = block_no * BLOCKSZ;
	ret = lseek(fd, offset, SEEK_SET);
	if (ret != offset) {
		perror("lseek");
		return -1;
	}

	size = BLOCKSZ;
	ret = write(fd, buf, size);
	if (ret != size) {
		fprintf(stderr, "disk write error; ret %d, size %d\n", (int) ret, size);
		perror("write");
		return -1;
	}

	return 0;
}
