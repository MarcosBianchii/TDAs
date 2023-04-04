#ifndef __QUEUE_T__
#define __QUEUE_T__

typedef struct Node node_t;
typedef struct Queue queue_t;
typedef struct Hash hash_t;

queue_t *queue_new();
void queue_put(queue_t *q, node_t *n);
node_t *queue_detach(queue_t *q, node_t *n);
void queue_move(queue_t *q, node_t *n, hash_t *h);
void queue_pop(queue_t *q, hash_t *h);
void queue_free(queue_t *q);
void queue_print(queue_t *q);

#endif // __QUEUE_T__
