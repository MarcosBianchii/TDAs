#include "avl.h"

typedef struct nodo {
      int altura_izq;
      int altura_der;
      void *valor;
      struct nodo *izq;
      struct nodo *der;
} nodo_t;

typedef struct avl {
      nodo_t *raiz;
      size_t tamanio;
      comparador_avl cmp;
} avl_t;

avl_t *avl_crear(comparador_avl cmp) {
      if (!cmp) return NULL;
      avl_t *avl = calloc(1, sizeof(avl_t));
      avl->cmp = cmp;
      return avl;
}

static int diferencia_altura(nodo_t *nodo) {
      if (!nodo) return 0;
      return nodo->altura_izq - nodo->altura_der;
}

static int max_altura(nodo_t *nodo) {
      if (!nodo) return 0;
      return nodo->altura_izq > nodo->altura_der ? nodo->altura_izq : nodo->altura_der;
}

static bool validar_doble_rotacion(nodo_t *padre, nodo_t *hijo) {
      if (diferencia_altura(padre) < 0 && diferencia_altura(hijo) > 0)
            return true;
      
      if (diferencia_altura(padre) > 0 && diferencia_altura(hijo) < 0)
            return true;
      
      return false;
}

static nodo_t *rotacion_derecha(nodo_t *);

static nodo_t *rotacion_izquierda(nodo_t *raiz) {
      if (validar_doble_rotacion(raiz, raiz->der))
            raiz->der = rotacion_derecha(raiz->der);

      nodo_t *hijo_der = raiz->der;
      raiz->der = hijo_der->izq;
      hijo_der->izq = raiz;
      raiz->altura_der = !raiz->der ? 0 : max_altura(raiz->der) + 1;
      hijo_der->altura_izq = max_altura(raiz) + 1;
      return hijo_der;
}

static nodo_t *rotacion_derecha(nodo_t *raiz) {
      if (validar_doble_rotacion(raiz, raiz->izq))
            raiz->izq = rotacion_izquierda(raiz->izq);

      nodo_t *hijo_izq = raiz->izq;
      raiz->izq = hijo_izq->der;
      hijo_izq->der = raiz;
      raiz->altura_izq = !raiz->izq ? 0 : max_altura(raiz->izq) + 1;
      hijo_izq->altura_der = max_altura(raiz) + 1;
      return hijo_izq;
}

static nodo_t *avl_insertar_rec(avl_t *avl, nodo_t *raiz, void *elemento) {
      if (!raiz) {
            nodo_t *nodo = calloc(1, sizeof(nodo_t));
            if (!nodo) return NULL;
            nodo->valor = elemento;
            avl->tamanio++;
            return nodo;
      }

      int cmp = avl->cmp(raiz->valor, elemento);
      if (cmp > 0) {
            raiz->izq = avl_insertar_rec(avl, raiz->izq, elemento);
            raiz->altura_izq = max_altura(raiz->izq) + 1;
      }

      else if (cmp < 0) {
            raiz->der = avl_insertar_rec(avl, raiz->der, elemento);
            raiz->altura_der = max_altura(raiz->der) + 1;
      }

      int dif_altura = diferencia_altura(raiz);
      if (dif_altura < -1)
            raiz = rotacion_izquierda(raiz);

      else if (dif_altura > 1)
            raiz = rotacion_derecha(raiz);

      return raiz;
}

void avl_insertar(avl_t *avl, void *elemento) {
      if (!avl) return;
      avl->raiz = avl_insertar_rec(avl, avl->raiz, elemento);
}

static nodo_t *obtener_predecesor(nodo_t *raiz, nodo_t **predecesor) {
      if (!raiz->der) {
            *predecesor = raiz;
            return raiz->izq;
      }

      raiz->der = obtener_predecesor(raiz->der, predecesor);
      raiz->altura_der = !raiz->der ? 0 : max_altura(raiz->der) + 1;

      int dif_altura = diferencia_altura(raiz);
      if (dif_altura < -1)
            raiz = rotacion_izquierda(raiz);

      else if (dif_altura > 1)
            raiz = rotacion_derecha(raiz);

      return raiz;
}

