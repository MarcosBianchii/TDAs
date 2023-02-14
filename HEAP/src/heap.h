#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int (*heap_comparador)(void *, void *);

typedef struct Heap {
      void **vector;
      size_t tamanio;
      size_t capacidad;
      heap_comparador cmp;
} heap_t;

// Reserva memoria para un heap.
//
// cmp:
// a - b => Heap Maximal.
// b - a => Heap Minimal.
heap_t *heap_crear(heap_comparador cmp, int n);

// Inserta un elemento en el Heap.
heap_t *heap_insertar(heap_t *h, void *item);

// Quita el primer elemento del Heap y lo devuelve.
void *heap_quitar(heap_t *h);

// Devuelve la cantidad de items en el Heap.
int heap_tamanio(heap_t *h);

// Devuelve true si el Heap esta vacio.
bool heap_vacio(heap_t *h);

// Libera la memoria utilizada por el Heap.
void heap_destruir(heap_t *h);

// Libera la memoria utilizada por el Heap y sus items.
void heap_destruir_todo(heap_t *h, void (*f)(void *));

// Ordena un vector de punteros utilizando Heapsort.
void heapsort(void **v, int (*cmp)(void *, void *), int n);

#endif // __HEAP_H__