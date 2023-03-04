#include "mostrar_avl.h"
#include "avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int max(int a, int b){ return a>b?a:b; }

int avl_a_array_r(nodo_t* raiz, void** buffer, int n, int i){
  if(i>=n || !raiz)
    return 0;

  buffer[i] = raiz;
  int a = avl_a_array_r(raiz->izq, buffer, n, 2*i+1);
  int b = avl_a_array_r(raiz->der, buffer, n, 2*i+2);
  return max(max(a,b),i+1);
}

int avl_a_array(avl_t* avl, void** buffer, int n){
  if(!avl)
    return 0;
  return avl_a_array_r(avl->raiz, buffer, n, 0);
}

void mostrar_arbol(void** buffer, int n, void (*formateador)(void*)){
  printf("\n");
  int niveles = 0;
  for(int restantes=n;restantes>0;restantes>>=1)
    niveles++;

  int n_nodo=0;
  for(int nivel=0;nivel<niveles;nivel++){
    int posicion = 1<<(niveles-nivel-1);

    for(int nodo=0;nodo<(1<<nivel);nodo++){
      for(int i=1;i<posicion;i++){
        if(i<=posicion/2-1 || buffer[2*n_nodo+1]==0)
          printf("  ");
        else{
          if(i == posicion/2)
            printf(" ┌");
          else printf("――");
        }
      }

      if(buffer[n_nodo]!=0){
        formateador(buffer[n_nodo]);
      }
      else{
        printf("  ");
      }

      for(int i=0;i<posicion;i++){
        if(i>=posicion/2 || buffer[2*n_nodo+2]==0)
          printf("  ");
        else{
          if(i == posicion/2-1)
            printf("―┐");
          else printf("――");
        }
      }
      n_nodo++;
    }
    printf("\n");
  }
}


void  mostrar_avl(avl_t* avl, void (*formateador)(void*)){
    void* valores[MAX_ARBOL];

    memset(valores, 0, sizeof(valores));
    int cantidad = avl_a_array(avl, valores, MAX_ARBOL);
    mostrar_arbol(valores, cantidad, formateador);
}
