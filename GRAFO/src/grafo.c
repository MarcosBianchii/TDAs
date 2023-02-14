#include "grafo.h"
#include "../lista/lista.h"
#include "../lista/pila.h"
#include "../lista/cola.h"
#include "../heap/heap.h"

grafo_t *grafo_crear(int n)
{
      if (n < 1) return NULL;

      grafo_t *g = calloc(1, sizeof(grafo_t));
      if (!g) return NULL;

      g->matriz = calloc(n, sizeof(int *));
      if (!g->matriz) {
            free(g);
            return NULL;
      }

      for (int i = 0; i < n; i++) {
            g->matriz[i] = calloc(i + 1, sizeof(celda_t));
            if (!g->matriz[i]) {
                  grafo_destruir(g);
                  return NULL;
            }

            g->n++;
      }

      return g;
}

// Devuelve true si los vertices estan dentro del intervalo [0, n-1].
static bool dentro_de_rango(grafo_t *g, int a, int b)
{
      return (a >= 0 && b >= 0 && a < g->n && b < g->n);
}

static void swap(int *a, int *b)
{
      int aux = *a;
      *a = *b;
      *b = aux;
}

grafo_t *grafo_agregar_arista(grafo_t *g, int v1, int v2, int peso)
{
      if (!g || !dentro_de_rango(g, v1, v2))
            return NULL;

      if (v1 < v2)
            swap(&v1, &v2);

      if (!grafo_existe_arista(g, v1, v2))
            g->m++;

      g->matriz[v1][v2].peso = peso;
      g->matriz[v1][v2].existe = true;
      return g;
}

grafo_t *grafo_eliminar_arista(grafo_t *g, int v1, int v2)
{
      if (!g || !dentro_de_rango(g, v1, v2))
            return NULL;

      if (v1 < v2)
            swap(&v1, &v2);

      if (grafo_existe_arista(g, v1, v2))
            g->m--;

      g->matriz[v1][v2].peso = 0;
      g->matriz[v1][v2].existe = false;
      return g;
}

bool grafo_existe_arista(grafo_t *g, int v1, int v2)
{
      if (!g || !dentro_de_rango(g, v1, v2))
            return false;

      if (v1 < v2)
            swap(&v1, &v2);
      
      return g->matriz[v1][v2].existe;
}

int grafo_peso_arista(grafo_t *g, int v1, int v2)
{
      if (!g || !dentro_de_rango(g, v1, v2))
            return 0;

      if (v1 < v2)
            swap(&v1, &v2);
      
      return g->matriz[v1][v2].peso;
}

int grafo_orden(grafo_t *g)
{
      if (!g) return 0;
      return g->n;
}

int grafo_tamanio(grafo_t *g)
{
      if (!g) return 0;
      return g->m;
}

void grafo_imprimir(grafo_t *g)
{
      if (!g) {
            printf(ROJO"Grafo es NULL"BLANCO);
            return;
      }

      int n_len = floor(log10(g->n))+1;
      printf("\n "VERDE);
      for (int i = 0; i < n_len - 1; i++)
            printf(" ");

      for (int i = 0; i < g->n; i++) {
            int i_len = i == 0 ? 1 : floor(log10(i))+1;
            for (int j = 0; j < 3 - i_len + 1; j++)
                  printf(" ");
            printf("%i", i);
      }

      printf(BLANCO"\n  ");
      for (int i = 0; i < n_len-1; i++)
            printf(" ");
      for (int i = 0; i < g->n; i++)
            printf("+---");
      printf("+");

      for (int i = 0; i < g->n; i++) {
            printf("\n");
            int i_len = i == 0 ? 1 : floor(log10(i))+1;
            for (int j = n_len; j > i_len; j--)
                  printf(" ");

            printf(VERDE"%i"BLANCO, i);

            for (int j = 0; j < i; j++)
                  printf("    ");
            printf(BLANCO" |");

            for (int j = i; j < g->n; j++) {
                  int pos_len_peso = grafo_peso_arista(g, i, j) == 0 ? 1 : grafo_peso_arista(g, i, j);
                  int pos_len = !grafo_existe_arista(g, i, j) ? 1 : floor(log10(pos_len_peso)) + 1;
                  if (pos_len <= 2) printf(" ");

                  if (grafo_existe_arista(g, i, j))
                        printf(ROJO"%i"BLANCO, grafo_peso_arista(g, i, j));
                  else  printf(" ");

                  if (pos_len == 1) printf(" ");
                  printf("|");
            }

            printf("\n  ");
            for (int j = 0; j < i; j++)
                  printf("    ");
            for (int j = 0; j < n_len-1; j++)
                  printf(" ");
            for (int j = 0; j < g->n - i; j++)
                  printf(BLANCO"+---");
            printf("+");
      }

      printf("\nn: %i | m: %i\n\n", g->n, g->m);
}

bool grafo_complementar(grafo_t *g)
{
      if (!g) return false;

      g->m = g->n * (g->n - 1) / 2 - g->m;

      for (int i = 0; i < g->n; i++)
            for (int j = 0; j <= i; j++)
                  if (i != j)
                        g->matriz[i][j].existe = !g->matriz[i][j].existe;

      return true;
}

