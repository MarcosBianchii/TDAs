#ifndef __DIGRAFO_H__
#define __DIGRAFO_H__

#include <stdbool.h>

typedef struct Digrafo digrafo_t;

// Reserva memoria para un digrafo.
digrafo_t *digrafo_crear(int n);

// Agrega v2 a la lista de adyacencia de v1.
digrafo_t *digrafo_agregar_arista(digrafo_t *d, int v1, int v2, int peso);

// Elimina v2 de la lista de adyacencia de v1.
int digrafo_borrar_arista(digrafo_t *d, int v1, int v2);

// Devuelve true si existe la arista de v1 a v2.
bool digrafo_existe_arista(digrafo_t *d, int v1, int v2);

// Devuelve el peso de la arista v1v2.
int digrafo_peso_arista(digrafo_t *d, int v1, int v2);

// Devuelve la cantidad de aristas del digrafo.
int digrafo_tamanio(digrafo_t *d);

// Imprime la estructura del digrafo por pantalla.
void digrafo_imprimir(digrafo_t *d);

// Libera la memoria reservada por digrafo_crear()
// y sus nodos de la lista.
void digrafo_destruir(digrafo_t *d);

#endif // __DIGRAFO_H__