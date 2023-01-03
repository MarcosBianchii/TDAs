#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int (*heap_comparador)(void *, void *);

// Struct de Heap.
typedef struct Heap {
      void **vector;
      int tamanio;
      size_t size;
      heap_comparador cmp;
} heap_t;

// Reserva memoria para un heap.
//
// cmp:
// a - b => Heap Maximal.
// b - a => Heap Minimal.
heap_t *heap_crear(heap_comparador cmp, int n);

// Inserta un elemento en el heap.
heap_t *heap_insertar(heap_t *h, void *item);

// Quita el primer elemento del heap y lo devuelve.
void *heap_quitar(heap_t *h);

// Devuelve el primer elemento del heap.
int heap_tamanio(heap_t *h);

// Devuelve el primer elemento del heap.
bool heap_vacio(heap_t *h);

// Destruye el heap.
void heap_destruir(heap_t *h);

// Destruye el heap y todos sus elementos.
void heap_destruir_todo(heap_t *h, void (*f)(void *));

// Ordena un vector de punteros.
void heapsort(void **v, heap_comparador cmp, int n);