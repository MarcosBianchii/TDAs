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

digrafo_t *digrafo_crear(int n);
digrafo_t *digrafo_agregar_arista(digrafo_t *d, int v1, int v2, int peso);
int        digrafo_borrar_arista(digrafo_t *d, int v1, int v2);
bool       digrafo_existe_arista(digrafo_t *d, int v1, int v2);
int        digrafo_peso_arista(digrafo_t *d, int v1, int v2);
int        digrafo_tamanio(digrafo_t *d);
void       digrafo_imprimir(digrafo_t *d);
void       digrafo_destruir(digrafo_t *d);

#endif // __DIGRAFO_H__