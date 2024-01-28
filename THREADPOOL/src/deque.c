#include "deque.h"
#include "string.h"


Deque
deque_new(size_t n)
{
    return (Deque) {
        .vec = calloc(n, sizeof(void *)),
        .i = 0,
        .j = 0,
        .len = 0,
        .cap = n,
    };
}
#include <stdio.h>

int
deque_push_front(Deque *deque, void *item)
{
    if (deque_full(*deque)) {
        size_t prev_cap = deque->cap;
        if (deque_resize(deque, DEQUE_RESIZE_COEF * deque->cap) <= prev_cap) {
            return 1;
        }
    }

    size_t i = deque->i;
    deque->i = i == 0 ? deque->cap - 1 : i - 1;
    deque->vec[deque->i] = item;
    deque->len++;

    return 0;
}


int
deque_push_back(Deque *deque, void *item)
{
    if (deque_full(*deque)) {
        size_t prev_cap = deque->cap;
        if (deque_resize(deque, DEQUE_RESIZE_COEF * deque->cap) <= prev_cap) {
            return 1;
        }
    }

    deque->vec[deque->j] = item;
    deque->j = (deque->j + 1) % deque->cap; 
    deque->len++;

    return 0;
}


void *
deque_pop_front(Deque *deque)
{
    if (deque_empty(*deque)) {
        return NULL;
    }

    void *item = deque->vec[deque->i];
    deque->vec[deque->i] = NULL;
    deque->i = (deque->i + 1) % deque->cap;
    deque->len--;

    return item;
}


void *
deque_pop_back(Deque *deque)
{
    if (deque_empty(*deque)) {
        return NULL;
    }

    size_t j = deque->j;
    deque->j = j == 0 ? deque->cap - 1 : j - 1;
    
    void *item = deque->vec[deque->j];
    deque->vec[deque->j] = NULL;
    deque->len--;

    return NULL;
}


bool
deque_full(Deque deque)
{
    return deque.len == deque.cap;
}


bool
deque_empty(Deque deque)
{
    return deque.len == 0;
}


#define MIN(a, b) (a) < (b) ? (a) : (b)

int
deque_resize(Deque *deque, size_t new_cap)
{
    if (!deque) return 0;

    if (new_cap < deque->len) {
        return deque->cap;
    }

    void **new_table = calloc(new_cap, sizeof(void *));
    if (!new_table) return deque->cap;

    // Move [i..] items.
    size_t moved = MIN(deque->cap - deque->i, deque->len);
    size_t __n = sizeof(void *) * moved;
    memmove(new_table, &deque->vec[deque->i], __n);

    // Move [..j] items.
    size_t __m = sizeof(void *) * (deque->len - moved);
    memmove(new_table + moved, deque->vec, __m);

    free(deque->vec);
    *deque = (Deque) {
        .vec = new_table,
        .i = 0,
        .j = deque->len,
        .len = deque->len,
        .cap = new_cap,
    };

    return new_cap;
}


size_t
deque_len(Deque deque)
{
    return deque.len;
}


size_t
deque_cap(Deque deque)
{
    return deque.cap;
}


void
deque_del(Deque *deque, void (*destructor)(void *))
{
    size_t i = deque->i;
    size_t cap = deque->cap;
    void **vec = deque->vec;

    for (size_t k = 0; k < deque->len; k++) {
        if (destructor) destructor(vec[(i + k) % cap]);
    }

    free(vec);
}
