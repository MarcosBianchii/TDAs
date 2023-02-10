#ifndef __DIGRAFO_H__
#define __DIGRAFO_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
//    Struct de Nodo
//    para la lista
//    del digrafo.
*/
typedef struct Nodo {
      int peso;
      int vertice;
      struct Nodo *siguiente;
} nodo_t;

/*
//    Struct de Digrafo
//    con lista de adyacencia.
*/
typedef struct Digrafo {
      nodo_t **lista;
      int n;
      int m;
} digrafo_t;

#define NEGRO    "\033[0;30m"
#define ROJO     "\033[0;31m"
#define VERDE    "\033[0;32m"
#define AMARILLO "\033[0;33m"
#define BLANCO   "\033[0;37m"


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