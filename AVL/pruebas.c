#include "src/avl.h"
#include "string.h"

int comparador(void *i, void *j) {
      if (!i && !j) return 0;

      if (!i) return -1;
      if (!j) return 1;

      return *(int *)i - *(int *)j;
}

int comparador_str(void *i, void *j) {
      return strlen((char *)i) - strlen((char *)j);
}

void pruebas_avl_crear() {
      avl_t *avl = avl_crear(comparador_str);
      printf("avl_t *avl = %p\n", avl);
      avl_t *null = avl_crear(NULL);
      printf("avl_t *null = %p\n", null);
      printf("\n");
      avl_destruir(avl);
}

void pruebas_avl_insertar() {
      avl_t *avl = avl_crear(comparador_str);
      printf("El arbol esta vacio = %s\n", avl_vacio(avl) ? "true" : "false");
      avl_insertar(avl, "hola");
      printf("El tamanio es = %li\n", avl_tamanio(avl));
      avl_insertar(avl, "aaaaaaa");
      printf("El tamanio es = %li\n", avl_tamanio(avl));
      printf("El arbol esta vacio = %s\n", avl_vacio(avl) ? "true" : "false");
      printf("\n");
      avl_destruir(avl);
}

void pruebas_avl_quitar() {
      avl_t *avl = avl_crear(comparador_str);
      int i = 0; avl_insertar(avl, &i);
      int j = 0; avl_insertar(avl, &j);
      int k = 0; avl_insertar(avl, &k);

      printf("El tamanio es = %li\n", avl_tamanio(avl));
      printf("El arbol esta vacio = %s\n", avl_vacio(avl) ? "true" : "false");
      int *elemento = avl_quitar(avl, &i);
      printf("El tamanio es = %li\n", avl_tamanio(avl));
      printf("El arbol esta vacio = %s\n", avl_vacio(avl) ? "true" : "false");
      printf("El elemento es = %i\n", *elemento);
      elemento = avl_quitar(avl, &i);
      elemento = avl_quitar(avl, &i);
      elemento = avl_quitar(avl, &i);
      elemento = avl_quitar(avl, &i);
      elemento = avl_quitar(avl, &i);
      elemento = avl_quitar(avl, &i);
      printf("\n");
      avl_destruir(avl);
}

void pruebas_avl_buscar() {
      avl_t *avl = avl_crear(comparador);
      int i = 0; avl_insertar(avl, &i);
      int j = 1; avl_insertar(avl, &j);
      int k = 2; avl_insertar(avl, &k);
      printf("valor = %i\n", *(int *)avl_buscar(avl, &i));
      printf("valor = %i\n", *(int *)avl_buscar(avl, &j));
      printf("valor = %i\n", *(int *)avl_buscar(avl, &k));
      printf("valor = %p\n", avl_buscar(avl, NULL));
      avl_destruir(avl);
}

int main() {
      pruebas_avl_crear();
      pruebas_avl_insertar();
      pruebas_avl_quitar();
      pruebas_avl_buscar();

      return 0;
}