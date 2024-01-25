#include "trie.h"
#include <stdio.h>


static inline bool
contains_symbol(Trie *t, unsigned char symbol)
{
    return t->children[symbol] != NULL;
}


static inline bool
str_is_empty(unsigned char *str)
{
    return *str == '\0';
}


static inline bool
str_is_last_char(unsigned char *str)
{
    return str_is_empty(str + 1);
}


Trie
trie_new()
{
    return (Trie) {
        .children = { 0 },
        .count = 0,
        .end = false,
    };
}


// Wrapper over `trie_add`.
static bool
__trie_add(Trie *t, unsigned char *str)
{
    if (!contains_symbol(t, *str)) {
        Trie *symbol = calloc(1, sizeof(Trie));
        t->children[*str] = symbol;
        t->count++;

        if (str_is_last_char(str)) {
            symbol->end = true;
            return false;
        }

    } else if (str_is_last_char(str)) {
        bool prev = t->children[*str]->end;
        t->children[*str]->end = true;
        return prev;
    }

    return __trie_add(t->children[*str], str + 1);
}


bool
trie_add(Trie *t, const char *signed_str)
{
    if (!t) return false;

    // Cast to `unsigned char *` to prevent negative indices.
    unsigned char *str = (unsigned char *) signed_str;

    if (str_is_empty(str)) {
        bool prev = t->end;
        t->end = true;
        return prev;
    }

    return __trie_add(t, str);
}


// Wrapper over `trie_rm`.
static Trie *
__trie_rm(Trie *t, unsigned char *str, bool *deleted)
{
    if (!t) return NULL;

    if (str_is_empty(str)) {
        if (t->end) {
            t->end = false;
            *deleted = true;
            if (trie_is_empty(*t)) {
                free(t);
                return NULL;
            }
        }

        return t;
    }

    t->children[*str] = __trie_rm(t->children[*str], str + 1, deleted);
    if (trie_is_empty(*t) && !t->end) {
        free(t);
        return NULL;
    }

    return t;
}


bool
trie_rm(Trie *t, const char *signed_str)
{
    if (!t) return false;

    // Cast to `unsigned char *` to prevent negative indices.
    unsigned char *str = (unsigned char *) signed_str;
    bool deleted = false;

    __trie_rm(t, str, &deleted);
    return deleted;
}


// Wrapper over `trie_contains`.
static bool
__trie_contains(Trie *t, unsigned char *str)
{
    if (!contains_symbol(t, *str)) {
        return false;
    }

    if (t->children[*str]->end && str_is_last_char(str)) {
        return true;
    }

    return __trie_contains(t->children[*str], str + 1);
}


bool
trie_contains(Trie t, const char *signed_str)
{
    // Cast to `unsigned char *` to prevent negative indices.
    unsigned char *str = (unsigned char *) signed_str;

    if (str_is_empty(str)) {
        return t.end;
    }

    return __trie_contains(&t, str);
}


static bool
__trie_contains_prefix(Trie *t, unsigned char *prefix)
{
    if (str_is_empty(prefix)) {
        return true;
    }

    if (!contains_symbol(t, *prefix)) {
        return false;
    }

    return __trie_contains_prefix(t->children[*prefix], prefix + 1);
}


bool
trie_contains_prefix(Trie t, const char *signed_prefix)
{
    // Cast to `unsigned char *` to prevent negative indices.
    unsigned char *prefix = (unsigned char *) signed_prefix;
    return __trie_contains_prefix(&t, prefix);
}


bool
trie_is_empty(Trie t)
{
    return t.count == 0;
}


// Procedure that navigates the trie's children
// accumulating their values in `acc` and printing
// it's state at terminal nodes.
static void
print_trie(Trie *t, char *acc, size_t len)
{
    if (t->end) printf("\"%s\"\n", acc);

    if (t->count == 0) {
        return;
    }

    size_t read = 0;
    size_t new_len = len + 1;
    for (int i = 0; i < CHILDREN_LEN; i++) {
        if (read == t->count) break;

        if (contains_symbol(t, i)) {
            char new_str[new_len + 1];
            snprintf(new_str, new_len + 1, "%s%c", acc, i);
            read++;

            print_trie(t->children[i], new_str, new_len);
        }
    }
}


// Macro implementation for printing a `Trie`.
void
__trie_show(Trie t, const char *var_name)
{
    printf("%s:\n", var_name);
    print_trie(&t, "", 0);
    puts("");
}


static void
__trie_del(Trie *t)
{
    for (int i = 0; i < CHILDREN_LEN; i++) {
        if (t->count == 0) break;

        if (t->children[i]) {
            __trie_del(t->children[i]);
            free(t->children[i]);
            t->count--;
        }
    }
}


void
trie_del(Trie *t)
{
    if (!t) return;

    for (int i = 0; i < CHILDREN_LEN; i++) {
        if (t->count == 0) break;

        if (t->children[i]) {
            __trie_del(t->children[i]);
            free(t->children[i]);
            t->children[i] = NULL;
            t->count--;
        }
    }
}
