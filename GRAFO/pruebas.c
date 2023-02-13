#include "src/grafo.h"

static void print_menu(char *str)
{
      printf(AMARILLO"\n%s:\n"BLANCO, str);
}

void prueba_grafo_crear()
{
      print_menu("Prueba grafo_crear()");

      grafo_t *g = grafo_crear(10);
      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo_agregar_arista()
{
      print_menu("Prueba grafo_agregar_arista()");

      grafo_t *g = grafo_crear(10);

      grafo_agregar_arista(g, 1, 6, 1);
      grafo_agregar_arista(g, 2, 8, 2);
      grafo_agregar_arista(g, 3, 11, 3);
      grafo_agregar_arista(g, 4, 2, 4);

      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo_eliminar_arista()
{
      print_menu("Prueba grafo_eliminar_arista()");

      grafo_t *g = grafo_crear(10);

      grafo_agregar_arista(g, 1, 6, 1);
      grafo_agregar_arista(g, 2, 8, 2);
      grafo_agregar_arista(g, 3, 11, 3);
      grafo_agregar_arista(g, 4, 2, 4);

      grafo_imprimir(g);

      grafo_eliminar_arista(g, 1, 6);
      grafo_eliminar_arista(g, 2, 8);
      grafo_eliminar_arista(g, 3, 11);
      grafo_eliminar_arista(g, 4, 2);

      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo_existe_arista()
{
      print_menu("Prueba grafo_existe_arista()");

      grafo_t *g = grafo_crear(5);

      grafo_agregar_arista(g, 0, 4, 1);
      grafo_agregar_arista(g, 1, 4, 2);
      grafo_agregar_arista(g, 2, 3, 3);
      grafo_agregar_arista(g, 3, 2, 4);

      bool p1 = grafo_existe_arista(g, 0, 4);
      bool p2 = grafo_existe_arista(g, 1, 4);
      bool p3 = grafo_existe_arista(g, 2, 2);
      bool p4 = grafo_existe_arista(g, 3, 2);

      printf("\n\
P1(0,4): %s\n\
P2(1,4): %s\n\
P3(2,2): %s\n\
P4(3,2): %s\n",
p1 ? VERDE"true"BLANCO : ROJO"false"BLANCO,
p2 ? VERDE"true"BLANCO : ROJO"false"BLANCO,
p3 ? VERDE"true"BLANCO : ROJO"false"BLANCO,
p4 ? VERDE"true"BLANCO : ROJO"false"BLANCO);

      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo_peso_arista()
{
      print_menu("Prueba grafo_peso_arista()");

      grafo_t *g = grafo_crear(5);
      grafo_agregar_arista(g, 0, 5, 1);
      grafo_agregar_arista(g, 1, 4, 2);
      grafo_agregar_arista(g, 2, 3, 3);
      grafo_agregar_arista(g, 3, 2, 4);

      printf("%i(0, 5) | %i(1, 4) | %i(1, 2)\n",
            grafo_peso_arista(g, 0, 5),
            grafo_peso_arista(g, 1, 4),
            grafo_peso_arista(g, 1, 2));

      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo()
{
      print_menu("Prueba grafo()");

      grafo_t *g = grafo_crear(5);

      grafo_agregar_arista(g, 0, 4, 1);
      grafo_imprimir(g);
      printf("g-1: %i\n", grafo_peso_arista(g, 0, 4));

      grafo_agregar_arista(g, 4, 0, 2);
      grafo_imprimir(g);
      printf("g-2: %i\n", grafo_peso_arista(g, 4, 0));

      grafo_destruir(g);
}

void prueba_grafo_imprimir()
{
      print_menu("Prueba grafo_imprimir()");

      grafo_t *g = grafo_crear(10);

      grafo_agregar_arista(g, 0, 4, 1);
      grafo_agregar_arista(g, 1, 4, 2);
      grafo_agregar_arista(g, 2, 3, 3);
      grafo_agregar_arista(g, 3, 2, 20);

      grafo_imprimir(g);
      grafo_destruir(g);
}

void prueba_grafo_complementar()
{
      print_menu("Prueba grafo_complementar()");

      grafo_t *g = grafo_crear(5);

      grafo_agregar_arista(g, 0, 4, 1);
      grafo_agregar_arista(g, 1, 4, 2);
      grafo_agregar_arista(g, 2, 3, 3);
      grafo_agregar_arista(g, 3, 2, 4);

      grafo_imprimir(g);

      grafo_t *c = grafo_complementar(g);

      grafo_imprimir(c);

      grafo_destruir(g);
      grafo_destruir(c);
}

void prueba_grafo_DFS()
{
      print_menu("Prueba grafo_DFS()");

      grafo_t *g = grafo_crear(13);

      grafo_agregar_arista(g, 0, 1, 1);
      grafo_agregar_arista(g, 0, 4, 7);
      grafo_agregar_arista(g, 1, 2, 6);
      grafo_agregar_arista(g, 1, 6, 8);
      grafo_agregar_arista(g, 2, 3, 21);
      grafo_agregar_arista(g, 2, 6, 2);
      grafo_agregar_arista(g, 2, 7, 3);
      grafo_agregar_arista(g, 2, 8, 9);
      grafo_agregar_arista(g, 3, 4, 4);
      grafo_agregar_arista(g, 3, 8, 3);
      grafo_agregar_arista(g, 4, 9, 3);
      grafo_agregar_arista(g, 4, 5, 15);
      grafo_agregar_arista(g, 5, 9, 10);
      grafo_agregar_arista(g, 5, 12, 7);
      grafo_agregar_arista(g, 6, 7, 3);
      grafo_agregar_arista(g, 6, 10, 21);
      grafo_agregar_arista(g, 7, 10, 18);
      grafo_agregar_arista(g, 7, 11, 4);
      grafo_agregar_arista(g, 7, 8, 9);
      grafo_agregar_arista(g, 8, 9, 1);
      grafo_agregar_arista(g, 8, 11, 12);
      grafo_agregar_arista(g, 8, 12, 14);
      grafo_agregar_arista(g, 9, 12, 5);
      grafo_agregar_arista(g, 10, 11, 11);
      grafo_agregar_arista(g, 11, 12, 19);
      grafo_imprimir(g);

      int len = 0;
      int v0 = 0;
      int v1 = 2;
      int *camino = grafo_DFS(g, v0, v1, &len);

      printf("camino (%i-%i): ", v0, v1);
      for (int i = 0; i < len; i++)
            printf("%i ", camino[i]);
      printf("\n");

      free(camino);
      grafo_destruir(g);
}

void prueba_grafo_BFS()
{
      print_menu("Prueba grafo_BFS()");

      grafo_t *g = grafo_crear(10);

      grafo_agregar_arista(g, 0, 1, 5);
      grafo_agregar_arista(g, 0, 4, 5);
      grafo_agregar_arista(g, 1, 2, 5);
      grafo_agregar_arista(g, 1, 4, 5);
      grafo_agregar_arista(g, 1, 5, 5);
      grafo_agregar_arista(g, 2, 3, 5);
      grafo_agregar_arista(g, 2, 5, 5);
      grafo_agregar_arista(g, 2, 6, 5);
      grafo_agregar_arista(g, 3, 6, 5);
      grafo_agregar_arista(g, 4, 7, 5);
      grafo_agregar_arista(g, 5, 7, 5);
      grafo_agregar_arista(g, 5, 8, 5);
      grafo_agregar_arista(g, 6, 8, 5);
      grafo_agregar_arista(g, 7, 9, 5);
      grafo_agregar_arista(g, 8, 9, 5);

      grafo_imprimir(g);

      int len = 0;
      int v0 = 0;
      int v1 = 9;
      int *camino = grafo_BFS(g, v0, v1, &len);

      printf("camino (%i-%i): ", v0, v1);
      for (int i = 0; i < len; i++)
            printf("%i ", camino[i]);
      printf("\n");

      free(camino);
      grafo_destruir(g);
}

void prueba_grafo_kruskal()
{
      print_menu("Prueba grafo_kruskal()");

      grafo_t *g = grafo_crear(13);
      grafo_agregar_arista(g, 0, 1, 1);
      grafo_agregar_arista(g, 0, 4, 7);
      grafo_agregar_arista(g, 1, 2, 6);
      grafo_agregar_arista(g, 1, 6, 8);
      grafo_agregar_arista(g, 2, 3, 21);
      grafo_agregar_arista(g, 2, 6, 2);
      grafo_agregar_arista(g, 2, 7, 3);
      grafo_agregar_arista(g, 2, 8, 9);
      grafo_agregar_arista(g, 3, 4, 4);
      grafo_agregar_arista(g, 3, 8, 3);
      grafo_agregar_arista(g, 4, 9, 3);
      grafo_agregar_arista(g, 4, 5, 15);
      grafo_agregar_arista(g, 5, 9, 10);
      grafo_agregar_arista(g, 5, 12, 7);
      grafo_agregar_arista(g, 6, 7, 3);
      grafo_agregar_arista(g, 6, 10, 21);
      grafo_agregar_arista(g, 7, 10, 18);
      grafo_agregar_arista(g, 7, 11, 4);
      grafo_agregar_arista(g, 7, 8, 9);
      grafo_agregar_arista(g, 8, 9, 1);
      grafo_agregar_arista(g, 8, 11, 12);
      grafo_agregar_arista(g, 8, 12, 14);
      grafo_agregar_arista(g, 9, 12, 5);
      grafo_agregar_arista(g, 10, 11, 11);
      grafo_agregar_arista(g, 11, 12, 19);

      grafo_imprimir(g);

      grafo_t *k = grafo_kruskal(g);
      grafo_destruir(g);

      grafo_imprimir(k);
      grafo_destruir(k);
}

void prueba_grafo_prim()
{
      print_menu("Prueba grafo_prim()");

      grafo_t *g = grafo_crear(13);
      grafo_agregar_arista(g, 0, 1, 1);
      grafo_agregar_arista(g, 0, 4, 7);
      grafo_agregar_arista(g, 1, 2, 6);
      grafo_agregar_arista(g, 1, 6, 8);
      grafo_agregar_arista(g, 2, 3, 21);
      grafo_agregar_arista(g, 2, 6, 2);
      grafo_agregar_arista(g, 2, 7, 3);
      grafo_agregar_arista(g, 2, 8, 9);
      grafo_agregar_arista(g, 3, 4, 4);
      grafo_agregar_arista(g, 3, 8, 3);
      grafo_agregar_arista(g, 4, 9, 3);
      grafo_agregar_arista(g, 4, 5, 15);
      grafo_agregar_arista(g, 5, 9, 10);
      grafo_agregar_arista(g, 5, 12, 7);
      grafo_agregar_arista(g, 6, 7, 3);
      grafo_agregar_arista(g, 6, 10, 21);
      grafo_agregar_arista(g, 7, 10, 18);
      grafo_agregar_arista(g, 7, 11, 4);
      grafo_agregar_arista(g, 7, 8, 9);
      grafo_agregar_arista(g, 8, 9, 1);
      grafo_agregar_arista(g, 8, 11, 12);
      grafo_agregar_arista(g, 8, 12, 14);
      grafo_agregar_arista(g, 9, 12, 5);
      grafo_agregar_arista(g, 10, 11, 11);
      grafo_agregar_arista(g, 11, 12, 19);

      grafo_t *p = grafo_prim(g, 0);
      grafo_destruir(g);
      
      grafo_imprimir(p);
      grafo_destruir(p);
}

void prueba_grafo_dijkstra()
{
      print_menu("Prueba grafo_dijkstra()");

      grafo_t *g = grafo_crear(6);
      // grafo_agregar_arista(g, 0, 1, 2);
      // grafo_agregar_arista(g, 0, 2, 5);
      // grafo_agregar_arista(g, 0, 3, 4);
      // grafo_agregar_arista(g, 1, 2, 2);
      // grafo_agregar_arista(g, 1, 4, 7);
      // grafo_agregar_arista(g, 2, 3, 1);
      // grafo_agregar_arista(g, 2, 4, 4);
      // grafo_agregar_arista(g, 2, 5, 3);
      // grafo_agregar_arista(g, 3, 5, 4);
      // grafo_agregar_arista(g, 4, 5, 1);
      // grafo_agregar_arista(g, 4, 6, 5);
      // grafo_agregar_arista(g, 5, 6, 7);

// GRAFO NO CONEXO
      // grafo_agregar_arista(g, 0, 1, 1);
      // grafo_agregar_arista(g, 1, 2, 2);
      // grafo_agregar_arista(g, 2, 3, 3);
      // grafo_agregar_arista(g, 3, 4, 4);
      // grafo_agregar_arista(g, 4, 5, 5);
      // grafo_agregar_arista(g, 5, 0, 0);

      grafo_agregar_arista(g, 0, 2, 1);
      grafo_agregar_arista(g, 0, 1, 2);
      grafo_agregar_arista(g, 1, 3, 3);
      grafo_agregar_arista(g, 3, 4, 4);
      grafo_agregar_arista(g, 3, 5, 5);
      grafo_agregar_arista(g, 2, 4, 0);



      grafo_imprimir(g);

      int len = 0, coste = 0, u = 0, v = 5;
      int *dist = grafo_dijkstra(g, u, v, &len, &coste);

      if (dist) {
            printf("Distancias desde %i a %i con un coste de %i\n > ", u, v, coste);
            for (int i = 0; i < len; i++)
                  printf("%d ", dist[i]);
            printf("\n");
            free(dist);
      } else printf("No hay camino entre %i y %i\n", u, v);

      grafo_destruir(g);
}

int main()
{
      // prueba_grafo_crear();
      // prueba_grafo_agregar_arista();
      // prueba_grafo_eliminar_arista();
      // prueba_grafo_existe_arista();
      // prueba_grafo_peso_arista();
      // prueba_grafo();
      // prueba_grafo_imprimir();
      // prueba_grafo_complementar();
      // prueba_grafo_DFS();
      // prueba_grafo_BFS();
      // prueba_grafo_kruskal();
      // prueba_grafo_prim();
      prueba_grafo_dijkstra();
      return 0;
}