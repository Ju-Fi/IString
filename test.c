#define ISTR_IMPLEMENT

#include "istr.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
        // cstr function takes in a regular c-string and returns an istring
        istr str = cstr("testings");
        istr str2 = cstr("bestings");
        printf("Str: %s %zu\n", str.s, str.len);
        printf("Str2: %s %zu\n", str2.s, str2.len);

        // istr_cat is a macro which can take in two istrings and returns an istring with their contents concatenated
        istr str3 = istr_cat(&str, &str2);
        printf("Cat: %s %zu\n", str3.s, str3.len);
        // istr_cat can also take in an istring builder and an istring and concatenate them if you need to perform an undetermined amount of concatenations
        istr_builder_t builder = istr_builder_create();
        for (int i = 0; i < 3; i++)
                istr_cat(&builder, &str3);

        // istr_builder_convert is used to convert an istring builder to an istring
        istr converted = istr_builder_convert(&builder);
        printf("Converted: %s %zu\n", converted.s, converted.len);

        // istr_cmp takes in two istrings and returns 1 (true) if they are identical and 0 (false) if they are not
        printf("Compared: %d\n", istr_cmp(&str, &str2));

        // istr_index_of returns the index of the given character. if the character is not found, it returns -1
        printf("Index: %lu\n", istr_index_of(&str2, 'b'));

        // istr_remove returns an istring with the character at the given index removed
        istr str4 = istr_remove(&str, istr_index_of(&str, 's'));
        printf("Removed: %s\n", str4.s);

        // istr_remove_all returns an istring with all instances of the given character removed
        istr str5 = istr_remove_all(&converted, 's');
        printf("Removed all: %s %zu\n", str5.s, str5.len);

        // istr_slice returns an istring with its contents `sliced` the amount of characters from the beginning inputted
        istr sliced_start = istr_slice(&str, 3);
        printf("Sliced start: %s\n", sliced_start.s);
        // when a negative number is inputted, characters are sliced from the end
        istr sliced_end = istr_slice(&str, -3);
        printf("Sliced end: %s\n", sliced_end.s);

        // istr_split_pop "splits" an istring based on the given delimiter and returns the first instance of the split
        istr split = istr_split_pop(&str2, 't');
        printf("Split: %s %zu\n", split.s, split.len);

        // istrings (and builders) are freed with istr_free
        istr_free(&str);
        istr_free(&str2);
        istr_free(&str3);
        istr_free(&str4);
        istr_free(&str5);
        istr_free(&sliced_start);
        istr_free(&sliced_end);
        istr_free(&converted);
        istr_free(&builder);

}

