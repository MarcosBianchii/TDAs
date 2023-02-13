#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


// struct de Grafo con matriz de adyacencia.
typedef struct Grafo {
      int **matriz;
      int n;
      int m;
} grafo_t;

#define NEGRO    "\033[0;30m"
#define ROJO     "\033[0;31m"
#define VERDE    "\033[0;32m"
#define AMARILLO "\033[0;33m"
#define BLANCO   "\033[0;37m"

// Reserva memoria para un grafo de n vertices.
grafo_t *grafo_crear(int n);

// Agrega una arista entre v1 y v2 con peso.
grafo_t *grafo_agregar_arista(grafo_t *g, int v1, int v2, int peso);

// Elimina la arista entre v1 y v2.
grafo_t *grafo_eliminar_arista(grafo_t *g, int v1, int v2);

// Devuelve true si existe una arista entre v1 y v2.
bool grafo_existe_arista(grafo_t *g, int v1, int v2);

// Devuelve el peso de la arista entre v1 y v2.
int grafo_peso_arista(grafo_t *g, int v1, int v2);

// Devuelve el cardinal de vertices del grafo.
int grafo_orden(grafo_t *g);

// Devuelve el cardinal de aristas del grafo.
int grafo_tamanio(grafo_t *g);

// Imprime la matriz de adyacencia del grafo
// y su número de vertices y aristas.
void grafo_imprimir(grafo_t *g);

// Devuelve un grafo complementario a g.
grafo_t *grafo_complementar(grafo_t *g);

// Recorre el Grafo en profundidad de u a v.
// Devuelve un arreglo con el recorrido y su tope en len.
int *grafo_DFS(grafo_t *g, int u, int v, int *len);

// Recorre el Grafo a lo ancho de u a v.
// Devuelve un arreglo con el recorrido y su tope en len.
int *grafo_BFS(grafo_t *g, int u, int v, int *len);

// Aplica Prim al grafo y devuelve
// su spanning tree minimo tomando a v0
// como el vertice inicial.
grafo_t *grafo_prim(grafo_t *g, int v0);

// Aplica Kruskal al grafo y devuelve
// su spanning tree minimo.
grafo_t *grafo_kruskal(grafo_t *g);

// Devuelve el camino minimo entre u y v.
// Devuelve un arreglo con el recorrido, su tope en len y su suma de pesos en coste.
int *grafo_dijkstra(grafo_t *g, int u, int v, int *len, int *coste);

// Libera la memoria reservada por grafo_crear().
void grafo_destruir(grafo_t *g);

#endif // __GRAFO_H__