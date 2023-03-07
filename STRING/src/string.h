#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>

typedef struct String string;

// Returns a new string structure.
string *str_new(const char *str);

// Returns the length of the string.
size_t str_len(string *str);

// Appends char C in STR.
string *str_add(string *str, char c);

// Deletes the last char in STR.
string *str_sub(string *str);

// Inserts SRC in STR at index POS.
string *str_insert(string *str, string *src, size_t pos);

// Inserts SRC in STR at index POS.
char *strc_insert(string *str, const char *src, size_t pos);

// Removes N chars from [POS, POS + N] in STR.
string *str_remove(string *str, size_t pos, size_t n);

// Returns a pointer to the data in STR.
char *str_get(string *str);

// Returns the char at POS in STR.
char str_char_at(string *str, size_t pos);

// Replaces MAX(replace->len, N) chars of STR with replace at POS.
string *str_replace(string *str, string *replace, size_t pos, size_t n);

// Replaces MAX(strlen(REPLACE), N) chars of STR with replace at POS.
char *strc_replace(string *str, const char *replace, size_t pos, size_t n);

// Compares both strings up to MIN(S1->len, S2->len).
int str_cmp(string *s1, string *s2);

// Compares both strings up to MIN(STR->len, MIN(strlen(CSTR), N)).
int strc_cmp(string *str, const char *cstr, size_t n);

// Copies string SRC to DST.
string *str_cpy(string *dst, string *src);

// Copies CSRC to DST up to MIN(strlen(CSRC), N).
char *strc_cpy(string *dst, const char *csrc, size_t n);

// Appends SRC to DST.
string *str_cat(string *dst, string *src);

// Appends CSRC to DST up to MIN(strlen(CSRC), N).
char *strc_cat(string *dst, const char *csrc, size_t n);

// Returns the index of the first occurrence of SUBSTR in STR.
int str_str(string *str, string *substr);

// Returns a pointer to the first occurence of SUBSTR in STR up to N.
char *strc_str(string *str, const char *substr, size_t n);

// Returns a copy of STR.
// string must be freed with str_free.
string *str_dup(string *str);

// Returns a copy of STR of length N.
// string must be freed with free.
char *strc_dup(string *str, size_t n);

// Frees the memory used by STR.
void str_free(string *str);

#endif // __STRING_H__