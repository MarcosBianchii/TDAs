#include "src/vector.h"

void pruebas_vector_crear()
{
      vector_t *v = vector_crear(100);
      printf("v->data = %p\n", v->data);
      printf("v->tamanio = %zu\n", v->tamanio);
      printf("v->capacidad = %zu\n", v->capacidad);
      vector_destruir(v);
}

void pruebas_vector_agregar()
{
      vector_t *v = vector_crear(100);

      vector_agregar(v, "hola", 0);
      vector_agregar(v, "mundo", 1);
      vector_agregar(v, "!", 2);
      vector_agregar(v, "?", 3);
      vector_agregar(v, "...", 4);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_agregar(v, "1985", -11);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_obtener()
{
      vector_t *v = vector_crear(100);

      vector_agregar(v, "hola", 100);
      vector_agregar(v, "mundo", 100);
      vector_agregar(v, "!", 100);
      vector_agregar(v, "?", 100);
      vector_agregar(v, "...", 100);

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

void pruebas_vector_eliminar()
{
      vector_t * v = vector_crear(100);

      vector_agregar(v, "hola", 0);
      vector_agregar(v, "mundo", 1);
      vector_agregar(v, "!", 2);
      vector_agregar(v, "?", 3);
      vector_agregar(v, "...", 4);

      vector_eliminar(v, -1);

      for (int i = 0; i < v->tamanio; i++)
            printf("v->data[%d] = %s\n", i, (char *)v->data[i]);
      printf("\n\n");

      vector_destruir(v);
}

void pruebas_vector_cantidad()
{
      vector_t *v = vector_crear(100);

      vector_agregar(v, "hola", 0);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_agregar(v, "mundo", 1);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_agregar(v, "!", 2);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_agregar(v, "?", 3);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_agregar(v, "...", 4);
      printf("v->tamanio = %zu\n", vector_cantidad(v));

      vector_eliminar(v, 2);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_eliminar(v, 2);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_eliminar(v, 2);
      printf("v->tamanio = %zu\n", vector_cantidad(v));
      vector_eliminar(v, 2);
      printf("v->tamanio = %zu\n", vector_cantidad(v));

      vector_destruir(v);
}

void pruebas_vector_vacio()
{
      vector_t *v = vector_crear(100);
      
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");
      vector_agregar(v, "hola", 0);
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");
      vector_eliminar(v, 0);
      printf("vector_vacio(v) = %s\n", vector_vacio(v) ? "true" : "false");

      vector_destruir(v);
}

int main()
{
      // pruebas_vector_crear();
      // pruebas_vector_agregar();
      // pruebas_vector_obtener();
      // pruebas_vector_eliminar();
      // pruebas_vector_cantidad();
      // pruebas_vector_vacio();

      return 0;
}