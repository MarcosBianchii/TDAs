#ifndef __LRU_CACHE_H__
#define __LRU_CACHE_H__
#include <stdlib.h>
#include <stdint.h>

typedef struct LRU_Cache cache_t;

// Instanciates a new LRU_Cache.
cache_t *cache_new(uint64_t n);

// Inserts word w in page p.
cache_t *cache_put(cache_t *c, uint64_t p, uint32_t w);

// Returns the word assigned in page p.
int cache_get(cache_t *c, uint64_t p);

// Returns the quantity of elements in c.
size_t cache_size(cache_t *c);

// Clears all the data.
void cache_clear(cache_t *c);

// Frees memory used by c.
void cache_free(cache_t *c);

#endif // __LRU_CACHE_H__