#ifndef __NODE_H__
#define __NODE_H__
#include <stdint.h>

typedef struct Node {
    uint32_t word;
    uint64_t page;
    struct Node *prev, *next;
} node_t;

node_t *node_new(uint64_t p, uint32_t w);
void node_set(node_t *n, uint64_t p, uint32_t w);
uint32_t node_get(node_t *n);

#endif // __NODE_H__