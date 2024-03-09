#include <stdlib.h>
#include <stdio.h>

#define TEST(_cond)					\
	do {						\
		if (!(_cond)) {				\
			fprintf(stderr,			\
			    #_cond " ... failed!\n");	\
			abort();			\
		} else					\
			fprintf(stderr,			\
			    #_cond " ... ok\n");	\
	} while (0)

int check_utf8(const char *, size_t);

int
main(int argc, char *argv[])
{
	TEST(check_utf8("ほげほげ", 12) == 1);
	//ほげほげ in Shift-JIS
	TEST(check_utf8("\x82\xd9\x82\xb0\x82\xd9\x82\xb0", 8) == 0);
	//copyright mark in UTF-8
	TEST(check_utf8("©", 2) == 1);
	// face in medical mask in UTF-8
	TEST(check_utf8("\xF0\x9F\x98\xB7", 4) == 1);
	// length invalid
	TEST(check_utf8("ふがふが", 11) == 0);
	// ascii
	TEST(check_utf8("Hello world.", 12) == 1);
	// empty
	TEST(check_utf8("", 1) == 1);
	// specials
	TEST(check_utf8("\t\b", 2) == 1);
	
	exit(0);
}
