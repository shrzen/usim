#ifndef USIM_DEFMIC_H
#define USIM_DEFMIC_H

// See SYS;COLD:DEFMIC LISP for the canonical definition.

char *op_names[16] = {
	"CALL",
	"CALL0",
	"MOVE",
	"CAR",
	"CDR",
	"CADR",
	"CDDR",
	"CDAR",
	"CAAR",
	"ND1",
	"ND2",
	"ND3",
	"BRANCH",
	"MISC",
	"ND4 ",
	"17 UNUSED"
	"AREFI",
};

char *reg_names[] = {
	"FEF",
	"FEF+100",
	"FEF+200",
	"FEF+300",
	"CONSTANTS PAGE",
	"LOCAL",
	"ARG POINTER",
	"PDL"
};

char *dest_names[] = {
	"D-IGNORE",
	"D-PDL",
	"D-NEXT",
	"D-LAST",
	"D-RETURN",
	"D-NEXT-Q",
	"D-LAST-Q",
	"D-NEXT-LIST",
	"D-MICRO, POPJ",
	"illegal",
	"illegal",
	"illegal",
	"illegal",
	"illegal",
	"illegal",
	"illegal"
};

char *branch_names[] = {
	"BR",
	"BR-NIL",
	"BR-NOT-NIL",
	"BR-NIL-POP",
	"BR-NOT-NIL-POP",
	"BR-ATOM",
	"BR-NOT-ATOM",
	"BR-ILL-7"
};

char *nd1_names[] = {
	"ND1-UNUSED",
	"+",
	"-",
	"*",
	"/",
	"LOGAND",
	"LOGXOR",
	"LOGIOR"
};

char *nd2_names[] = {
	"=",
	">",
	"<",
	"EQ",
	"SETE-CDR",
	"SETE-CDDR",
	"SETE-1+",
	"SETE-1-"
};

char *nd3_names[] = {
	"BIND-OBSOLETE?",
	"BIND-NIL",
	"BIND-POP",
	"SET-NIL",
	"SET-ZERO",
	"PUSH-E",
	"MOVEM",
	"POP"
};

char *nd4_names[] = {
	"STACK-CLOSURE-DISCONNECT",
	"STACK-CLOSURE-UNSHARE",
	"MAKE-STACK-CLOSURE",
	"PUSH-NUMBER",
	"STACK-CLOSURE-DISCONNECT-FIRST",
	"PUSH-CDR-IF-CAR-EQUAL",
	"PUSH-CDR-STORE-CAR-IF-CONS"
};

char *arefi_names[] = {
	"AR-1",
	"ARRAY-LEADER",
	"%%INSTANCE-REF",
	"COMMON-LISP-AR-1",
	"SET-AR-1",
	"SET-ARRAY-LEADER",
	"SET-%%INSTANCE-REF",
	"UNUSED-AREFI"
};

