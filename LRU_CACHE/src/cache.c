#include "cache.h"
#include "queue.h"
#include "hash.h"
#include "node.h"

typedef struct LRU_Cache {
    queue_t *q;
    hash_t *h;
    size_t capacity;
    size_t size;
} cache_t;

cache_t *cache_new(uint64_t n) {
    cache_t *c = malloc(sizeof(cache_t));
    if (!c) return NULL;
    
    c->q = queue_new();
    c->h = hash_new(n);
    if (!c->q || !c->h) {
        queue_free(c->q);
        return NULL;
    }

    c->capacity = n;
    c->size = 0;
    return c;
}

cache_t *cache_put(cache_t *c, uint64_t p, uint32_t w) {
    if (!c) return NULL;

    node_t *n = hash_get(c->h, p);
    if (n) {
        node_set(n, p, w);
        queue_move(c->q, n, c->h);
        return c;
    }
    
    node_t *m = node_new(p, w);
    if (!m) return NULL;

    queue_put(c->q, m);
    hash_put(c->h, p, m);

    if (c->size == c->capacity) {
        queue_pop(c->q, c->h);
        return c;
    }

    c->size++;
    return c;
}

int cache_get(cache_t *c, uint64_t p) {
    if (!c) return -1;

    node_t *n = hash_get(c->h, p);
    if (!n) return -1;

    queue_move(c->q, n, c->h);
    return node_get_word(n);
}

size_t cache_size(cache_t *c) {
    if (!c) return 0;
    return c->size;
}

void cache_clear(cache_t *c) {
    if (!c) return;

    queue_t *q = queue_new();
    hash_t *h = hash_new(c->capacity);
    if (!q || !h) {
        queue_free(q);
        return;
    }

    queue_free(c->q);
    hash_free(c->h);

    c->q = q;
    c->h = h;
    c->size = 0;    
}

void cache_free(cache_t *c) {
    if (!c) return;

    queue_free(c->q);
    hash_free(c->h);
    free(c);
}

void cache_print(cache_t *c) {
    queue_print(c->q);
}
