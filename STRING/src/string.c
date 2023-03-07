#include "string.h"
#include <stdlib.h>

#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

typedef struct String {
      char *data;
      size_t len;
} string;

string *str_new(const char *str) {
      size_t size = 0;
      if (str) size = strlen(str); 

      string *new_str = malloc(sizeof(string));
      if (!new_str) return NULL;

      new_str->data = malloc(sizeof(char) * (size + 1));
      if (!new_str->data) {
            free(new_str);
            return NULL;
      }

      new_str->len = size;
      memcpy(new_str->data, str, size * sizeof(char));
      new_str->data[size] = '\0';
      return new_str;
}

size_t str_len(string *str) {
      if (!str) return 0;
      return str->len;
}

static int str_resize(string *str, size_t new_cap) {
      if (new_cap <= 0) new_cap = 1;

      char *new_block = realloc(str->data, sizeof(char) * new_cap);
      if (!new_block) return 0;

      str->data = new_block;
      return 1;
}

string *str_add(string *str, char c) {
      if (!str) return NULL;

      if (!str_resize(str, str->len + 2))
            return NULL;
      
      str->data[str->len++] = c;
      str->data[str->len] = '\0';

      return str;
}

string *str_sub(string *str) {
      if (!str || str->len <= 0) return NULL;

      if (!str_resize(str, str->len))
            return NULL;

      str->data[--str->len] = '\0';
      return str;
}

char *strc_insert(string *str, const char *src, size_t pos) {
      if (!str || !src) return NULL;

      pos = pos >= str->len ? str->len : (pos < 0 ? 0 : pos);
      int src_len = strlen(src);
      str_resize(str, str->len + src_len + 1);

      memcpy(
            str->data + pos + src_len,
            str->data + pos,
            (str->len - pos) * sizeof(char)
      );
      
      memcpy(
            str->data + pos,
            src,
            src_len * sizeof(char)
      );

      str->len += src_len;
      str->data[str->len] = '\0';

      return str->data;
}

string *str_insert(string *str, string *src, size_t pos) {
      if (!str || !src) return NULL;

      if (!strc_insert(str, src->data, pos))
            return NULL;
      
      return str;
}

string *str_remove(string *str, size_t pos, size_t n) {
      if (!str || n <= 0) return NULL;

      pos = pos >= str->len ? str->len - n : (pos < 0 ? 0 : pos);
      n = pos + n > str->len ? str->len - pos : n;
      int diff = str->len - pos - n;

      memmove(
            str->data + pos,
            str->data + pos + n,
            diff * sizeof(char)
      );

      str_resize(str, str->len - n + 1);
      str->len -= n;
      str->data[str->len] = '\0';

      return str;
}

char *str_get(string *str) {
      if (!str) return NULL;
      return str->data;
}

char str_char_at(string *str, size_t pos) {
      if (!str || pos >= str->len) return '\0';
      if (pos < 0) pos = 0;
      return str->data[pos];
}

string *str_replace(string *str, string *replace, size_t pos, size_t n) {
      if (!str || !replace) return NULL;

      n = MAX(replace->len, n);
      if (!str_remove(str, pos, n)
      ||  !str_insert(str, replace, pos))
            return NULL;
      
      return str;
}

char *strc_replace(string *str, const char *replace, size_t pos, size_t n) {
      if (!str || !replace) return NULL;

      n = MAX(strlen(replace), n);
      if (!str_remove(str, pos, n)
      ||  !strc_insert(str, replace, pos))
            return NULL;

      return str->data;
}

int str_cmp(string *s1, string *s2) {
      if (!s1 || !s2) return 0;
      return strncmp(s1->data, s2->data, MIN(s1->len, s2->len));
}

int strc_cmp(string *str, const char *cstr, size_t n) {
      if (!str || !cstr) return 0;

      if (n <= 0) n = str->len;
      return strncmp(str->data, cstr, MIN(str->len, MIN(strlen(cstr), n)));
}

string *str_cpy(string *dst, string *src) {
      if (!src || !dst) return NULL;

      if (!str_resize(dst, src->len + 1))
            return NULL;

      if (!strncpy(dst->data, src->data, src->len))
            return NULL;

      dst->len = src->len;
      dst->data[dst->len] = '\0';
      return dst;
}

char *strc_cpy(string *dst, const char *csrc, size_t n) {
      if (!csrc || !dst) return NULL;

      int src_len = strlen(csrc);
      if (n <= 0) n = src_len;

      int min_value = MIN(src_len, n);
      if (!str_resize(dst, min_value + 1))
            return NULL;

      if (!strncpy(dst->data, csrc, min_value))
            return NULL;
      
      dst->len = min_value;
      dst->data[dst->len] = '\0';
      return dst->data;
}

string *str_cat(string *dst, string *src) {
      if (!dst || !src) return NULL;

      if (!str_resize(dst, dst->len + src->len + 1))
            return NULL;
      
      if (!strncat(dst->data, src->data, src->len))
            return NULL;

      dst->len += src->len;
      dst->data[dst->len] = '\0';
      return dst;
}

char *strc_cat(string *dst, const char *csrc, size_t n) {
      if (!dst || !csrc) return NULL;

      int src_len = strlen(csrc);
      if (n <= 0) n = src_len;

      int min_value = MIN(src_len, n);
      if (!str_resize(dst, dst->len + min_value + 1))
            return NULL;
      
      if (!strncat(dst->data, csrc, min_value))
            return NULL;
      
      dst->len += min_value;
      dst->data[dst->len] = '\0';
      return dst->data;
}

int str_str(string *str, string *substr) {
      if (!str || !substr) return -1;

      int i = 0;
      int j = 0;
      while (i < str->len) {
            while (str->data[i] == substr->data[j]) {
                  if (!substr->data[++j])
                        return i - j + 1;
                  i++;
            }

            i++;
      }

      return -1;
}

char *strc_str(string *str, const char *substr, size_t n) {
      if (!str || !substr) return NULL;

      int src_len = strlen(substr);
      if (n <= 0) n = src_len;
      char *i = str->data;
      char *j = (char *)substr;
      int counter = 0;
      while (*i) {
            while (*i == *j) {
                  if (!*++j || counter == n)
                        return i - src_len + 1;
                  i++;
                  counter++;
            }

            counter = 0;
            i++;
      }

      return NULL;
}

string *str_dup(string *str) {
      if (!str) return NULL;
      return str_new(str->data);
}

char *strc_dup(string *str, size_t n) {
      if (!str) return NULL;
      if (n <= 0) n = str->len;

      char *new_str = malloc(MIN(str->len, n) + 1);
      if (!new_str) return NULL;

      strncpy(new_str, str->data, MIN(str->len, n));
      return new_str;
}

void str_free(string *str) {
      if (!str) return;
      free(str->data);
      free(str);
}