struct {
	char *name;
	int value;
} misc_inst[] = {
	{ "", 0 },
	//240 241 FREE
	{ "(CAR . M-CAR)", 0242 },
	{ "(CDR . M-CDR)", 0243 },
	{ "(CAAR . M-CAAR)", 0244 },
	{ "(CADR . M-CADR)", 0245 },
	{ "(CDAR . M-CDAR)", 0246 },
	{ "(CDDR . M-CDDR)", 0247 },
	{ "CAAAR", 0250 },
	{ "CAADR", 0251 },
	{ "CADAR", 0252 },
	{ "CADDR", 0253 },
	{ "CDAAR", 0254 },
	{ "CDADR", 0255 },
	{ "CDDAR", 0256 },
	{ "CDDDR", 0257 },
	{ "CAAAAR", 0260 },
	{ "CAAADR", 0261 },
	{ "CAADAR", 0262 },
	{ "CAADDR", 0263 },
	{ "CADAAR", 0264 },
	{ "CADADR", 0265 },
	{ "CADDAR", 0266 },
	{ "CADDDR", 0267 },
	{ "CDAAAR", 0270 },
	{ "CDAADR", 0271 },
	{ "CDADAR", 0272 },
	{ "CDADDR", 0273 },
	{ "CDDAAR", 0274 },
	{ "CDDADR", 0275 },
	{ "CDDDAR", 0276 },
	{ "CDDDDR", 0277 },

	{ "%LOAD-FROM-HIGHER-CONTEXT", 0300 },
	{ "%LOCATE-IN-HIGHER-CONTEXT", 0301 },
	{ "%STORE-IN-HIGHER-CONTEXT", 0302 },
	{ "%DATA-TYPE", 0303 },
	{ "%POINTER", 0304 },
	{ "%MAKE-REST-ARG-SAFE", 0305 },
	{ "%PERMIT-TAIL-RECURSION", 0306 },
	{ "INTERNAL-FLOAT", 0307 },
	{ "%MAKE-POINTER", 0310 },
	{ "%SPREAD", 0311 },
	{ "%P-STORE-CONTENTS", 0312 },
	{ "%LOGLDB", 0313 },
	{ "%LOGDPB", 0314 },
	{ "LDB", 0315 },
	{ "DPB", 0316 },
	{ "%P-STORE-TAG-AND-POINTER", 0317 },

	{ "INTERNAL-GET-2", 0320 },
	{ "GETL", 0321 },
	{ "ASSQ", 0322 },
	{ "LAST", 0323 },
	{ "LENGTH", 0324 },
	{ "1+", 0325 },
	{ "1-", 0326 },
	{ "RPLACA", 0327 },
	{ "RPLACD", 0330 },
	{ "ZEROP", 0331 },
	{ "SET", 0332 },
	{ "(FIXP . INTEGERP)", 0333 },
	{ "FLOATP", 0334 },
	{ "EQUAL", 0335 },
	{ "%SET-SELF-MAPPING-TABLE", 0336 },
	{ "PDL-WORD", 0337 },
	{ "FALSE", 0340 },
	{ "TRUE", 0341 },
	{ "NOT", 0342 },
	{ "(NULL . NOT)", 0342 },
	{ "ATOM", 0343 },
	{ "ODDP", 0344 },
	{ "EVENP", 0345 },
	{ "%HALT", 0346 },
	{ "(SYMBOL-NAME . GET-PNAME)", 0347 },
	{ "LSH", 0350 },
	{ "ROT", 0351 },
	{ "*BOOLE", 0352 },
	{ "NUMBERP", 0353 },
	{ "PLUSP", 0354 },
	{ "MINUSP", 0355 },
	{ "\\", 0356 },
	{ "MINUS", 0357 },
	{ "%SXHASH-STRING", 0360 },
	{ "VALUE-CELL-LOCATION", 0361 },
	{ "FUNCTION-CELL-LOCATION", 0362 },
	{ "PROPERTY-CELL-LOCATION", 0363 },
	{ "NCONS", 0364 },
	{ "NCONS-IN-AREA", 0365 },
	{ "CONS", 0366 },
	{ "CONS-IN-AREA", 0367 },
	{ "XCONS", 0370 },
	{ "XCONS-IN-AREA", 0371 },
	{ "%SPREAD-N", 0372 },
	{ "(SYMBOL-VALUE . SYMEVAL)", 0373 },
	{ "POP-M-FROM-UNDER-N", 0374 },
	{ "GET-LEXICAL-VALUE-CELL", 0375 },
	{ "%CALL-MULT-VALUE", 0376 },
	{ "%CALL0-MULT-VALUE", 0377 },
	{ "%RETURN-2", 0400 },
	{ "%RETURN-3", 0401 },
	{ "%RETURN-N", 0402 },
	{ "RETURN-NEXT-VALUE", 0403 },
	{ "RETURN-LIST", 0404 },
	{ "UNBIND-TO-INDEX-UNDER-N", 0405 },
	{ "(BIND . %BIND)", 0406 },
	// 407 unused
	{ "MEMQ", 0410 },
	{ "(INTERNAL-< . M-<)", 0411 },
	{ "(INTERNAL-> . M->)", 0412 },
	{ "(INTERNAL-= . M-=)", 0413 },
	{ "INTERNAL-CHAR-EQUAL", 0414 },
	{ "%STRING-SEARCH-CHAR", 0415 },
	{ "%STRING-EQUAL", 0416 },
	{ "NTH", 0417 },
	{ "NTHCDR", 0420 },
	{ "(*PLUS . M-+)", 0421 },
	{ "(*DIF . M--)", 0422 },
	{ "(*TIMES . M-*)", 0423 },
	{ "(*QUO . M-//)", 0424 },
	{ "(*LOGAND . M-LOGAND)", 0425 },
	{ "(*LOGXOR . M-LOGXOR)", 0426 },
	{ "(*LOGIOR . M-LOGIOR)", 0427 },
	{ "ARRAY-LEADER", 0430 },
	{ "STORE-ARRAY-LEADER", 0431 },
	{ "GET-LIST-POINTER-INTO-ARRAY", 0432 },
	{ "ARRAY-PUSH", 0433 },
	{ "INTERNAL-APPLY", 0434 },
	{ "%MAKE-LIST", 0435 },
	{ "LIST", 0436 },
	{ "LIST*", 0437 },
	{ "LIST-IN-AREA", 0440 },
	{ "LIST*-IN-AREA", 0441 },
	{ "LOCATE-IN-INSTANCE", 0442 },
	{ "%P-CDR-CODE", 0443 },
	{ "%P-DATA-TYPE", 0444 },
	{ "%P-POINTER", 0445 },
	{ "%PAGE-TRACE", 0446 },
	{ "THROW-N", 0447 },
	{ "%P-STORE-CDR-CODE", 0450 },
	{ "%P-STORE-DATA-TYPE", 0451 },
	{ "%P-STORE-POINTER", 0452 },
	{ "FLOAT-EXPONENT", 0453 },
	{ "FLOAT-FRACTION", 0454 },
	{ "SCALE-FLOAT", 0455 },
	{ "%CATCH-OPEN", 0456 },
	{ "%CATCH-OPEN-MV", 0457 },
	{ "INTERNAL-FLOOR-1", 0460 },

	{ "%DIV", 0461 },
	{ "%FEXPR-CALL", 0462 },
	{ "%FEXPR-CALL-MV", 0463 },
	{ "%FEXPR-CALL-MV-LIST", 0464 },
	{ "%CATCH-OPEN-MV-LIST", 0465 },
	{ "(CATCH . *CATCH)", 0466 },
	{ "%BLT", 0467 },
	{ "(THROW . *THROW)", 0470 },
	{ "%XBUS-WRITE-SYNC", 0471 },
	{ "%P-LDB", 0472 },
	{ "%P-DPB", 0473 },
	{ "MASK-FIELD", 0474 },
	{ "%P-MASK-FIELD", 0475 },
	{ "DEPOSIT-FIELD", 0476 },
	{ "%P-DEPOSIT-FIELD", 0477 },
	{ "COPY-ARRAY-CONTENTS", 0500 },
	{ "COPY-ARRAY-CONTENTS-AND-LEADER", 0501 },
	{ "%FUNCTION-INSIDE-SELF", 0502 },
	{ "ARRAY-HAS-LEADER-P", 0503 },
	{ "COPY-ARRAY-PORTION", 0504 },
	{ "FIND-POSITION-IN-LIST", 0505 },
	{ "%GET-SELF-MAPPING-TABLE", 0506 },
	{ "G-L-P", 0507 },
	{ "INTERNAL-FLOOR-2", 0510 },
	{ "EQL", 0511 },
	{ "AR-1", 0512 },
	{ "AR-2", 0513 },
	{ "AR-3", 0514 },
	{ "AS-1", 0515 },
	{ "AS-2", 0516 },
	{ "AS-3", 0517 },
	{ "%INSTANCE-REF", 0520 },
	{ "%INSTANCE-LOC", 0521 },
	{ "%INSTANCE-SET", 0522 },
	{ "%BINDING-INSTANCES", 0523 },
	{ "%EXTERNAL-VALUE-CELL", 0524 },
	{ "%USING-BINDING-INSTANCES", 0525 },
	{ "%GC-CONS-WORK", 0526 },
	{ "%P-CONTENTS-OFFSET", 0527 },
	{ "%DISK-RESTORE", 0530 },
	{ "%DISK-SAVE", 0531 },
	{ "%ARGS-INFO", 0532 },
	{ "%OPEN-CALL-BLOCK", 0533 },
	{ "%PUSH", 0534 },
	{ "%ACTIVATE-OPEN-CALL-BLOCK", 0535 },
	{ "%ASSURE-PDL-ROOM", 0536 },
	{ "STACK-GROUP-RETURN", 0537 },
	{ "AS-2-REVERSE", 0540 },
	{ "%MAKE-STACK-LIST", 0541 },
	{ "STACK-GROUP-RESUME", 0542 },
	{ "%CALL-MULT-VALUE-LIST", 0543 },
	{ "%CALL0-MULT-VALUE-LIST", 0544 },
	{ "%GC-SCAV-RESET", 0545 },
	{ "%P-STORE-CONTENTS-OFFSET", 0546 },
	{ "%GC-FREE-REGION", 0547 },
	{ "%GC-FLIP", 0550 },
	{ "ARRAY-LENGTH", 0551 },
	{ "ARRAY-TOTAL-SIZE", 0551 },
	{ "ARRAY-ACTIVE-LENGTH", 0552 },
	{ "%COMPUTE-PAGE-HASH", 0553 },
	{ "THROW-SPREAD", 0554 },
	{ "%UNIBUS-READ", 0555 },
	{ "%UNIBUS-WRITE", 0556 },
	{ "%GC-SCAVENGE", 0557 },
	{ "%CHAOS-WAKEUP", 0560 },
	{ "%AREA-NUMBER", 0561 },
	{ "*MAX", 0562 },
	{ "*MIN", 0563 },
	{ "CLOSURE", 0565 },
	{ "AR-2-REVERSE", 0566 },
	{ "LISTP", 0567 },
	{ "NLISTP", 0570 },
	{ "SYMBOLP", 0571 },
	{ "NSYMBOLP", 0572 },
	{ "ARRAYP", 0573 },
	{ "FBOUNDP", 0574 },
	{ "STRINGP", 0575 },
	{ "BOUNDP", 0576 },
	{ "INTERNAL-\\", 0577 },
	{ "(SYMBOL-FUNCTION . FSYMEVAL)", 0600 },
	{ "AP-1", 0601 },
	{ "AP-2", 0602 },
	{ "AP-3", 0603 },
	{ "AP-LEADER", 0604 },
	{ "%P-LDB-OFFSET", 0605 },
	{ "%P-DPB-OFFSET", 0606 },
	{ "%P-MASK-FIELD-OFFSET", 0607 },
	{ "%P-DEPOSIT-FIELD-OFFSET", 0610 },
	{ "%MULTIPLY-FRACTIONS", 0611 },
	{ "%DIVIDE-DOUBLE", 0612 },
	{ "%REMAINDER-DOUBLE", 0613 },
	{ "HAULONG", 0614 },
	{ "%ALLOCATE-AND-INITIALIZE", 0615 },
	{ "%ALLOCATE-AND-INITIALIZE-ARRAY", 0616 },
	{ "%MAKE-POINTER-OFFSET", 0617 },
	{ "^", 0620 },
	{ "%CHANGE-PAGE-STATUS", 0621 },
	{ "%CREATE-PHYSICAL-PAGE", 0622 },
	{ "%DELETE-PHYSICAL-PAGE", 0623 },
	{ "%24-BIT-PLUS", 0624 },
	{ "%24-BIT-DIFFERENCE", 0625 },
	{ "%24-BIT-TIMES", 0626 },
	{ "ABS", 0627 },
	{ "%POINTER-DIFFERENCE", 0630 },
	{ "%P-CONTENTS-AS-LOCATIVE", 0631 },
	{ "%P-CONTENTS-AS-LOCATIVE-OFFSET", 0632 },
	{ "(EQ . M-EQ)", 0633 },
	{ "%STORE-CONDITIONAL", 0634 },
	{ "%STACK-FRAME-POINTER", 0635 },
	{ "*UNWIND-STACK", 0636 },
	{ "%XBUS-READ", 0637 },
	{ "%XBUS-WRITE", 0640 },
	{ "ELT", 0641 },
	{ "MOVE-PDL-TOP", 0642 },
	{ "SHRINK-PDL-SAVE-TOP", 0643 },
	{ "SPECIAL-PDL-INDEX", 0644 },
	{ "UNBIND-TO-INDEX", 0645 },
	{ "UNBIND-TO-INDEX-MOVE", 0646 },
	{ "FIX", 0647 },
	{ "FLOAT", 0650 },
	{ "SMALL-FLOAT", 0651 },
	{ "%FLOAT-DOUBLE", 0652 },
	{ "BIGNUM-TO-ARRAY", 0653 },
	{ "ARRAY-TO-BIGNUM", 0654 },
	{ "%UNWIND-PROTECT-CONTINUE", 0655 },
	{ "%WRITE-INTERNAL-PROCESSOR-MEMORIES", 0656 },
	{ "%PAGE-STATUS", 0657 },
	{ "%REGION-NUMBER", 0660 },
	{ "%FIND-STRUCTURE-HEADER", 0661 },
	{ "%STRUCTURE-BOXED-SIZE", 0662 },
	{ "%STRUCTURE-TOTAL-SIZE", 0663 },
	{ "%MAKE-REGION", 0664 },
	{ "BITBLT", 0665 },
	{ "%DISK-OP", 0666 },
	{ "%PHYSICAL-ADDRESS", 0667 },
	{ "POP-OPEN-CALL", 0670 },
	{ "%BEEP", 0671 },
	{ "%FIND-STRUCTURE-LEADER", 0672 },
	{ "BPT", 0673 },
	{ "%FINDCORE", 0674 },
	{ "%PAGE-IN", 0675 },
	{ "ASH", 0676 },
	{ "%MAKE-EXPLICIT-STACK-LIST", 0677 },
	{ "%DRAW-CHAR", 0700 },
	{ "%DRAW-RECTANGLE", 0701 },
	{ "%DRAW-LINE", 0702 },
	{ "%DRAW-TRIANGLE", 0703 },
	{ "%COLOR-TRANSFORM", 0704 },
	{ "%RECORD-EVENT", 0705 },
	{ "%AOS-TRIANGLE", 0706 },
	{ "%SET-MOUSE-SCREEN", 0707 },
	{ "%OPEN-MOUSE-CURSOR", 0710 },
	{ "SETELT", 0711 },
	{ "%BLT-TYPED", 0712 },
	{ "AR-1-FORCE", 0714 },
	{ "AS-1-FORCE", 0715 },
	{ "AP-1-FORCE", 0716 },
	{ "AREF", 0717 },
	{ "ASET", 0720 },
	{ "ALOC", 0721 },

	{ "EQUALP", 0722 },
	{ "%MAKE-EXPLICIT-STACK-LIST*", 0723 },
	{ "SETCAR", 0724 },
	{ "SETCDR", 0725 },
	{ "GET-LOCATION-OR-NIL", 0726 },
	{ "%STRING-WIDTH", 0727 },
	{ "AR-1-CACHED-1", 0730 },
	{ "AR-1-CACHED-2", 0731 },

	{ "%MULTIBUS-READ-16", 0732 },
	{ "%MULTIBUS-WRITE-16", 0733 },
	{ "%MULTIBUS-READ-8", 0734 },
	{ "%MULTIBUS-WRITE-8", 0735 },
	{ "%MULTIBUS-READ-32", 0736 },
	{ "%MULTIBUS-WRITE-32", 0737 },

	{ "SET-AR-1", 0740 },
	{ "SET-AR-2", 0741 },
	{ "SET-AR-3", 0742 },
	{ "SET-AR-1-FORCE", 0743 },
	{ "SET-AREF", 0744 },
	{ "SET-ARRAY-LEADER", 0745 },
	{ "SET-%INSTANCE-REF", 0746 },
	{ "VECTOR-PUSH", 0747 },
	{ "ARRAY-HAS-FILL-POINTER-P", 0750 },
	{ "ARRAY-LEADER-LENGTH", 0751 },
	{ "ARRAY-RANK", 0752 },
	{ "ARRAY-DIMENSION", 0753 },
	{ "ARRAY-IN-BOUNDS-P", 0754 },
	{ "ARRAY-ROW-MAJOR-INDEX", 0755 },

	{ "RETURN-N-KEEP-CONTROL", 0756 },
	{ "RETURN-SPREAD-KEEP-CONTROL", 0757 },
	{ "COMMON-LISP-LISTP", 0760 },

	{ "%NUBUS-READ", 0761 },
	{ "%NUBUS-WRITE", 0762 },
	{ "%MICROSECOND-TIME", 0763 },
	{ "%FIXNUM-MICROSECOND-TIME", 0764 },
	{ "%IO-SPACE-READ", 0765 },
	{ "%IO-SPACE-WRITE", 0766 },
	{ "%NUBUS-PHYSICAL-ADDRESS", 0767 },

	{ "VECTORP", 0770 },
	{ "SIMPLE-VECTOR-P", 0771 },
	{ "SIMPLE-ARRAY-P", 0772 },
	{ "SIMPLE-STRING-P", 0773 },
	{ "BIT-VECTOR-P", 0774 },
	{ "SIMPLE-BIT-VECTOR-P", 0775 },
	{ "NAMED-STRUCTURE-P", 0776 },
	{ "NAMED-STRUCTURE-SYMBOL", 0776 },
	{ "TYPEP-STRUCTURE-OR-FLAVOR", 0777 },
	{ "FIXNUMP", 01000 },
	{ "SMALL-FLOATP", 01001 },
	{ "CHARACTERP", 01002 },

	{ "CAR-SAFE", 01003 },
	{ "CDR-SAFE", 01004 },
	{ "CADR-SAFE", 01005 },
	{ "CDDR-SAFE", 01006 },
	{ "CDDDDR-SAFE", 01007 },
	{ "NTHCDR-SAFE", 01010 },
	{ "NTH-SAFE", 01011 },
	{ "CARCDR", 01012 },
	{ "ENDP", 01013 },
	{ "CONSP-OR-POP", 01014 },
	{ "INDICATORS-VALUE", 01015 },
	{ "%POINTER-TIMES", 01016 },
	{ "COMMON-LISP-AREF", 01017 },
	{ "COMMON-LISP-AR-1", 01020 },
	{ "COMMON-LISP-AR-1-FORCE", 01021 },
	{ "INTERNAL-GET-3", 01022 },

	{ "CHAR-INT", 01023 },
	{ "INT-CHAR", 01024 },
	{ "ALPHA-CHAR-P", 01025 },
	{ "UPPER-CASE-P", 01026 },
	{ "ALPHANUMERICP", 01027 },
	{ "PACKAGE-CELL-LOCATION", 01030 },
	{ "MEMBER-EQL", 01031 },
	{ "RATIONALP", 01032 },
	{ "RATIOP", 01033 },
	{ "COMPLEXP", 01034 },
	{ "%RATIO-CONS", 01035 },
	{ "%COMPLEX-CONS", 01036 },
	{ "BOTH-CASE-P", 01037 },
	{ "CHAR-UPCASE", 01040 },
	{ "CHAR-DOWNCASE", 01041 },
	{ "LOWER-CASE-P", 01042 },

	{ "%micro-paging", 01100 },
	{ "%PROCESSOR-SWITCHES", 01101 },
	{ "%COLD-BOOT", 01102 },

	{ "%test-multiply-return-low", 01103 },
	{ "%test-multiply-return-high", 01104 },
	{ "%mult-16", 01105 },
	{ "%mult-32", 01106 },

	{ "%quart-transfer", 01107 },
	{ "%nubus-read-8", 01110 },
	{ "%nubus-write-8", 01111 },

	{ "%lambda-rg-quad-slot", 01112 },
	{ "%lambda-tv-quad-slot", 01113 },
	{ "%lambda-mouse-buttons", 01114 },
	{ "%sys-conf-physical-page", 01115 },
	{ "%lambda-sdu-quad-slot", 01116 },

	// FROM HERE TO 1777 FREE

	// - MISCELLANEOUS FUNCTIONS -
	{ "UNBIND-0", 0200 },
	{ "UNBIND-1", 0201 },
	{ "UNBIND-2", 0202 },
	{ "UNBIND-3", 0203 },
	{ "UNBIND-4", 0204 },
	{ "UNBIND-5", 0205 },
	{ "UNBIND-6", 0206 },
	{ "UNBIND-7", 0207 },
	{ "UNBIND-10", 0210 },
	{ "UNBIND-11", 0211 },
	{ "UNBIND-12", 0212 },
	{ "UNBIND-13", 0213 },
	{ "UNBIND-14", 0214 },
	{ "UNBIND-15", 0215 },
	{ "UNBIND-16", 0216 },
	{ "UNBIND-17", 0217 },

	{ "POPPDL-0", 0220 },
	{ "POPPDL-1", 0221 },
	{ "POPPDL-2", 0222 },
	{ "POPPDL-3", 0223 },
	{ "POPPDL-4", 0224 },
	{ "POPPDL-5", 0225 },
	{ "POPPDL-6", 0226 },
	{ "POPPDL-7", 0227 },
	{ "POPPDL-10", 0230 },
	{ "POPPDL-11", 0231 },
	{ "POPPDL-12", 0232 },
	{ "POPPDL-13", 0233 },
	{ "POPPDL-14", 0234 },
	{ "POPPDL-15", 0235 },
	{ "POPPDL-16", 0236 },
	{ "POPPDL-17", 0237 },
	{ (char *)0, 0 }
};

char *call_names[] = {
	"CALL",
	"CALL0",
	"MOVE",
	"CAR",
	"CDR",
	"CADR",
	"CDDR",
	"CDAR",
	"CAAR"
};

#endif