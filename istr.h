#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct istr {
    const char *s;
    const size_t len;
} istr;

typedef struct istr_builder istr_builder_t;

enum istr_error_code {
    ISTR_ERROR_ALLOC
};

istr cstr(const char *cstring);

istr_builder_t istr_builder_create();

istr istr_builder_convert(istr_builder_t *strbuild);

#define istr_cat(a, b) _Generic((a),                \
        istr *: _istr_cat_istr,                        \
        istr_builder_t *: _istr_cat_builder        \
)(a, b)

istr _istr_cat_istr(istr *a, istr *b);

void _istr_cat_builder(istr_builder_t *strbuild, istr *str);

#define istr_free(a) _Generic((a),                \
        istr * : _istr_free,                        \
        istr_builder_t * : _istr_builder_free        \
)(a)

void _istr_free(istr *str);

void _istr_builder_free(istr_builder_t *strbuild);

#define istr_split_pop(a, b) _Generic((a),        \
        istr * : _istr_split_pop_istr                \
)(a, b)

istr _istr_split_pop_istr(istr *str, char delimiter);

int64_t istr_index_of(istr *str, char c); // TODO: add support to get index of a string
bool istr_cmp(istr *a, istr *b);

istr istr_remove(istr *str, uint64_t index);

istr istr_remove_all(istr *str, char c);

istr istr_slice(istr *str, int32_t amount_to_slice);

static void istr_handle_error(enum istr_error_code code);

#define ISTR_IMPLEMENT
#ifdef ISTR_IMPLEMENT

typedef struct istr_builder {
    char *sb;
    size_t len;
} istr_builder_t;

istr cstr(const char *cstring) {
        istr res = {.len = strlen(cstring)};
        res.s = malloc(sizeof(char) * (res.len + 1));
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        memcpy((void *) res.s, cstring, res.len + 1);

        return res;
}

istr_builder_t istr_builder_create() {
        istr_builder_t strbuild = {.len = 0};
        return strbuild;
}

istr istr_builder_convert(istr_builder_t *strbuild) {
        istr res = {.s = malloc(sizeof(char) * (strbuild->len + 1)),
                .len = strbuild->len};
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        memcpy((void *) res.s, strbuild->sb, res.len + 1);

        return res;
}

istr _istr_cat_istr(istr *a, istr *b) {
        istr res = {.len = a->len + b->len};
        res.s = malloc(sizeof(char) * (res.len + 1));
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        memcpy((void *) res.s, a->s, a->len);
        memcpy((void *) (res.s + a->len), b->s, b->len + 1);

        return res;
}

void _istr_cat_builder(istr_builder_t *strbuild, istr *str) {
        bool start_of_cat = strbuild->len == 0;
        strbuild->len += str->len;
        if (strbuild->sb == NULL) {
                strbuild->sb = malloc(sizeof(char) * (strbuild->len + 1));
                if (strbuild->sb == NULL) {
                        istr_handle_error(ISTR_ERROR_ALLOC);
                        return;
                }
        } else
                strbuild->sb = realloc(strbuild->sb, strbuild->len + 1);

        if (start_of_cat)
                memcpy((void *) strbuild->sb, str->s, str->len + 1);
        else {
                memcpy((void *) (strbuild->sb + (strbuild->len - str->len)), str->s,
                       str->len + 1);
        }
}

void _istr_free(istr *str) { free((void *) str->s); }

void _istr_builder_free(istr_builder_t *strbuild) { free(strbuild->sb); }

int64_t istr_index_of(istr *str, char c) {
        for (size_t i = 0; i < str->len; i++) {
                if (str->s[i] == c)
                        return i;
        }
        return -1;
}

bool istr_cmp(istr *a, istr *b) {
        if (a->len != b->len)
                return false;
        for (size_t i = 0; i < a->len; i++) {
                if (a->s[i] != b->s[i])
                        return false;
        }
        return true;
}

istr istr_remove(istr *str, uint64_t index) {
        istr res = {.s = malloc(sizeof(char) * str->len), .len = str->len - 1};
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        memcpy((void *) res.s, str->s, index);
        memcpy((void *) &res.s[index], &str->s[index + 1], str->len - index);
        return res;
}

istr istr_remove_all(istr *str, char c) {
        uint32_t char_count = 0;
        for (uint64_t i = 0; i < str->len; i++)
                if (str->s[i] == c)
                        char_count++;

        istr res = {.s = malloc(sizeof(char) * (str->len - char_count + 1)),
                .len = str->len - char_count};
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        uint64_t j = 0;
        for (uint64_t i = 0; i < res.len; i++) {
                if (str->s[j] == c)
                        j++;
                memcpy((void *) &res.s[i], &str->s[j], 1);
                j++;
        }

        return res;
}

istr istr_slice(istr *str, int amount_to_slice) {
        bool slice_end = amount_to_slice < 0;
        if (slice_end)
                amount_to_slice *= -1;

        assert(str->len > (size_t) amount_to_slice);

        istr res = {.s = malloc(sizeof(char) * (str->len - amount_to_slice + 1)),
                .len = str->len - amount_to_slice};
        if (res.s == NULL) {
                istr_handle_error(ISTR_ERROR_ALLOC);
                return res;
        }

        memcpy((void *) res.s, slice_end ? str->s : &str->s[amount_to_slice], res.len);

        return res;
}

istr _istr_split_pop_istr(istr *str, char delimiter) {
        int64_t delim_loc = istr_index_of(str, delimiter);
        if (delim_loc != -1) {
                istr res = istr_slice(str, (str->len - delim_loc) * -1);
                if (res.s == NULL) {
                        istr_handle_error(ISTR_ERROR_ALLOC);
                        return res;
                }
                return res;
        }
        istr res = {.s = NULL, .len = 0};

        return res;
}

static void istr_handle_error(enum istr_error_code code) {
#ifndef ISTR_ERROR_NO_LOG
        switch (code) {
                case ISTR_ERROR_ALLOC:
                        perror("Error allocating string");
                        break;
        }
#endif
#ifndef ISTR_ERROR_NO_EXIT
        exit(EXIT_FAILURE);
#endif
}

#endif
