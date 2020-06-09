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
int itree_altura(ITree nodo) {
  return (itree_empty(nodo)) ? -1 : nodo->altura;
}

/* Devuelve factor balance del ITree dado como parámetro,
restando las alturas de sus subárboles izquierdo y derecho. */
int itree_balance_factor(ITree nodo) {
  return itree_altura(nodo->left) - itree_altura(nodo->right);
}

/* Devuelve el máximo de dos doubles. */
double maximo(double n1, double n2) {
  return n1 < n2 ? n2 : n1;
}

/* Calcula la altura de un ITree luego de insertar un nodo. */
int calcular_altura(ITree nodo) {
  return 1 + (int) maximo(itree_altura(nodo->right), itree_altura(nodo->left));
}

/* Calcula el máximo extremo derecho de un ITree luego de insertar un nodo. */
double calcular_max(ITree nodo) {
  if (!itree_empty(nodo->left) && !itree_empty(nodo->right))
    return maximo(maximo(nodo->der, nodo->left->max), nodo->right->max);
  else if (!itree_empty(nodo->left) || !itree_empty(nodo->right)) {
    ITree nodoNoNULL = (!itree_empty(nodo->left)) ? nodo->left : nodo->right;
    return maximo(nodo->der, nodoNoNULL->max);
  } else
    return nodo->der;
}

/* Realiza una rotación a derecha del nodo dado como parámetro. */
ITree rotacion_a_derecha(ITree nodo) {
  ITree nuevaRaiz = nodo->left; // El hijo izquierdo del nodo pasará a ser la nueva raíz del árbol.
  ITree hijo_raiz = nuevaRaiz->right;
  nuevaRaiz->right = nodo;
  /* El hijo derecho del hijo izquierdo del nodo pasará a ser el hijo izquierdo
  del nodo sobre el cual se realizó la rotación. */
  nodo->left = hijo_raiz;
  /* Se actualizan las alturas y máximos de los nodos rotados. */
  nodo->altura = 1 + (int) maximo(itree_altura(nodo->right), itree_altura(nodo->left));
  nuevaRaiz->altura = 1 + (int) maximo(itree_altura(nuevaRaiz->right), itree_altura(nuevaRaiz->left));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

/* Realiza una rotación a izquierda del nodo dado como parámetro. */
ITree rotacion_a_izquierda(ITree nodo) {
  ITree nuevaRaiz = nodo->right; // El hijo derecho del nodo pasará a ser la nueva raíz del árbol.
  ITree hijo_raiz = nuevaRaiz->left;
  nuevaRaiz->left = nodo;
  /* El hijo izquierdo del hijo derecho del nodo pasará a ser el hijo derecho
  del nodo sobre el cual se realizó la rotación. */
  nodo->right = hijo_raiz;
  /* Se actualizan las alturas y máximos de los nodos rotados. */
  nodo->altura = 1 + (int) maximo(itree_altura(nodo->right), (itree_altura(nodo->left)));
  nuevaRaiz->altura = 1 + (int) maximo(itree_altura(nuevaRaiz->right), (itree_altura(nuevaRaiz->left)));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

/* itree_insertar inserta un nodo en el lugar correspondiente del ITree, y luego
realiza las rotaciones correspondientes si el árbol resultante está desbalanceado. */
ITree itree_insertar(ITree nodo, double izq, double der) {
  if (itree_empty(nodo)) { /* Si el nodo es vacío, se debe insertar aquí. */
    nodo = malloc(sizeof(ITNodo));
    nodo->izq = izq;
    nodo->der = der;
    nodo->altura = 0;
    nodo->max = nodo->der;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
  } else if (nodo->izq > izq || (nodo->izq == izq && nodo->der > der)) {
    /* Si el intervalo a insertar es menor según el orden lexicográfico, se insertará en el subárbol izquierdo. */
    nodo->left = itree_insertar(nodo->left, izq, der);
  } else if (nodo->izq < izq || (nodo->izq == izq && nodo->der < der)) {
    /* Si el intervalo a insertar es mayor según el orden lexicográfico, se insertará en el subárbol derecho. */
    nodo->right = itree_insertar(nodo->right, izq, der);
  } else {
    /* Si el intervalo a insertar ya está en el árbol, no se inserta nada. */
    return nodo;
  }
  /* El programa entrará en esta sección de la función solo si se llamó 
  recursivamente en el subárbol izquierdo o derecho. Si el intervalo no está presente en el árbol, 
  la recursión desciende hasta alguna hoja del mismo donde se insertará el elemento, y luego 
  las alturas y máximos se irán actualizando desde abajo hacia arriba. */
  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left), (double) itree_altura(nodo->right));
  nodo->max = calcular_max(nodo);
  /* Se calcula el factor balance del nodo, y en caso de desbalanceo se realizan las rotaciones correspondientes. */
  int balance = itree_balance_factor(nodo);
  if (balance < -1) {
    /* Si el subárbol izquierdo es de menor altura que el derecho, y el nuevo elemento
    es lexicográficamente mayor al subárbol derecho, se debe realizar una rotación simple a izquierda. */
    if (izq > nodo->right->izq || (izq == nodo->right->izq && der > nodo->right->der))
      nodo = rotacion_a_izquierda(nodo);
    /* En otro caso, se debe realizar una rotación doble derecha-izquierda. */
    else {
      nodo->right = rotacion_a_derecha(nodo->right);
      nodo = rotacion_a_izquierda(nodo);
    }
  } else if (balance > 1) {
    /* Si el subárbol derecho es de menor altura que el izquierdo, y el nuevo elemento
    es lexicográficamente menor al subárbol izquierdo, se debe realizar una rotación simple a derecha. */
    if (izq < nodo->left->izq || (izq == nodo->left->izq && der < nodo->left->der))
      nodo = rotacion_a_derecha(nodo);
    /* En otro caso, se debe realizar una rotación doble izquierda-derecha. */
    else {
      nodo->left = rotacion_a_izquierda(nodo->left);
      nodo = rotacion_a_derecha(nodo);
    }
  }
  return nodo;
}

