#ifndef __QUEUE_T__
#define __QUEUE_T__

#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    uint32_t word;
    struct Node *prev, *next;
} node_t;


typedef struct Queue {
    node_t *head, *tail;
    size_t size;
} queue_t;

queue_t *queue_new();
void queue_put(queue_t *q, node_t *n);
void queue_remove(queue_t *q, node_t *n);
void queue_move(queue_t *q, node_t *n);
void queue_free(queue_t *q);
void queue_print(queue_t *q);

#endif // __QUEUE_T__