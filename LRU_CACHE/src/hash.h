#ifndef __HASH_H__
#define __HASH_H__
#include <stdlib.h>
#include <stdint.h>

typedef struct Node node_t;
typedef struct Hash hash_t;

hash_t *hash_new(size_t n);
void hash_put(hash_t *h, uint64_t p, node_t *n);
node_t *hash_get(hash_t *h, uint64_t p);
void hash_remove(hash_t *h, uint64_t p);
void hash_free(hash_t *h);

#endif // __HASH_H__