#include "src/cache.h"
#include <stdint.h>
#include <stdio.h>

void test_cache_new() {
    cache_t *c = cache_new(5);
    printf("cache_new(5) = %p\n", c);
    printf("cache_size(c) = %lu\n", cache_size(c));
    cache_free(c);

    puts("");
    cache_t *d = cache_new(-1);
    printf("cache_new(-1) = %p\n", d);
    printf("cache_size(c) = %lu\n", cache_size(d));
    cache_free(d);
}

void test_cache_put() {
    cache_t *c = cache_new(3);
    cache_put(c, 0, 10);
    cache_print(c);

    cache_put(c, 1, 11);
    cache_print(c);

    cache_put(c, 2, 12);
    cache_print(c);

    cache_put(c, 3, 13);
    cache_print(c);

    cache_put(c, 4, 14);
    cache_print(c);

    cache_put(c, 5, 15);
    cache_print(c);

    cache_free(c);
}

void test_cache_get() {
    cache_t *c = cache_new(5);

    cache_put(c, 0, 10);
    cache_put(c, 1, 11);
    cache_put(c, 2, 12);
    cache_put(c, 3, 13);
    cache_put(c, 4, 14);
    cache_print(c);
    puts("");

    printf("cache_get(c, 1) = %d\n", cache_get(c, 1));
    cache_print(c);
    puts("");

    printf("cache_get(c, 3) = %d\n", cache_get(c, 3));
    cache_print(c);
    puts("");

    printf("cache_get(c, -1) = %d\n", cache_get(c, -1));
    cache_print(c);
    puts("");

    printf("cache_get(c, 10) = %d\n", cache_get(c, 10));
    cache_print(c);
    puts("");

    cache_free(c);
}

void test_cache_clear() {
    cache_t *c = cache_new(5);

    cache_put(c, 0, 10);
    cache_put(c, 1, 11);
    cache_put(c, 2, 12);
    cache_put(c, 3, 13);
    cache_put(c, 4, 14);
    cache_print(c);
    printf("size = %li\n", cache_size(c));
    puts("");

    cache_clear(c);
    cache_print(c);
    printf("size = %li\n", cache_size(c));
    puts("");

    cache_free(c);
}

int main() {
    // test_cache_new();
    // test_cache_put();
    // test_cache_get();
    // test_cache_clear();

    return 0;
}