static nodo_t *avl_quitar_rec(avl_t *avl, nodo_t *raiz, void *elemento, void **item_a_quitar) {
      if (!raiz) return NULL;

      int cmp = avl->cmp(raiz->valor, elemento);
      if (cmp > 0) {
            raiz->izq = avl_quitar_rec(avl, raiz->izq, elemento, item_a_quitar);
            raiz->altura_izq = !raiz->izq ? 0 : max_altura(raiz->izq) + 1;
      }

      else if (cmp < 0) {
            raiz->der = avl_quitar_rec(avl, raiz->der, elemento, item_a_quitar);
            raiz->altura_der = !raiz->der ? 0 : max_altura(raiz->der) + 1;
      }

      else {
            avl->tamanio--;
            *item_a_quitar = raiz->valor;

            nodo_t *izq = raiz->izq;
            nodo_t *der = raiz->der;
            if (izq && der) {
                  nodo_t *predecesor = NULL;
                  raiz->izq = obtener_predecesor(raiz->izq, &predecesor);
                  raiz->valor = predecesor->valor;
                  raiz->altura_izq = !raiz->izq ? 0 : max_altura(raiz->izq) + 1;
                  free(predecesor);
            } else {
                  free(raiz);
                  raiz = izq ? izq : der;
            }
      }

      int dif_altura = diferencia_altura(raiz);
      if (dif_altura < -1)
            raiz = rotacion_izquierda(raiz);

      else if (dif_altura > 1)
            raiz = rotacion_derecha(raiz);

      return raiz;
}

void *avl_quitar(avl_t *avl, void *elemento) {
      if (!avl) return NULL;
      void *item_a_quitar = NULL;
      avl->raiz = avl_quitar_rec(avl, avl->raiz, elemento, &item_a_quitar);
      return item_a_quitar;
}

static void *avl_buscar_rec(avl_t *avl, nodo_t *raiz, void *elemento) {
      if (!raiz) return NULL;

      int cmp = avl->cmp(raiz->valor, elemento);
      if (cmp > 0) return avl_buscar_rec(avl, raiz->izq, elemento);
      if (cmp < 0) return avl_buscar_rec(avl, raiz->der, elemento);
      else return raiz->valor;
}

void *avl_buscar(avl_t *avl, void *elemento) {
      if (!avl) return NULL;
      return avl_buscar_rec(avl, avl->raiz, elemento);
}

bool avl_vacio(avl_t *avl) {
      if (!avl) return true;
      return avl->tamanio == 0;
}

size_t avl_tamanio(avl_t *avl) {
      if (!avl) return 0;
      return avl->tamanio;
}

static void avl_recorrido_rec(avl_t *avl, nodo_t *raiz, avl_recorrido recorrido, bool (*f)(void *), bool *exit) {
      if (!raiz || *exit) return;

      if (recorrido == PREORDEN)
            if (f(raiz->valor)) *exit = true;
      avl_recorrido_rec(avl, raiz->izq, recorrido, f, exit);
      if (recorrido == INORDEN)
            if (f(raiz->valor)) *exit = true;
      avl_recorrido_rec(avl, raiz->der, recorrido, f, exit);
      if (recorrido == POSTORDEN)
            if (f(raiz->valor)) *exit = true;
}

void avl_recorrer_con_funcion(avl_t *avl, avl_recorrido recorrido, bool (*f)(void *)) {
      if (!avl || !f) return;
      bool exit = false;
      avl_recorrido_rec(avl, avl->raiz, recorrido, f, &exit);
}

void avl_destruir(avl_t *avl) {
      avl_destruir_todo(avl, NULL);
}

static void avl_destruir_todo_rec(nodo_t *raiz, void (*f)(void *)) {
      if (!raiz) return;

      avl_destruir_todo_rec(raiz->izq, f);
      avl_destruir_todo_rec(raiz->der, f);
      if (f) f(raiz->valor);
      free(raiz);
}

void avl_destruir_todo(avl_t *avl, void (*destructor)(void *)) {
      if (!avl) return;
      
      avl_destruir_todo_rec(avl->raiz, destructor);
      free(avl);
}