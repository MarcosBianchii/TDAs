#include "heap.h"
#include <stdlib.h>

typedef struct Heap {
      void **vector;
      size_t tamanio;
      size_t capacidad;
      heap_comparador cmp;
} heap_t;

static void swap(void **a, void **b)
{
      void *c = *a;
      *a = *b;
      *b = c;
}

static void sift_up(void **v, int (*cmp)(void *, void *), int i)
{
      if (i == 0) return;

      int padre = (i-1)/2;
      if (cmp(v[i], v[padre]) > 0) {
            swap(&v[i], &v[padre]);
            sift_up(v, cmp, padre);
      }
}

static void sift_down(void **v, int (*cmp)(void *, void *), int tope, int i)
{
      if (i >= tope) return;

      int izq = i*2+1;
      int der = i*2+2;
      if (izq >= tope)
            return;

      int elegido = der < tope ? (cmp(v[izq], v[der]) < 0 ? der : izq) : izq;

      if (cmp(v[i], v[elegido]) < 0) {
            swap(&v[i], &v[elegido]);
            sift_down(v, cmp, tope, elegido);
      }
}

heap_t *heap_crear(heap_comparador cmp, int n)
{
      if (!cmp) return NULL;
      if (n < 10) n = 10;

      heap_t *h = malloc(sizeof(heap_t));
      if (!h) return NULL;

      h->vector = malloc(sizeof(void *) * n);
      if (!h->vector) {
            free(h);
            return NULL;
      }

      h->cmp = cmp;
      h->tamanio = 0;
      h->capacidad = n;

      return h;
}

static heap_t *heap_agrandar(heap_t *h)
{
      size_t nueva_capacidad = h->capacidad * 2;
      void *bloque = realloc(h->vector, sizeof(void *) * nueva_capacidad);
      if (!bloque) return NULL;

      h->vector = bloque;
      h->capacidad = nueva_capacidad;

      return h;
}

heap_t *heap_insertar(heap_t *h, void *item)
{
      if (!h) return NULL;

      if (h->tamanio == h->capacidad)
            heap_agrandar(h);

      h->vector[h->tamanio] = item;
      sift_up(h->vector, h->cmp, h->tamanio++);

      return h;
}

void *heap_quitar(heap_t *h)
{
      if (!h) return NULL;

      if (heap_vacio(h))
            return NULL;

      void *item = h->vector[0];
      swap(&h->vector[0], &h->vector[--h->tamanio]);
      sift_down(h->vector, h->cmp, h->tamanio, 0);

      return item;
}

int heap_tamanio(heap_t *h)
{
      if (!h) return 0;

      return h->tamanio;
}

bool heap_vacio(heap_t *h)
{
      if (!h) return true;

      return h->tamanio == 0;
}

void heap_destruir(heap_t *h)
{
      heap_destruir_todo(h, NULL);
}

void heap_destruir_todo(heap_t *h, void (*f)(void *))
{
      if (!h) return;

      if (f)
            for (int i = 0; i < h->tamanio; i++)
                  f(h->vector[i]);

      free(h->vector);
      free(h);
}

void heapsort(void **v, int (*cmp)(void *, void *), int n)
{
      for (int i = n/2-1; i >= 0; i--)
            sift_down(v, cmp, n, i);

      for (int i = 0; i < n; i++) {
            swap(&v[0], &v[n-1-i]);
            sift_down(v, cmp, n-2-i, 0);
      }
}