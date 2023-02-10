#include "digrafo.h"

digrafo_t *digrafo_crear(int n)
{
      if (n < 1) return NULL;

      digrafo_t *d = malloc(sizeof(digrafo_t));
      if (!d) return NULL;

      d->lista = calloc(n, sizeof(nodo_t *));
      if (!d->lista) {
            free(d);
            return NULL;
      }

      d->n = n;
      d->m = 0;

      return d;
}

//    Devuelve true si la posicion en la lista existe.
static bool dentro_de_rango(digrafo_t *d, int a, int b)
{
      return a >= 0 && a < d->n && b >= 0 && b < d->n;
}

digrafo_t *digrafo_agregar_arista(digrafo_t *d, int v1, int v2, int peso)
{
      if (!d || !dentro_de_rango(d, v1, v2))
            return NULL;

      nodo_t *nuevo = malloc(sizeof(nodo_t));
      if (!nuevo) return NULL;

      nuevo->peso = peso;
      nuevo->vertice = v2;
      nuevo->siguiente = d->lista[v1];
      d->lista[v1] = nuevo;
      d->m++;

      return d;
}

//    Elimina un nodo de la lista de nodos.
static nodo_t *search_and_destroy(nodo_t *actual, int v0, int *peso)
{
      if (!actual) return NULL;

      if (actual->vertice == v0) {
            nodo_t *aux = actual->siguiente;
            *peso = actual->peso;
            free(actual);
            return aux;
      }

      actual->siguiente = search_and_destroy(actual->siguiente, v0, peso);
      return actual;
}

int digrafo_borrar_arista(digrafo_t *d, int v1, int v2)
{
      if (!d || !dentro_de_rango(d, v1, v2))
            return -1;

      int peso = -1;
      d->lista[v1] = search_and_destroy(d->lista[v1], v2, &peso);
      if (peso != -1) d->m--;
      return peso;
}

//    Itera la lista de adyacencia aplicando
//    una funciona cada nodo.
static int iterar_lista(nodo_t *nodo, int v0, void (*f)(void *))
{
      if (!nodo) return -1;

      if (nodo->vertice == v0)
            return nodo->peso;

      nodo_t *siguiente = nodo->siguiente;
      if (f) f(nodo);

      return iterar_lista(siguiente, v0, f);
}

bool digrafo_existe_arista(digrafo_t *d, int v1, int v2)
{
      if (!d || !dentro_de_rango(d, v1, v2))
            return false;

      if (iterar_lista(d->lista[v1], v2, NULL) < 0)
            return false;
      else  return true;
}

int digrafo_peso_arista(digrafo_t *d, int v1, int v2)
{
      if (!d || !dentro_de_rango(d, v1, v2))
            return -1;

      return iterar_lista(d->lista[v1], v2, NULL);
}

int digrafo_tamanio(digrafo_t *d)
{
      if (!d) return 0;
      return d->m;
}

//    Imprime un nodo por pantalla.
static void imprimir_nodo(void *n)
{
      nodo_t *nodo = n;

      printf(NEGRO"("AMARILLO"%i"NEGRO", "AMARILLO"%i"NEGRO")", nodo->vertice, nodo->peso);
      if (nodo->siguiente) printf(NEGRO" -> ");
}

void digrafo_imprimir(digrafo_t *d)
{
      if (!d) {
            printf(ROJO"El Digrafo es NULL\n"BLANCO);
            return;
      }

      printf("\nDigrafo:\n");
      for (int i = 0; i < d->n; i++) {
            printf(AMARILLO"%d"NEGRO": "BLANCO, i);
            iterar_lista(d->lista[i], -1, imprimir_nodo);
            printf("\n");
      }

      printf("\nn: %i | m: %i\n\n", d->n, d->m);
}

void digrafo_destruir(digrafo_t *d)
{
      if (!d) return;

      for (int i = 0; i < d->n; i++)
            iterar_lista(d->lista[i], -1, free);

      free(d->lista);
      free(d);
}