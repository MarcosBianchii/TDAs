#include "node.h"
#include <stdlib.h>

node_t *node_new(uint64_t p, uint32_t w) {
    node_t *n = calloc(1, sizeof(node_t));
    if (!n) return NULL;

    n->page = p;
    n->word = w;
    return n;
}

void node_set(node_t *n, uint64_t p, uint32_t w) {
    n->page = p;
    n->word = w;
}

uint64_t node_get_page(node_t *n) {
    if (!n) return -1;
    return n->page;
}

uint32_t node_get_word(node_t *n) {
    return n->word;
}
