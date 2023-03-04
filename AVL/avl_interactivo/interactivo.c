#include "mostrar_avl.h"
#include "avl.h"
#include <stdio.h>
#include <ctype.h>

void formatear_int(void* _nodo){
  nodo_t* nodo = _nodo;
  int i = *(int*)nodo->valor;
  printf("%2d", i);
}

int comparar_int(void* _i1, void* _i2){
  int* i1=_i1;
  int* i2=_i2;
  return *i1-*i2;
}

void destruir_int(void* i){
  free(i);
}

int main(int argc, char* argv[]){
  avl_t* avl = avl_crear(comparar_int);

  printf("\n+<valor> inserta un valor, -<valor> elimina un valor, ?<valor> bsuca un valor, m muestra el arbol, q sale.\nLos valores deben estar entre 1 y 99, plis.\n");

  while(1){

    printf("> ");

    char buffer[100];
    char c=0;
    int valor=0;

    while(!fgets(buffer, 100, stdin));

    sscanf(buffer, "%c%i", &c, &valor);
    c = (char)tolower(c);

    if(c == 'q')
      break;

    if(c == 'm')
      mostrar_avl(avl, formatear_int);
    else if(c && valor>0 && valor<100){

      if(c == '+'){
        int* i = malloc(sizeof(int));
        *i = valor;
        avl_insertar(avl, i);
      }
      else if (c == '-'){
        int* elemento = avl_quitar(avl, &valor);
        free(elemento);
      }
      else if(c == '?'){
        int* encontrado = avl_buscar(avl, &valor);
        if(encontrado)
          printf("Valor encontrado: %i\n", *encontrado);
        else printf("No encontré el valor D:\n");
      }
      else
        printf("Tenes que usar +<numero> o -<numero>");

      mostrar_avl(avl, formatear_int);
    }
  }

  avl_destruir_todo(avl, destruir_int);
}
