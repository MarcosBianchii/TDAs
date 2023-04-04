#include "node.h"
#include "queue.h"
#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Queue {
    node_t *head, *tail;
    size_t size;
} queue_t;

queue_t *queue_new() {
    return calloc(1, sizeof(queue_t));
}

static bool queue_empty(queue_t *q) {
    return q->head == NULL;
}

void queue_put(queue_t *q, node_t *n) {
    if (queue_empty(q)) {
        q->head = n;
        q->tail = n;
        return;
    }

    n->next = q->head;
    q->head->prev = n;
    q->head = n;
}

node_t *queue_detach(queue_t *q, node_t *n) {
    if (q->head == n) {
        if (n->next) n->next->prev = NULL;
        q->head = n->next;
    }

    else if (q->tail == n) {
        if (n->prev) n->prev->next = NULL;
        q->tail = n->prev;
    }

    else {
        if (n->prev) n->prev->next = n->next;
        if (n->next) n->next->prev = n->prev;
    }

    n->next = NULL;
    n->prev = NULL;
    return n;
}

void queue_move(queue_t *q, node_t *n, hash_t *h) {
    queue_detach(q, n);
    queue_put(q, n);
}

void queue_pop(queue_t *q, hash_t *h) {
    if (queue_empty(q)) return;

    node_t *n = q->tail;
    hash_remove(h, n->page);
    queue_detach(q, n);
    free(n);
}

void queue_free(queue_t *q) {
    while (q->head) {
        node_t *next = q->head->next;
        free(q->head);
        q->head = next;
    }

    free(q);
}

void queue_print(queue_t *q) {
    putc('[', stdout);
    node_t *n = q->head;
    while (n) {
        printf("%li:%i", n->page, n->word);
        n = n->next;
        if (n) printf(", ");
    }
    puts("]");
}
