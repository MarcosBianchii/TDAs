#include <stdio.h>
#include "src/threadpool.h"
#include <assert.h>

void test_init() {
    ThreadPool *pool = thpool_new(4);
    
    // Queue.
    assert(pool->tasks->len == 0);
    assert(pool->tasks->vec != NULL);

    // Workers.
    assert(!pool->exit);
    assert(pool->running == 0);
    assert(pool->len == 4);

    thpool_del(pool);
}

const size_t N = 100000000;
void sum(void *arg) {
    size_t *a = (size_t *) arg;
    
    for (size_t i = 0; i < N; i++) {
        *a += 1;
    }
}

void test_spawn_sequential() {
    ThreadPool *pool = thpool_new(10);
    assert(thpool_spawn(pool, NULL, NULL) == 2);
    size_t a = 0;

    assert(pool->running == 0);
    thpool_spawn(pool, sum, &a);
    thpool_wait(pool);
    assert(pool->running == 0);
    assert(a == N);

    assert(pool->running == 0);
    thpool_spawn(pool, sum, &a);
    thpool_wait(pool);
    assert(pool->running == 0);
    assert(a == 2 * N);

    assert(pool->running == 0);
    thpool_spawn(pool, sum, &a);
    thpool_wait(pool);
    assert(pool->running == 0);
    assert(a == 3 * N);

    thpool_del(pool);
}

const size_t M = 94;

struct Arg {
    size_t id;
    char *arg;
};

void ascii(void *__arg) {
    struct Arg *arg = (struct Arg *) __arg;
    arg->arg = malloc(M);

    for (size_t i = 0; i < M; i++) {
        arg->arg[i] = ' ' + i;
    }

    printf("%li: %s\n", arg->id, arg->arg);
    free(arg->arg);
    free(arg);
}

void test_spawn_async() {
    ThreadPool *pool = thpool_new(2);

    for (size_t i = 0; i < 100; i++) {
        struct Arg *arg = malloc(sizeof(struct Arg));
        arg->id = i;
        arg->arg = NULL;
        thpool_spawn(pool, ascii, arg);
    }

    thpool_wait(pool);
    assert(pool->running == 0);

    thpool_del(pool);
}

int main() {
    test_init();
    test_spawn_sequential();
    test_spawn_async();
    return 0;
}