static void grafo_DFS_rec(grafo_t *g, pila_t *p, int u, int v, int *array, char *visitados, int *len)
{
      for (int i = 0; i < g->n; i++) {
            if (grafo_existe_arista(g, u, i) && i == v) {
                  array[(*len)++] = i;
                  return;
            }

            if (grafo_existe_arista(g, u, i) && !visitados[i]) {
                  visitados[i]++;
                  int *apilar = malloc(sizeof(int));
                  *apilar = i;
                  pila_apilar(p, apilar);
            }
      }

      int *vertice = pila_desapilar(p);
      if (!vertice) {
            memset(array, 0, *len * sizeof(int));
            *len = 0;
            return;
      }

      int i = *vertice;
      free(vertice);

      if (*len >= g->n) {
            memset(array, 0, *len * sizeof(int));
            *len = 0;
            return;
      }

      array[(*len)++] = i;
      if (i == v) return;
      grafo_DFS_rec(g, p, i, v, array, visitados, len);
}

int *grafo_DFS(grafo_t *g, int u, int v, int *len)
{
      if (!g || !dentro_de_rango(g, u, v) || !len)
            return NULL;

      pila_t *p = pila_crear();
      int *array = malloc(pow(g->n, 2));
      char visitados[g->n * sizeof(char)];
      memset(visitados, 0, sizeof(visitados) * sizeof(char));
      *len = 1;
      array[0] = u;
      visitados[u] = 1;
      grafo_DFS_rec(g, p, u, v, array, visitados, len);
      pila_destruir_todo(p, free);
      return array;
}

static void grafo_BFS_rec(grafo_t *g, cola_t *c, int u, int v, int *array, char *visitados, int *len)
{
      for (int i = 0; i < g->n; i++) {
            if (grafo_existe_arista(g, u, i) && i == v) {
                  array[(*len)++] = i;
                  return;
            }

            if (grafo_existe_arista(g, u, i) && !visitados[i]) {
                  visitados[i]++;
                  int *encolar = malloc(sizeof(int));
                  *encolar = i;
                  cola_encolar(c, encolar);
            }
      }

      int *vertice = cola_desencolar(c);
      if (!vertice) {
            memset(array, 0, *len * sizeof(int));
            *len = 0;
            return;
      }

      int i = *vertice;
      free(vertice);

      array[(*len)++] = i;
      if (i == v) return;
      if (*len == pow(g->n, 2)) return;
      grafo_BFS_rec(g, c, i, v, array, visitados, len);
}

int *grafo_BFS(grafo_t *g, int u, int v, int *len)
{
      if (!g || !dentro_de_rango(g, u, v) || !len)
            return NULL;

      cola_t *c = cola_crear();
      int *array = malloc(pow(g->n, 2));
      char visitados[g->n * sizeof(char)];
      memset(visitados, 0, sizeof(visitados));
      *len = 1;
      array[0] = u;
      visitados[u] = 1;
      grafo_BFS_rec(g, c, u, v, array, visitados, len);
      cola_destruir_todo(c, free);
      return array;
}

static bool grafo_ciclo_rec(grafo_t *g, char visitados[], int v, int v0)
{
      visitados[v] = true;
      
      for (int i = 0; i < g->n; i++) {
            if (i != v0 && grafo_existe_arista(g, v, i) && visitados[i])
                  return true;
            
            if (grafo_existe_arista(g, v, i) && !visitados[i])
                  if (grafo_ciclo_rec(g, visitados, i, v))
                        return true;
      }

      return false;
}

static bool grafo_ciclo(grafo_t *g, int v0)
{
      char visitados[g->n * sizeof(char)];
      memset(visitados, 0, sizeof(visitados));
      return grafo_ciclo_rec(g, visitados, v0, v0);
}

typedef struct Arista {
      int u;
      int v;
      int peso;
} arista_t;

static int comparador_arista(void *a, void *b)
{
      return ((arista_t *)b)->peso - ((arista_t *)a)->peso;
}

static grafo_t *prim_rec(grafo_t *g, grafo_t *p, heap_t *h, char visitados[], int v0)
{
      visitados[v0] = 1;

      for (int i = 0; i < p->n; i++) {
            if (grafo_existe_arista(g, v0, i) && !visitados[i]) {
                  arista_t *a = malloc(sizeof(arista_t));
                  if (!a) {
                        grafo_destruir(p);
                        heap_destruir_todo(h, free);
                        return NULL;
                  }

                  a->u = v0;
                  a->v = i;
                  a->peso = grafo_peso_arista(g, i, v0);
                  heap_insertar(h, a);
            }
      }

      arista_t *arista = heap_quitar(h);
      grafo_agregar_arista(p, arista->u, arista->v, arista->peso);
      if (grafo_ciclo(p, arista->u))
            grafo_eliminar_arista(p, arista->u, arista->v);
      
      int proximo_vertice = arista->v;
      free(arista);
      
      if (p->m >= p->n - 1 || heap_vacio(h))
            return p;

      return prim_rec(g, p, h, visitados, proximo_vertice);
}

