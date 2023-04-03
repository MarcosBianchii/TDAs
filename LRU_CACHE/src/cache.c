#include "cache.h"
#include "queue.h"

typedef struct LRU_Cache {
    queue_t *q;
    node_t **s;
    size_t capacity;
    size_t size;
} cache_t;

cache_t *cache_new(uint64_t n) {
    cache_t *c = malloc(sizeof(cache_t));
    if (!c) return NULL;
    
    c->q = queue_new();
    c->s = calloc(n, sizeof(node_t *));
    if (!c->q || !c->s) {
        queue_free(c->q);
        return NULL;
    }

    c->capacity = n;
    c->size = 0;
    return c;
}

static node_t *node_new(uint32_t w) {
    node_t *n = calloc(1, sizeof(node_t));
    if (!n) return NULL;

    n->word = w;
    return n;
}

cache_t *cache_put(cache_t *c, uint64_t p, uint32_t w) {
    if (!c || c->capacity <= p) return NULL;

    node_t *n = c->s[p];
    if (n) {
        n->word = w;
        queue_move(c->q, n);
        return c;
    }
    
    node_t *m = node_new(w);
    if (!m) return NULL;

    c->s[p] = m;
    queue_put(c->q, m);
    if (c->size == c->capacity) {
        queue_remove(c->q, m);
        return c;
    }

    c->size++;
    return c;
}

int cache_get(cache_t *c, uint64_t p) {
    if (!c || c->capacity <= p || !c->s[p])
        return -1;

    queue_move(c->q, c->s[p]);
    return c->s[p]->word;
}

size_t cache_size(cache_t *c) {
    if (!c) return 0;
    return c->size;
}

void cache_clear(cache_t *c) {
    if (!c) return;

    queue_t *q = queue_new();
    node_t **s = calloc(c->capacity, sizeof(node_t *));
    if (!q || !s) {
        queue_free(q);
        return;
    }

    queue_free(c->q);
    free(c->s);

    c->q = q;
    c->s = s;
    c->size = 0;    
}

void cache_free(cache_t *c) {
    if (!c) return;

    queue_free(c->q);
    free(c->s);
    free(c);
}

void cache_print(cache_t *c) {
    queue_print(c->q);
}
