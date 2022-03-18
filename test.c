#define ISTR_IMPLEMENT
#include "istr.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    	// cstr function takes in a regular c-string and returns an istring
	istr str = cstr("testings");
	istr str2 = cstr("bestings");
	printf("%s %zu\n", str.s, str.len);
    	printf("%s %zu\n", str2.s, str2.len);

    	// istr_cat takes in two istrings and returns an istring with their contents concatenated
	istr str3 = istr_cat(&str, &str2);
	printf("%s %zu\n", str3.s, str3.len);

    	// istr_cmp takes in two istrings and returns 1 (true) if they are identical and 0 (false) if they are not
    	printf("%d\n", istr_cmp(&str, &str2));

    	// istr_index_of returns the index of the given character
    	printf("%lu\n", istr_index_of(&str2, 'b'));

	// istr_remove returns an istring with the character at the given index removed
	istr str4 = istr_remove(&str, istr_index_of(&str, 's'));
	printf("%s\n", str4.s);

    	// istrings are freed with istr_free
	istr_free(&str);
	istr_free(&str2);
	istr_free(&str3);	
}
