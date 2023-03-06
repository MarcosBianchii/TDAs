#include "src/digrafo.h"

static void print_menu(char *str)
{
      printf(AMARILLO"\n%s:\n"BLANCO, str);
}

void pruebas_digrafo_crear()
{
      print_menu("Pruebas de digrafo_crear()");
      printf("\n");

      digrafo_t *d = digrafo_crear(-1);
      digrafo_imprimir(d);

      digrafo_t *e = digrafo_crear(0);
      digrafo_imprimir(e);

      digrafo_t *f = digrafo_crear(10);
      digrafo_imprimir(f);

      digrafo_destruir(d);
}

void pruebas_digrafo_agregar_arista()
{
      print_menu("Pruebas de digrafo_agregar_arista()");

      digrafo_t *d = digrafo_crear(5);
      digrafo_agregar_arista(d, 0, 1, 1);
      digrafo_agregar_arista(d, 0, 2, 2);
      digrafo_agregar_arista(d, 1, 2, 5);
      digrafo_agregar_arista(d, 1, 3, 6);
      digrafo_agregar_arista(d, 1, 4, 7);
      digrafo_agregar_arista(d, 2, 3, 8);
      digrafo_agregar_arista(d, 2, 4, 9);
      digrafo_agregar_arista(d, 3, 4, 10);

      digrafo_agregar_arista(d, 5, 6, 11);
      digrafo_agregar_arista(d, 4, 10, 12);
      digrafo_agregar_arista(d, 20, 2, 13);

      digrafo_imprimir(d);
      digrafo_destruir(d);
}

void pruebas_digrafo_existe_arista()
{
      print_menu("Pruebas de digrafo_existe_arista()");
      printf("\n");

      digrafo_t *d = digrafo_crear(5);
      digrafo_agregar_arista(d, 0, 1, 1);
      digrafo_agregar_arista(d, 0, 2, 2);
      digrafo_agregar_arista(d, 1, 2, 5);
      digrafo_agregar_arista(d, 1, 3, 6);

      printf("%s\n"BLANCO, digrafo_existe_arista(d, 0, 1) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 0, 2) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 1, 2) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 1, 3) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 1, 4) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 2, 3) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 2, 4) ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_existe_arista(d, 9, 9) ? VERDE"true" : ROJO"false");

      digrafo_destruir(d);
}

void pruebas_digrafo_borrar_arista()
{
      print_menu("Pruebas de digrafo_borrar_arista()");

      digrafo_t *d = digrafo_crear(5);

      digrafo_agregar_arista(d, 0, 1, 1);
      digrafo_agregar_arista(d, 0, 2, 2);
      digrafo_agregar_arista(d, 1, 2, 5);
      digrafo_agregar_arista(d, 1, 3, 6);
      digrafo_imprimir(d);

      digrafo_borrar_arista(d, 0, 1);
      digrafo_borrar_arista(d, 0, 2);
      digrafo_borrar_arista(d, 1, 7);
      digrafo_borrar_arista(d, 1, 4);
      digrafo_imprimir(d);

      digrafo_destruir(d);
}

void pruebas_digrafo_peso_arista()
{
      print_menu("Pruebas de digrafo_peso_arista()");

      digrafo_t *d = digrafo_crear(5);

      digrafo_agregar_arista(d, 0, 1, 1);
      digrafo_agregar_arista(d, 0, 2, 2);
      digrafo_agregar_arista(d, 1, 2, 5);
      digrafo_agregar_arista(d, 1, 3, 6);
      digrafo_imprimir(d);

      printf("%s\n"BLANCO, digrafo_peso_arista(d, 0, 1) ==  1 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 0, 2) ==  2 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 1, 2) ==  5 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 1, 3) ==  6 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 1, 4) == -1 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 2, 3) == -1 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 2, 4) == -1 ? VERDE"true" : ROJO"false");
      printf("%s\n"BLANCO, digrafo_peso_arista(d, 9, 9) == -1 ? VERDE"true" : ROJO"false");

      printf("\n");
      digrafo_destruir(d);
}

int main()
{
      pruebas_digrafo_crear();
      pruebas_digrafo_agregar_arista();
      pruebas_digrafo_existe_arista();
      pruebas_digrafo_borrar_arista();
      pruebas_digrafo_peso_arista();
      return 0;
}