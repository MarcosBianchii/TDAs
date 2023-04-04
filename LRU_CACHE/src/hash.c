#include "hash.h"
#include "node.h"
#include <stdbool.h>

typedef struct Cell {
    node_t *node;
    bool flag;
} cell_t;

typedef struct Hash {
    cell_t *table;
    size_t capacity;
} hash_t;

static uint64_t hash(uint64_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

hash_t *hash_new(size_t n) {
    hash_t *h = malloc(sizeof(hash_t));
    if (!h) return NULL;

    h->capacity = n*2;
    h->table = calloc(h->capacity, sizeof(cell_t));
    if (!h->table) {
        free(h);
        return NULL;
    }

    return h;
}

static uint64_t traverse_table_put(hash_t *h, uint64_t pos, uint64_t p) {
    while (h->table[pos].node)
        pos = (pos + 1) % h->capacity;
    return pos;
}

void hash_put(hash_t *h, uint64_t p, node_t *n) {
    uint64_t pos = traverse_table_put(h, hash(p) % h->capacity, p);
    h->table[pos].node = n;
}

// TODO: mover el nodo en el hash si su pos inicial esta vacia.
static uint64_t traverse_table_get(hash_t *h, uint64_t pos, uint64_t p) {
    uint32_t counter = 0;
    while (counter++ < h->capacity && (h->table[pos].node || h->table[pos].flag) && node_get_page(h->table[pos].node) != p)
        pos = (pos + 1) % h->capacity;

    return pos;
}

node_t *hash_get(hash_t *h, uint64_t p) {
    uint64_t pos = traverse_table_get(h, hash(p) % h->capacity, p);
    return node_get_page(h->table[pos].node) == p ? h->table[pos].node : NULL;
}

void hash_remove(hash_t *h, uint64_t p) {
    uint64_t pos = traverse_table_get(h, hash(p) % h->capacity, p);
    if (node_get_page(h->table[pos].node) == p)
        h->table[pos] = (cell_t){
            .node = NULL,
            .flag = true,
        };
}

void hash_free(hash_t *h) {
    free(h->table);
    free(h);
}
