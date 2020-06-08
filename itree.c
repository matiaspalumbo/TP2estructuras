#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "itree.h"
#include "cola.h"

/* Archivo con la implementación de Árboles de Intervalos AVL. */


ITree itree_crear() {
  return NULL;
}

void itree_destruir(ITree nodo) {
  if (!itree_empty(nodo)) {
    itree_destruir(nodo->left);
    itree_destruir(nodo->right);
    free(nodo);
  }
}

int itree_empty(ITree nodo) {
  return nodo == NULL;
}


/* Devuelve la altura del ITree dado como parámetro */
int itree_altura(ITree arbol) {
  return (itree_empty(arbol)) ? -1 : arbol->altura;
}

/* Devuelve factor balance del ITree dado como parámetro,
restando las alturas de sus subárboles izquierdo y derecho. */
int itree_balance_factor(ITree arbol) {
  return itree_altura(arbol->left) - itree_altura(arbol->right);
}

/* Devuelve el máximo de dos doubles. */
double maximo(double n1, double n2) {
  return n1 < n2 ? n2 : n1;
}

/* Calcula la altura de un ITree luego de insertar un nodo. */
int calcular_altura(ITree arbol) {
  return 1 + (int) maximo(itree_altura(arbol->right), itree_altura(arbol->left));
}

/* Calcula el máximo extremo derecho de un ITree luego de insertar un nodo. */
double calcular_max(ITree arbol) {
  if (!itree_empty(arbol->left) && !itree_empty(arbol->right))
    return maximo(maximo(arbol->der, arbol->left->max), arbol->right->max);
  else if (!itree_empty(arbol->left) || !itree_empty(arbol->right)) {
    ITree nodoNoNULL = (!itree_empty(arbol->left)) ? arbol->left : arbol->right;
    return maximo(arbol->der, nodoNoNULL->max);
  } else
    return arbol->der;
}

/* Realiza una rotación a derecha del nodo dado como parámetro. */
ITree rotacion_a_derecha(ITree nodo) {
  ITree nuevaRaiz = nodo->left; // El hijo izquierdo del nodo pasará a ser la nueva raíz del árbol.
  ITree hijo_raiz = nuevaRaiz->right;
  nuevaRaiz->right = nodo;
  /* El hijo derecho del hijo izquierdo del nodo pasará a ser el hijo izquierdo
  del nodo sobre el cual se realizó la rotación. */       V
  nodo->left = hijo_raiz;
  nodo->altura = 1 + (int) maximo(itree_altura(nodo->right), itree_altura(nodo->left));
  nuevaRaiz->altura = 1 + (int) maximo(itree_altura(nuevaRaiz->right), itree_altura(nuevaRaiz->left));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

ITree rotacion_a_izquierda(ITree nodo) {
  ITree nuevaRaiz = nodo->right;
  ITree hijo_raiz = nuevaRaiz->left; 
  nuevaRaiz->left = nodo;
  nodo->right = hijo_raiz;
  nodo->altura = 1 + (int) maximo(itree_altura(nodo->right), (itree_altura(nodo->left)));
  nuevaRaiz->altura = 1 + (int) maximo(itree_altura(nuevaRaiz->right), (itree_altura(nuevaRaiz->left)));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

ITree itree_insertar(ITree nodo, double izq, double der) {
  if (itree_empty(nodo)) {
    nodo = malloc(sizeof(ITNodo));
    nodo->izq = izq;
    nodo->der = der;
    nodo->altura = 0;
    nodo->max = nodo->der;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
  } else if (nodo->izq > izq || (nodo->izq == izq && nodo->der > der)) {
    nodo->left = itree_insertar(nodo->left, izq, der);
  } else if (nodo->izq < izq || (nodo->izq == izq && nodo->der < der)) {
    nodo->right = itree_insertar(nodo->right, izq, der);
  } else {
    return nodo;
  }

  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left), (double) itree_altura(nodo->right));
  nodo->max = calcular_max(nodo);

  int balance = itree_balance_factor(nodo);
  if (balance < -1 && (izq > nodo->right->izq || (izq == nodo->right->izq && der > nodo->right->der))) {
    printf("Izq Izq: ");imprimir_intervalo(nodo);puts("");
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1 && (izq < nodo->left->izq || (izq == nodo->left->izq && der < nodo->left->der))) {
    printf("Der Der: ");imprimir_intervalo(nodo);puts("");
    nodo = rotacion_a_derecha(nodo);
  } else if (balance < -1) {
    printf("Der Izq: ");imprimir_intervalo(nodo);puts("");
    nodo->right = rotacion_a_derecha(nodo->right);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1) {
    printf("Izq Der: ");imprimir_intervalo(nodo);puts("");
    nodo->left = rotacion_a_izquierda(nodo->left);
    nodo = rotacion_a_derecha(nodo);
  }
  return nodo;
}