/* itree_eliminar elimina un nodo si está presente en el ITree, y luego
realiza las rotaciones correspondientes si el árbol resultante está desbalanceado. */
ITree itree_eliminar(ITree nodo, double izq, double der) {
  if (!itree_empty(nodo)) {
    if (nodo->izq == izq && nodo->der == der) { // Si el nodo actual es el nodo a eliminar.
      /* A continuación se distinguen los casos en los que el nodo tiene ninguno, uno o dos hijos no NULL.
      Los dos primeros casos son triviales en la eliminación del nodo. En el caso donde tiene dos hijos no NULL,
      el nodo a eliminar se reemplaza por el mínimo nodo del subárbol derecho. */
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
      /* Si el intervalo a eliminar es menor según el orden lexicográfico, si está
      en el árbol estará en el subárbol izquierdo, por lo que se llama a la función
      recursivamente sobre el subárbol izquierdo. */
      nodo->left = itree_eliminar(nodo->left, izq, der);
    } else {
      /* En caso contrario, si el intervalo a eliminar es un nodo del árbol, 
      estará en el subárbol derecho. */
      nodo->right = itree_eliminar(nodo->right, izq, der);
    }
  }
  if (itree_empty(nodo))
    return nodo;
  /* Se actualizan la altura y el máximo del árbol. */
  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left),(double) itree_altura(nodo->right));
  nodo->max = calcular_max(nodo);
  /* Se calcula el factor balance del árbol, y en caso de desbalanceo se realizan las rotaciones correspondientes. */
  int balance = itree_balance_factor(nodo);
  if (balance < -1) {
    /* Si el subárbol izquierdo es de menor altura que el derecho, y lo mismo sucede
    para los subárboles del subárbol derecho, se debe realizar una rotación simple a izquierda. */
    if (itree_balance_factor(nodo->right) < 0)
      nodo = rotacion_a_izquierda(nodo);
    /* En otro caso, se debe realizar una rotación doble derecha-izquierda. */
    else {
      nodo->right = rotacion_a_derecha(nodo->right);
      nodo = rotacion_a_izquierda(nodo);
    }
  } else if (balance > 1) {
    /* Si el subárbol derecho es de menor altura que el izquierdo, y lo mismo sucede
    para los subárboles del subárbol izquierdo, se debe realizar una rotación simple a derecha. */
    if (itree_balance_factor(nodo->left) > 0)
      nodo = rotacion_a_derecha(nodo);
    /* En otro caso, se debe realizar una rotación doble izquierda-derecha. */
    else {
      nodo->left = rotacion_a_izquierda(nodo->left);
      nodo = rotacion_a_derecha(nodo);
    }
  }
  return nodo;
}

void imprimir_intervalo(ITree nodo) {
  if (!itree_empty(nodo)) printf("[%g, %g] ", nodo->izq, nodo->der); // DEFINIR FORMATO
}

void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit) {
  if (!itree_empty(arbol)) {
    itree_recorrer_dfs(arbol->left, visit);
    visit(arbol);
    itree_recorrer_dfs(arbol->right, visit);
  }
}

void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit) {
  if (!itree_empty(arbol)) {
    /* Crea una cola con la raiz del árbol. */
    Cola queue = cola_crear();
    cola_encolar(queue, arbol);
    ITNodo *temp;
    while (!cola_es_vacia(queue)) {
      /* Mientras la cola no sea vacía, visito el primer elemento y lo elimino de la cola. */
      temp = cola_primero(queue);
      cola_desencolar(queue);
      visit(temp);
      /* Luego agrego a la cola los hijos de ese nodo, en el orden que quiero que sean visitados. */
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