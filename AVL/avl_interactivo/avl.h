#ifndef __AVL_H__
#define __AVL_H__

#include <stdbool.h>
#include <stdlib.h>

typedef enum { PREORDEN, INORDEN, POSTORDEN } avl_recorrido;

typedef int (*comparador_avl)(void *, void *);

typedef struct avl avl_t;

// Devuelve una estructura de arbol AVL.
avl_t *avl_crear(comparador_avl cmp);

// Inserta un elemento en el avl.
void avl_insertar(avl_t *avl, void *elemento);

// Quita un elemento del avl y lo devuelve.
void *avl_quitar(avl_t *avl, void *elemento);

// Busca un elemento dentro del avl.
void *avl_buscar(avl_t *avl, void *elemento);

// Devuelve true si el AVL no tiene elementos.
bool avl_vacio(avl_t *avl);

// Devuelve la cantidad de elementos dentro del AVL.
size_t avl_tamanio(avl_t *avl);

// Aplica la funcion a cada elemento del arbol utilizando un cierto recorrido, 
// si la funcion devuelve true el recorrido se corta.
void avl_recorrer_con_funcion(avl_t *avl, avl_recorrido recorrido, bool (*f)(void *));

// Libera la memoria utilizada por el AVL.
void avl_destruir(avl_t *avl);

// Libera la memoria utilizada por el AVL y sus elementos.
void avl_destruir_todo(avl_t *avl, void (*destructor)(void *));

#endif // __AVL_H__