ITree itree_eliminar(ITree nodo, double izq, double der) {
  if (itree_empty(nodo))
    return nodo;
  else if (nodo->izq == izq && nodo->der == der) {
    if (itree_empty(nodo->left) && itree_empty(nodo->right)) {
      free(nodo);
      nodo = NULL;
    } else if (!itree_empty(nodo->left) && !itree_empty(nodo->right)) {
      ITree minNodoDerecho = nodo->right;
      while (!itree_empty(minNodoDerecho->left)) {
        minNodoDerecho = minNodoDerecho->left;
      }
      nodo->izq = minNodoDerecho->izq;
      nodo->der = minNodoDerecho->der;
      nodo->right = itree_eliminar(nodo->right, minNodoDerecho->izq, minNodoDerecho->der);
    } else {
      ITree hijoNoNULL = (!itree_empty(nodo->left)) ? nodo->left : nodo->right;
      free(nodo);
      nodo = hijoNoNULL;
    }
  } else if (nodo->izq > izq || (nodo->izq == izq && nodo->der > der)) {
    nodo->left = itree_eliminar(nodo->left, izq, der);
  } else { 
    nodo->right = itree_eliminar(nodo->right, izq, der);
  }
  
  if (itree_empty(nodo)) return nodo;

  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left),(double) itree_altura(nodo->right));
  nodo->max = calcular_max(nodo);
  
  int balance = itree_balance_factor(nodo);
  if (balance < -1 && itree_balance_factor(nodo->right) < 0) {
    // printf("Izq Izq: %0.2f\n", nodo->izq);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1 && itree_balance_factor(nodo->left) > 0) {
    // printf("Der Der: %0.2f\n", nodo->izq);
    nodo = rotacion_a_derecha(nodo);
  } else if (balance < -1) {
    // printf("Der Izq: %0.2f\n", nodo->izq);
    nodo->right = rotacion_a_derecha(nodo->right);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1) {
    // printf("Izq Der: %0.2f\n", nodo->izq);
    nodo->left = rotacion_a_izquierda(nodo->left);
    nodo = rotacion_a_derecha(nodo);
  }

  return nodo;
}

void imprimir_intervalo(ITree nodo) {
  if (!itree_empty(nodo)) printf("[%g, %g] ", nodo->izq, nodo->der); // DEFINIR FORMATO
}

void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit) {
  // printf("recorrer DFS"); imprimir_intervalo(arbol); puts("");
  if (!itree_empty(arbol)) {
    itree_recorrer_dfs(arbol->left, visit);
    visit(arbol);
    itree_recorrer_dfs(arbol->right, visit);
  }
}

void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit) {
  // printf("recorrer BFS"); imprimir_intervalo(arbol); puts("");
  if (!itree_empty(arbol)) {
    Cola queue = cola_crear();
    cola_encolar(queue, arbol);
    ITNodo *temp;
    while (!cola_es_vacia(queue)) {
      temp = cola_primero(queue);
      cola_desencolar(queue);
      visit(temp);
      if (!itree_empty(temp->left)) cola_encolar(queue, temp->left);
      if (!itree_empty(temp->right)) cola_encolar(queue, temp->right);
    }
    cola_destruir(queue);
  }
}

// void pretty_print_aux(ITree nodo, int space) { 
//   if (itree_empty(nodo)) 
//     return; 
//   space += 15; 
//   pretty_print_aux(nodo->right, space); 
//   printf("\n"); 
//   for (int i = 15; i < space; i++) 
//       printf(" "); 
//   printf("[%0.0f, %0.0f]{%0.0f}(%d)", nodo->izq, nodo->der, nodo->max, itree_altura(nodo));
//   pretty_print_aux(nodo->left, space); 
// } 

// void pretty_print(ITree nodo) {
//   puts("");puts("");
//   pretty_print_aux(nodo, 0);
//   puts("");puts("");puts("");puts("");
// }


ITree itree_intersecar(ITree arbol, double izq, double der) {
  ITree interseccion = NULL;
  if (!itree_empty(arbol)) {
    if (der < arbol->izq) {
      if (!itree_empty(arbol->left) && izq <= arbol->left->max)
        interseccion = itree_intersecar(arbol->left, izq, der);
    } else if (izq > arbol->der) {
      if (!itree_empty(arbol->left) && izq <= arbol->left->max)
        interseccion = itree_intersecar(arbol->left, izq, der);
      else if (!itree_empty(arbol->right) && izq <= arbol->right->max)
        interseccion = itree_intersecar(arbol->right, izq, der);
    } else
        interseccion = arbol;
  }

  return interseccion;
}