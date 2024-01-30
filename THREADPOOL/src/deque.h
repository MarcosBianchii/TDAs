#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <stdlib.h>
#include <stdbool.h>

#define DEQUE_RESIZE_COEF 2

typedef struct Deque {
    void **vec;
    size_t len, cap, i, j;
} Deque;


// Instanciates a new `Deque` with capacity `n`.
Deque deque_new(size_t n);


// Pushes `item` at the front of the deque.
//
// # Return
//
// Returns `0` on success and `1` on error.
//
// # Example
//
// ```c
// Deque d = deque_new(5);                        // []
// assert(0, deque_push_front(&d, (char *) "a")); // ["a"]
// assert(0, deque_push_front(&d, (char *) "b")); // ["b", "a"]
// assert(0, deque_push_front(&d, (char *) "c")); // ["c", "b", "a"]
// ```
int deque_push_front(Deque *deque, void *item);


// Pushes `item` at the back of the deque.
//
// # Return
//
// Returns `0` on success and `1` on error.
//
// # Example
//
// ```c
// Deque d = deque_new(5);                       // []
// assert(0, deque_push_back(&d, (char *) "a")); // ["a"]
// assert(0, deque_push_back(&d, (char *) "b")); // ["a", "b"]
// assert(0, deque_push_back(&d, (char *) "c")); // ["a", "b", "c"]
// ```
int deque_push_back(Deque *deque, void *item);


// Pops the item at the front of the deque and returns it. If the deque is empty return `NULL`.
//
// # Example
//
// ```c
// Deque d = deque_new(5);                       // []
// assert(0, deque_push_back(&d, (char *) "a")); // ["a"]
// assert(0, deque_push_back(&d, (char *) "b")); // ["a", "b"]
// 
// deque_pop_front(&d); // ["b"]
// deque_pop_front(&d); // []
// assert(NULL, deque_pop_front(&d));
// ```
void *deque_pop_front(Deque *deque);


// Pops the item at the back of the deque and returns it. If the deque is empty return `NULL`.
//
// # Example
//
// ```c
// Deque d = deque_new(5);                        // []
// assert(0, deque_push_front(&d, (char *) "a")); // ["a"]
// assert(0, deque_push_front(&d, (char *) "b")); // ["b", "a"]
// 
// deque_pop_back(&d); // ["b"]
// deque_pop_back(&d); // []
// assert(NULL, deque_pop_back(&d));
// ```
void *deque_pop_back(Deque *deque);


// Evaluates to `true` if the deque's capacity is equal to it's length.
bool deque_full(Deque deque);


// Evaluates to `true` if the deque's lenght is equal to `0`.
bool deque_empty(Deque deque);


// Resizes the given deque to with a new capacity only if `new_cap` <= deque->len.
// It rearranges the items so that they are in order.
int deque_resize(Deque *deque, size_t new_cap);


// Returns the amount of items in the given deque.
size_t deque_len(Deque deque);


// Returns the item capacity for the given deque.
size_t deque_cap(Deque deque);


// Frees the memory consumed by the structure and applies
// the given `destructor` function to every item in the deque.
void deque_del(Deque *deque, void (*destructor)(void *));

#endif // __DEQUE_H_