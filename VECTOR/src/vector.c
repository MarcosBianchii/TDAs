#include "vector.h"

vector_t *vector_crear(int capacidad)
{
      if (capacidad < 10) capacidad = 10;

      vector_t *v = malloc(sizeof(vector_t));
      if (!v) return NULL;

      v->data = malloc(capacidad * sizeof(void *));
      if (!v->data) {
            free(v);
            return NULL;
      }

      v->capacidad = capacidad;
      v->tamanio = 0;
      return v;
}

// Duplica la capacidad del vector;
static vector_t *vector_agrandar(vector_t *v)
{
      size_t nueva_capacidad = v->capacidad * 2;
      void *nueva_data = realloc(v->data, nueva_capacidad * sizeof(void *));
      if (!nueva_data) return NULL;

      v->data = nueva_data;
      v->capacidad = nueva_capacidad;
      return v;
}

vector_t *vector_agregar_en(vector_t *v, void *elemento, int posicion)
{
      if (!v) return NULL;

      if (v->tamanio == v->capacidad)
            if (!vector_agrandar(v))
                  return NULL;

      if (posicion < 0) posicion = 0;
      if (posicion > v->tamanio) posicion = v->tamanio;

      for (int i = v->tamanio++; i > posicion; i--)
            v->data[i] = v->data[i-1];
      
      v->data[posicion] = elemento;
      return v;
}

void *vector_obtener(vector_t *v, int posicion)
{
      if (!v || vector_vacio(v)) return NULL;

      if (posicion < 0) posicion = 0;
      if (posicion >= v->tamanio) posicion = v->tamanio - 1;

      return v->data[posicion];
}

void *vector_eliminar_en(vector_t *v, int posicion)
{
      if (!v || vector_vacio(v)) return NULL;

      if (posicion < 0) posicion = 0;
      if (posicion >= v->tamanio) posicion = v->tamanio - 1;

      void *elemento = v->data[posicion];
      v->tamanio--;

      for (int i = posicion; i < v->tamanio; i++)
            v->data[i] = v->data[i+1];
      
      return elemento;
}

vector_t *vector_push(vector_t *v, void *elemento)
{
      return vector_agregar_en(v, elemento, v->tamanio);
}

void *vector_pop(vector_t *v)
{
      return vector_eliminar_en(v, v->tamanio - 1);
}

size_t vector_tamanio(vector_t *v)
{
      if (!v) return 0;
      return v->tamanio;
}

bool vector_vacio(vector_t *v)
{
      if (!v) return true;
      return v->tamanio == 0;
}

void vector_destruir(vector_t *v)
{
      vector_destruir_todo(v, NULL);
}

void vector_destruir_todo(vector_t *v, void (*f)(void *))
{
      if (!v) return;

      if (f)
            for (int i = 0; i < v->tamanio; i++)
                  f(v->data[i]);

      free(v->data);
      free(v);
}