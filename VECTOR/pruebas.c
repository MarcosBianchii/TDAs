#include "src/vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
      void **data;
      size_t tamanio;
      size_t capacidad;
} vector_t;

void pruebas_vector_crear()
{
      vector_t *v = vector_crear(100);
      printf("v->data = %p\n", v->data);
      printf("v->tamanio = %zu\n", v->tamanio);
      printf("v->capacidad = %zu\n", v->capacidad);
      vector_destruir(v);
}

void pruebas_vector_agregar_en()
{
      vector_t *v = vector_crear(100);

      vector_agregar_en(v, "hola", 0);
      vector_agregar_en(v, "mundo", 1);
      vector_agregar_en(v, "!", 2);
      vector_agregar_en(v, "?", 3);
      vector_agregar_en(v, "...", 4);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_agregar_en(v, "1985", -11);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_obtener()
{
      vector_t *v = vector_crear(100);

      vector_agregar_en(v, "hola", 100);
      vector_agregar_en(v, "mundo", 100);
      vector_agregar_en(v, "!", 100);
      vector_agregar_en(v, "?", 100);
      vector_agregar_en(v, "...", 100);

      printf("v->data[%d] = %s\n", 0, (char *)vector_obtener(v, 0));
      printf("v->data[%d] = %s\n", 1, (char *)vector_obtener(v, 1));
      printf("v->data[%d] = %s\n", 2, (char *)vector_obtener(v, 2));
      printf("v->data[%d] = %s\n", 3, (char *)vector_obtener(v, 3));
      printf("v->data[%d] = %s\n", 4, (char *)vector_obtener(v, 4));

      printf("v->data[%d] = %s\n", -1, (char *)vector_obtener(v, -1));
      printf("v->data[%d] = %s\n", -2, (char *)vector_obtener(v, 1000));

      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_eliminar_en()
{
      vector_t * v = vector_crear(100);

      vector_agregar_en(v, "hola", 0);
      vector_agregar_en(v, "mundo", 1);
      vector_agregar_en(v, "!", 2);
      vector_agregar_en(v, "?", 3);
      vector_agregar_en(v, "...", 4);

      vector_eliminar_en(v, -1);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_tamanio()
{
      vector_t *v = vector_crear(100);

      vector_agregar_en(v, "hola", 0);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_agregar_en(v, "mundo", 1);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_agregar_en(v, "!", 2);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_agregar_en(v, "?", 3);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_agregar_en(v, "...", 4);
      printf("v->tamanio = %zu\n", vector_tamanio(v));

      vector_eliminar_en(v, 2);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_eliminar_en(v, 2);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_eliminar_en(v, 2);
      printf("v->tamanio = %zu\n", vector_tamanio(v));
      vector_eliminar_en(v, 2);
      printf("v->tamanio = %zu\n", vector_tamanio(v));

      vector_destruir(v);
}

void pruebas_vector_vacio()
{
      vector_t *v = vector_crear(100);
      
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");
      vector_agregar_en(v, "hola", 0);
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");
      vector_eliminar_en(v, 0);
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");

      vector_destruir(v);
}

void pruebas_vector_push()
{
      vector_t *v = vector_crear(10);

      vector_push(v, "hola");
      vector_push(v, "mundo");
      vector_push(v, "!");
      vector_push(v, "?");
      vector_push(v, "...");

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_pop()
{
      vector_t *v = vector_crear(10);

      vector_push(v, "hola");
      vector_push(v, "mundo");
      vector_push(v, "!");
      vector_push(v, "?");
      vector_push(v, "...");

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));
      printf("vector_pop(v) = %s\n", (char *)vector_pop(v));

      vector_destruir(v);
}

int main()
{
      // pruebas_vector_crear();
      // pruebas_vector_agregar_en();
      // pruebas_vector_obtener();
      // pruebas_vector_eliminar_en();
      // pruebas_vector_tamanio();
      // pruebas_vector_vacio();
      // pruebas_vector_push();
      // pruebas_vector_pop();
      return 0;
}