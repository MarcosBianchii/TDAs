#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    uint32_t word;
    struct Node *prev, *next;
} node_t;

typedef struct Queue {
    node_t *head, *tail;
    size_t size;
} queue_t;

node_t *node_new(uint32_t w) {
    node_t *n = calloc(1, sizeof(node_t));
    if (!n) return NULL;

    n->word = w;
    return n;
}

void node_set(node_t *n, uint32_t w) {
    n->word = w;
}

uint32_t node_get(node_t *n) {
    return n->word;
}

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

void queue_remove(queue_t *q, node_t *n) {
    if (q->head == n) {
        if (n->next) n->next->prev = NULL;
        q->head = n->next;
        return;
    }

    else if (q->tail == n) {
        if (n->prev) n->prev->next = NULL;
        q->tail = n->prev;
        n->prev = NULL;
        return;
    }

    if (n->prev) n->prev->next = n->next;
    if (n->next) n->next->prev = n->prev;
    n->prev = NULL;
}

void queue_move(queue_t *q, node_t *n) {
    queue_remove(q, n);
    queue_put(q, n);
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
        printf("%d", n->word);
        n = n->next;
        if (n) printf(", ");
    }
    puts("]");
}
