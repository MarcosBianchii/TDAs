#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdbool.h>
#include <stdlib.h>


#define CHILDREN_LEN 256

typedef struct Trie {
    struct Trie *children[CHILDREN_LEN];
    size_t count;
    bool end;
} Trie;


// Instanciates an empty `Trie` structure.
Trie trie_new();


// Adds a new set of symbols to the `Trie`.
//
// # Return
//
// Returns `true` if the given string was already
// in the structure, otherwise returns `false`.
bool trie_add(Trie *t, const char *str);


// Removes the given set of symbols from the `Trie`.
//
// # Return
//
// Returns `true` if `str` was succesfully removed.
// If the given string was not found returns `false`.
bool trie_rm(Trie *t, const char *str);


// Evaluates to `true` if the given `Trie` has the given string.
bool trie_contains(Trie t, const char *str);


// Evaluates to `true` if the given `Trie` has no strings.
bool trie_is_empty(Trie t);


// Prints to the screen every string inside the structure.
#define trie_show(t) __trie_show((t), #t)
void __trie_show(Trie t, const char *var_name);


// Frees the memory used by the structure.
void trie_del(Trie *t);

#endif // __TRIE_H__
