#include "src/threadpool.h"
#include "src/deque.h"
#include <stdio.h>
#include <assert.h>

void test_init() {
    ThreadPool *pool = threadpool_new(4);
    
    assert(threadpool_running(pool) == 0);
    assert(threadpool_len(pool) == 4);

    threadpool_del(pool);
}

const size_t N = 100000000;
void sum(void *arg) {
    size_t *a = (size_t *) arg;
    
    for (size_t i = 0; i < N; i++) {
        *a += 1;
    }
}

void test_spawn_sequential() {
    ThreadPool *pool = threadpool_new(10);
    assert(threadpool_spawn(pool, NULL, NULL) == 1);
    size_t a = 0;

    assert(threadpool_running(pool) == 0);
    threadpool_spawn(pool, sum, &a);
    threadpool_wait(pool);
    assert(threadpool_running(pool) == 0);
    assert(a == N);

    assert(threadpool_running(pool) == 0);
    threadpool_spawn(pool, sum, &a);
    threadpool_wait(pool);
    assert(threadpool_running(pool) == 0);
    assert(a == 2 * N);

    assert(threadpool_running(pool) == 0);
    threadpool_spawn(pool, sum, &a);
    threadpool_wait(pool);
    assert(threadpool_running(pool) == 0);
    assert(a == 3 * N);

    threadpool_del(pool);
}

#define M 95

void ascii(void *__arg) {
    size_t *id = (size_t *) __arg;

    char str[M] = {0};
    for (size_t i = 0; i < M - 1; i++) {
        str[i] = ' ' + i;
    }

    printf("%li: %s\n", *id, str);
    free(id);
}

void test_spawn_async() {
    ThreadPool *pool = threadpool_new(2);

    for (size_t i = 0; i < 100; i++) {
        size_t *id = malloc(sizeof(size_t));
        *id = i;
        threadpool_spawn(pool, ascii, id);
    }

    threadpool_wait(pool);
    assert(threadpool_running(pool) == 0);

    threadpool_del(pool);
}

void print_deque(Deque d) {
    printf("i: %li, j: %li, len: %li, cap: %li\n", d.i, d.j, d.len, d.cap);
    for (size_t i = 0; i < d.cap; i++) {
        void *item = d.vec[i];
        if (item) {
            printf("%li: %p\n", i, d.vec[i]);
        } else {
            printf("%li: (null)\n", i);
        }
    }

    puts("");
}

void test_deque() {
    Deque d = deque_new(3);
    print_deque(d);

    deque_push_back(&d, (void *) 1);
    deque_push_back(&d, (void *) 2);
    print_deque(d);

    deque_pop_front(&d);
    print_deque(d);

    deque_push_front(&d, (void *) 3);
    print_deque(d);

    deque_push_front(&d, (void *) 4);
    print_deque(d);

    deque_push_front(&d, (void *) 5);
    print_deque(d);

    deque_push_front(&d, (void *) 6);
    print_deque(d);

    deque_push_back(&d, (void *) 7);
    print_deque(d);

    deque_push_back(&d, (void *) 8);
    print_deque(d);

    deque_del(&d, NULL);
}

int main() {
    test_init();
    test_spawn_sequential();
    test_spawn_async();
    test_deque();
    return 0;
}