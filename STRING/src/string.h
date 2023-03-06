#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>

typedef struct String string;

// Returns a new string structure.
string *str_new(const char *str);

// Returns the length of the string.
size_t str_len(string *str);

// Appends char C in STR.
char *str_add(string *str, char c);

// Inserts SRC in STR at index POS.
char *str_insert(string *str, const char *src, size_t pos);

// Removes N chars from [POS, POS + N] in STR.
char *str_remove(string *str, size_t pos, size_t n);

// Returns a pointer to the data in STR.
char *str_get(string *str);

// Replaces MAX(strlen(REPLACE), N) chars of STR with replace at POS.
char *str_replace(string *str, const char *replace, size_t pos, size_t n);

// Compares both strings up to MIN(S1->len, S2->len).
int str_cmp(string *s1, string *s2);

// Compares both strings up to MIN(STR->len, MIN(strlen(CSTR), N)).
int strc_cmp(string *str, const char *cstr, size_t n);

// Copies string SRC to DST.
char *str_cpy(string *dst, string *src);

// Copies CSRC to DST up to MIN(strlen(CSRC), N).
char *strc_cpy(string *dst, const char *csrc, size_t n);

// Appends SRC to DST.
char *str_cat(string *dst, string *src);

// Appends CSRC to DST up to MIN(strlen(CSRC), N).
char *strc_cat(string *dst, const char *csrc, size_t n);

// Frees the memory used by STR.
void str_free(string *str);

#endif // __STRING_H__