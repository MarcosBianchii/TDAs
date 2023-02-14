#include "src/heap.h"

int comparador(void *a, void *b)
{
      return *(int *)a - *(int *)b;
}

void pruebas_heap_crear()
{
      heap_t *h = heap_crear(comparador, 10);
      heap_t *i = heap_crear(NULL, 10);

      printf("*h: %p\n", h);
      printf("*i: %p\n", i);

      heap_destruir(h);
      heap_destruir(i);
}

void pruebas_heap_insertar()
{
      heap_t *h = heap_crear(comparador, 10);

      int n = 10;
      printf("1: %p\n", heap_insertar(h, &n));

      int *m = malloc(sizeof(int));
      *m = 69;
      
      heap_t *i = heap_crear(comparador, 10);
      printf("2: %p\n", heap_insertar(i, m));

      heap_destruir(h);
      heap_destruir_todo(i, free);
}

void pruebas_heap_quitar()
{
      heap_t *h = heap_crear(comparador, 10);
      int n = 10; heap_insertar(h, &n);
      int m = 20; heap_insertar(h, &m);
      int o = 30; heap_insertar(h, &o);
      int p = 40; heap_insertar(h, &p);
      int q = 50; heap_insertar(h, &q);
      int r = 60; heap_insertar(h, &r);

      printf("1: %i\n", *(int *)heap_quitar(h));
      printf("2: %i\n", *(int *)heap_quitar(h));
      printf("3: %i\n", *(int *)heap_quitar(h));
      printf("4: %i\n", *(int *)heap_quitar(h));
      printf("5: %i\n", *(int *)heap_quitar(h));
      printf("6: %i\n", *(int *)heap_quitar(h));

      heap_destruir(h);
}

void pruebas_heap_tamanio()
{
      heap_t *h = heap_crear(comparador, 10);
      int n = 10; heap_insertar(h, &n);
      printf("1 = %i\n", heap_tamanio(h));
      int m = 20; heap_insertar(h, &m);
      printf("2 = %i\n", heap_tamanio(h));
      int o = 30; heap_insertar(h, &o);
      printf("3 = %i\n", heap_tamanio(h));
      int p = 40; heap_insertar(h, &p);
      printf("4 = %i\n", heap_tamanio(h));
      int q = 50; heap_insertar(h, &q);
      printf("5 = %i\n", heap_tamanio(h));
      int r = 60; heap_insertar(h, &r);
      printf("6 = %i\n", heap_tamanio(h));
      int s = 70; heap_insertar(h, &s);
      printf("7 = %i\n", heap_tamanio(h));
      int t = 80; heap_insertar(h, &t);
      printf("8 = %i\n", heap_tamanio(h));
      int u = 90; heap_insertar(h, &u);
      printf("9 = %i\n", heap_tamanio(h));
      int v = 100;heap_insertar(h, &v);
      printf("10 = %i\n", heap_tamanio(h));

      heap_destruir(h);
}

void pruebas_heapsort()
{
      int tope = 10;
      void **vector = malloc(sizeof(void *) * tope);

      int n = 100;vector[0] = &n;
      int m = 90; vector[1] = &m;
      int o = 80; vector[2] = &o;
      int p = 70; vector[3] = &p;
      int q = 60; vector[4] = &q;
      int r = 50; vector[5] = &r;
      int s = 40; vector[6] = &s;
      int t = 30; vector[7] = &t;
      int u = 20; vector[8] = &u;
      int v = 10; vector[9] = &v;

      printf("Vector:\n");
      for (int i = 0; i < tope; i++)
            printf("%i: %i\n", i, *(int *)vector[i]);

      printf("\nHeapsort:\n");
      heapsort(vector, comparador, tope);
      for (int i = 0; i < tope; i++)
            printf("%i: %i\n", i, *(int *)vector[i]);

      free(vector);
}

int main()
{
      pruebas_heap_crear();
      pruebas_heap_insertar();
      pruebas_heap_quitar();
      pruebas_heap_tamanio();
      pruebas_heapsort();

      return 0;
}