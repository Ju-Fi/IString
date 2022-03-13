#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct istr {
	const char *s;
	const size_t len;
} istr;

istr cstr(const char * cstring);

istr istr_cat(istr *a, istr *b);
void istr_free(istr *str);
unsigned long istr_index_of(istr *str, char c); //TODO: add support to get index of a string
bool istr_cmp(istr *a, istr *b);
// TODO: istr_remove - removes first intstance of inputted character of that string and returns the result
