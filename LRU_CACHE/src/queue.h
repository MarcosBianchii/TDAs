#ifndef __NODE_T__
#define __NODE_T__
#include <stdint.h>

typedef struct Node node_t;

node_t *node_new(uint32_t w);
void node_set(node_t *n, uint32_t w);
uint32_t node_get(node_t *n);

#endif // __NODE_T__


#ifndef __QUEUE_T__
#define __QUEUE_T__

typedef struct Queue queue_t;

queue_t *queue_new();
void queue_put(queue_t *q, node_t *n);
void queue_remove(queue_t *q, node_t *n);
void queue_move(queue_t *q, node_t *n);
void queue_free(queue_t *q);
void queue_print(queue_t *q);

#endif // __QUEUE_T__
