#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Vector {
      void **data;
      size_t tamanio;
      size_t capacidad;
} vector_t;

// Crea un vector.
vector_t *vector_crear(int capacidad);

// Agrega un elemento al vector.
vector_t *vector_agregar(vector_t *v, void *elemento, int posicion);

// Devuelve el elemento en la posición indicada.
void *vector_obtener(vector_t *v, int posicion);

// Elimina un elemento del vector y lo devuelve.
void *vector_eliminar(vector_t *v, int posicion);

// Devuelve la cantidad de elementos del vector.
size_t vector_cantidad(vector_t *v);

// Devuelve true si el vector esta vacio.
bool vector_vacio(vector_t *v);

// Destruye un vector.
void vector_destruir(vector_t *v);

// Destruye un vector y sus elementos.
void vector_destruir_todo(vector_t *v, void (*f)(void *));

#endif // __VECTOR_H__