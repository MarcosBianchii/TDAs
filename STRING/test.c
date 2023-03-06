#include "src/string.h"
#include <stdio.h>
#include <stdlib.h>

void test_str_new() {
      string *str = str_new("Hello World!");
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n", str_len(str));
      printf("real len = %li\n\n", strlen(str_get(str)));
      str_free(str);

      str = str_new(NULL);
      printf("str_new(NULL) = %p\n", str);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));
      str_free(str);
}

void test_str_add() {
      string *str = str_new("Hello World");
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));
      str_add(str, '!');
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));
      str_add(str, '!');
      str_add(str, '!');
      str_add(str, '!');
      str_add(str, '!');
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n", str_len(str));
      printf("real len = %li\n\n", strlen(str_get(str)));
      str_add(NULL, '!');
      str_free(str);
}

void test_str_insert() {
      string *str = str_new("Hello World");
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_insert(str, "Hello ", 6);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_insert(str, "Bye ", 0);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_insert(str, "!", 100);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n", str_len(str));
      printf("real len = %li\n\n", strlen(str_get(str)));

      str_free(str);
}

void test_str_remove() {
      string *str = str_new("Hello World!");
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_remove(str, 0, 2);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_insert(str, "He", 0);
      str_remove(str, str_len(str), 2);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_insert(str, "d!", str_len(str));
      str_remove(str, 3, str_len(str));
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n", str_len(str));
      printf("real len = %li\n\n", strlen(str_get(str)));

      str_free(str);
}

void test_str_replace() {
      string *str = str_new("Hello World!");
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_replace(str, "Bye", 0, 5);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_replace(str, "Hola!", 0, 1);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_replace(str, " World!", 4, 1);
      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      str_free(str);
}

void test_str_cmp() {
      string *str = str_new("Hello World!");
      string *__0 = str_new("Hello_World!");
      string *__1 = str_new("Hola Mundo!!");
      string *__2 = str_new(str_get(str));

      printf("str_cmp(str, __0) = %i\n", str_cmp(str, __0));
      printf(" strcmp(str, __0) = %i\n\n", strcmp(str_get(str), str_get(__0)));

      printf("str_cmp(str, __1) = %i\n", str_cmp(str, __1));
      printf(" strcmp(str, __1) = %i\n\n", strcmp(str_get(str), str_get(__1)));

      printf("str_cmp(str, __2) = %i\n", str_cmp(str, __2));
      printf(" strcmp(str, __2) = %i\n\n", strcmp(str_get(str), str_get(__2)));

      printf("str_cmp(NULL, str) = %i\n", str_cmp(NULL, str));
      printf("str_cmp(str, NULL) = %i\n", str_cmp(str, NULL));
      printf("str_cmp(NULL, NULL) = %i\n", str_cmp(NULL, NULL));

      str_free(str);
      str_free(__0);
      str_free(__1);
      str_free(__2);
}

void test_strc_cmp() {
      string *str = str_new("Hello World!");

      printf("str_cmp(str, 'Hello World') = %i\n", strc_cmp(str, "Hello World!", 0));
      printf(" strcmp(str, 'Hello World') = %i\n\n", strcmp(str_get(str), "Hello World!"));

      printf("str_cmp(str, 'Hola Mundo') = %i\n", strc_cmp(str, "Hola Mundo!", 0));
      printf(" strcmp(str, 'Hola Mundo') = %i\n\n", strcmp(str_get(str), "Hola Mundo!"));

      printf("str_cmp(str, 'Hello_World!') = %i\n", strc_cmp(str, "Hello_World!!", 0));
      printf(" strcmp(str, 'Hello_World!') = %i\n\n", strcmp(str_get(str), "Hello_World!!"));

      str_free(str);
}

void test_str_cpy() {
      string *str = str_new("Hello World!");
      string *__0 = str_new("Chau Mundo");
      string *__1 = str_new("Hola Mundo!");

      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      printf("str_cpy(str, __0) = %s\n", str_cpy(str, __0));
      printf("str->len = %li\n\n", str_len(str));

      printf("str_cpy(str, __1) = %s\n", str_cpy(str, __1));
      printf("str->len = %li\n\n", str_len(str));

      printf("str_cpy(__0, __1) = %s\n", str_cpy(__0, __1));
      printf("str->len = %li\n\n", str_len(__0));

      str_free(str);
      str_free(__0);
      str_free(__1);
}

void test_strc_cpy() {
      string *str = str_new("Hello World!");
      char *cstr = malloc(sizeof(char) * 100);
      strcpy(cstr, "Hola Mundo");

      printf("strc_cpy(str, cstr, 0) = %s\n", strc_cpy(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      strcpy(cstr, "Chau Mundo");
      printf("strc_cpy(str, cstr, 0) = %s\n", strc_cpy(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      strcpy(cstr, "Hello World!");
      printf("strc_cpy(str, cstr, 0) = %s\n", strc_cpy(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      str_free(str);
      free(cstr);
}

void test_str_cat() {
      string *str = str_new("Hello World!");
      string *__0 = str_new("Chau Mundo");
      string *__1 = str_new("Hola Mundo!");

      printf("str->data = %s\n", str_get(str));
      printf("str->len = %li\n\n", str_len(str));

      printf("str_cat(str, __0) = %s\n", str_cat(str, __0));
      printf("str->len = %li\n\n", str_len(str));
      
      printf("str_cat(str, __1) = %s\n", str_cat(str, __1));
      printf("str->len = %li\n\n", str_len(str));

      printf("str_cat(__0, __1) = %s\n", str_cat(__0, __1));
      printf("str->len = %li\n\n", str_len(__0));

      str_free(str);
      str_free(__0);
      str_free(__1);
}

void test_strc_cat() {
      string *str = str_new("Hello World!");
      char *cstr = malloc(sizeof(char) * 100);
      strcpy(cstr, "Hola Mundo");

      printf("strc_cat(str, cstr, 0) = %s\n", strc_cat(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      strcpy(cstr, "Chau Mundo");
      printf("strc_cat(str, cstr, 0) = %s\n", strc_cat(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      strcpy(cstr, "Hello World!");
      printf("strc_cat(str, cstr, 0) = %s\n", strc_cat(str, cstr, 0));
      printf("str->len = %li\n\n", str_len(str));

      str_free(str);
      free(cstr);
}

int main() {
      // test_str_new();
      // test_str_add();
      // test_str_insert();
      // test_str_remove();
      // test_str_replace();
      // test_str_cmp();
      // test_strc_cmp();
      // test_str_cpy();
      // test_strc_cpy();
      // test_str_cat();
      // test_strc_cat();
      return 0;
}