grafo_t *grafo_prim(grafo_t *g, int v0)
{
      if (!g || !dentro_de_rango(g, v0, v0))
            return NULL;

      grafo_t *p = grafo_crear(g->n);
      heap_t *h = heap_crear(comparador_arista, g->m);
      if (!p || !h) {
            grafo_destruir(p);
            heap_destruir(h);
            return NULL;
      }

      char visitados[p->n];
      memset(visitados, 0, sizeof(visitados));
      p = prim_rec(g, p, h, visitados, v0);
      heap_destruir_todo(h, free);
      return p;
}

grafo_t *grafo_kruskal(grafo_t *g)
{
      if (!g) return NULL;

      grafo_t *k = grafo_crear(g->n);
      heap_t *h = heap_crear(comparador_arista, g->m);
      if (!k || !h) {
            grafo_destruir(k);
            heap_destruir(h);
            return NULL;
      }

      for (int i = 0; i < g->n; i++)
            for (int j = 0; j < i; j++)
                  if (grafo_existe_arista(g, i, j)) {
                        arista_t *a = malloc(sizeof(arista_t));
                        if (!a) {
                              grafo_destruir(k);
                              heap_destruir_todo(h, free);
                              return NULL;
                        }

                        a->u = i;
                        a->v = j;
                        a->peso = g->matriz[i][j].peso;
                        heap_insertar(h, a);
                  }

      while (!heap_vacio(h) && k->m < k->n - 1) {
            arista_t *a = heap_quitar(h);
            if (!a) {
                  grafo_destruir(k);
                  heap_destruir_todo(h, free);
                  return NULL;
            }

            grafo_agregar_arista(k, a->u, a->v, a->peso);
            if (grafo_ciclo(k, a->u))
                  grafo_eliminar_arista(k, a->u, a->v);

            free(a);
      }

      heap_destruir_todo(h, free);
      return k;
}

static bool dijkstra(grafo_t *g, int u, int v, heap_t *h, char visitados[], int anterior[], float pesos[])
{
      if (u == v) return true;

      for (int i = 0; i < g->n; i++)
            if (grafo_existe_arista(g, u, i) && !visitados[i]) {
                  int peso_arista = grafo_peso_arista(g, u, i);
                  arista_t *arista = malloc(sizeof(arista_t));
                  if (!arista) return false;

                  arista->peso = peso_arista;
                  arista->u = u;
                  arista->v = i;
                  heap_insertar(h, arista);

                  if (peso_arista + pesos[u] < pesos[i]) {
                        pesos[i] = peso_arista + pesos[u];
                        anterior[i] = u;
                  }
            }

      if (heap_vacio(h))
            return false;
      
      visitados[u] = 1;
      arista_t *arista = heap_quitar(h);
      int proximo_vertice = arista->v;
      int peso = arista->peso + pesos[u];
      free(arista);

      dijkstra(g, proximo_vertice, v, h, visitados, anterior, pesos);
}

static bool conseguir_camino(int u, int v, pila_t *p, int anterior[])
{
      if (u == v) return true;

      int *n = malloc(sizeof(int));
      if (!n) return false;

      *n = anterior[v];
      pila_apilar(p, n);
      conseguir_camino(u, *n, p, anterior);
}

static void llenar_camino(pila_t *p, int *camino, int *len, int v)
{
      while (!pila_vacia(p)) {
            int *v = pila_desapilar(p);
            camino[(*len)++] = *v;
            free(v);
      }

      camino[(*len)++] = v;
}

int *grafo_dijkstra(grafo_t *g, int u, int v, int *len, int *coste)
{
      if (!g || !dentro_de_rango(g, u, v) || !len)
            return NULL;
      
      *len = 0;
      *coste = 0;
      int *camino = malloc(g->n * sizeof(int));
      heap_t *h = heap_crear(comparador_arista, g->m);
      if (!camino || !h) {
            free(camino);
            heap_destruir(h);
            return NULL;
      }

      char visitados[g->n];
      int anterior[g->n];
      float pesos[g->n];
      memset(visitados, 0, sizeof(visitados));
      for (int i = 0; i < g->n; i++) {
            anterior[i] = -1;
            pesos[i] = INFINITY;
      }

      pesos[u] = 0;
      if (!dijkstra(g, u, v, h, visitados, anterior, pesos)) {
            heap_destruir_todo(h, free);
            free(camino);
            return NULL;
      }

      heap_destruir_todo(h, free);
      pila_t *p = pila_crear();
      if (!conseguir_camino(u, v, p, anterior)) {
            pila_destruir_todo(p, free);
            free(camino);
            return NULL;
      }

      llenar_camino(p, camino, len, v);
      pila_destruir_todo(p, free);
      if (coste) *coste = pesos[v];
      return camino;
}

void grafo_destruir(grafo_t *g)
{
      if (!g) return;

      for (int i = 0; i < g->n; i++)
            free(g->matriz[i]);

      free(g->matriz);
      free(g);
}