#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// #include "../Implementaciones/Pilas/pila.h"
#include "itree.h"


ITree itree_crear() {
  return NULL;
}


void itree_destruir(ITree nodo) {
  if (nodo) {
    itree_destruir(nodo->left);
    itree_destruir(nodo->right);
    free(nodo);
  }
}


int itree_empty(ITree nodo) {
  return nodo == NULL;
}


// ITree itree_insertar(ITree nodo, int dato) {
//   ITree nuevoNodo = malloc(sizeof(ITNodo));
//   nuevoNodo->dato = dato;
//   nuevoNodo->altura = itree_altura(nodo);
//   nuevoNodo->left = NULL;
//   nuevoNodo->right = NULL;
//   if (itree_empty(nodo)) {
//     nodo = nuevoNodo;
//   } else {
//     ITree temp = nodo, *direccion = (temp->dato > dato) ? temp->left : temp->right;
//     nuevoNodo->altura++;
//     while (direccion) {
//       nuevoNodo->altura++;
//       temp = direccion;
//       direccion = (temp->dato > dato) ? temp->left : temp->right;
//     }
//     if (temp->dato > dato)
//       temp->left = nuevoNodo;
//     else
//       temp->right = nuevoNodo;
//   }

//   return nodo;
// }

double maximo(double n1, double n2) {
  return n1 < n2 ? n2 : n1;
}

double calcular_max(ITNodo* nodo) {
  if (nodo->left && nodo->right)
    return maximo(maximo(nodo->der, nodo->left->max), nodo->right->max);
  else if (nodo->left || nodo->right) {
    ITNodo* nodoNoNULL = (nodo->left) ? nodo->left : nodo->right;
    return maximo(nodo->der, nodoNoNULL->max);
  } else
    return nodo->der;
}


// int itree_altura(ITree nodo) {
//   if (itree_empty(nodo))
//     return -1;
//   else {
//     int alturaLeft = 0, alturaRight = 0;
//     alturaLeft = 1 + itree_altura(nodo->left);
//     alturaRight = 1 + itree_altura(nodo->right);
//     return maximo(alturaLeft, alturaRight);
//   }
// }


int itree_altura(ITree nodo) {
  return (itree_empty(nodo)) ? -1 : nodo->altura;
}

int itree_balance_factor(ITree nodo) {
  return itree_altura(nodo->left) - itree_altura(nodo->right);
}

ITree rotacion_a_derecha(ITree nodo) {
  ITree nuevaRaiz = nodo->left;
  ITree hijo_raiz = nuevaRaiz->right; 
  nuevaRaiz->right = nodo;
  nodo->left = hijo_raiz;
  nodo->altura = 1 + maximo(itree_altura(nodo->right), (itree_altura(nodo->left)));
  nuevaRaiz->altura = 1 + maximo(itree_altura(nuevaRaiz->right), (itree_altura(nuevaRaiz->left)));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

ITree rotacion_a_izquierda(ITree nodo) {
  ITree nuevaRaiz = nodo->right;
  ITree hijo_raiz = nuevaRaiz->left; 
  nuevaRaiz->left = nodo;
  nodo->right = hijo_raiz;
  nodo->altura = 1 + maximo(itree_altura(nodo->right), (itree_altura(nodo->left)));
  nuevaRaiz->altura = 1 + maximo(itree_altura(nuevaRaiz->right), (itree_altura(nuevaRaiz->left)));
  nodo->max = calcular_max(nodo);
  nuevaRaiz->max = calcular_max(nuevaRaiz);
  return nuevaRaiz;
}

ITree itree_insertar(ITree nodo, double izq, double der) {
  if (itree_empty(nodo)) {
    nodo = malloc(sizeof(ITNodo));
    nodo->izq = izq;
    nodo->der = der;
    nodo->left = NULL;
    nodo->right = NULL;
    nodo->altura = 0;
    nodo->max = nodo->der;
    // printf("0 %lf, %lf\n", nodo->izq, nodo->der);
    return nodo;
  } else if (nodo->izq > izq || (nodo->izq == izq && nodo->der != der)) {
    nodo->left = itree_insertar(nodo->left, izq, der);
  }
  else if (nodo->izq < izq) {
    nodo->right = itree_insertar(nodo->right, izq, der);
  }
  else {
    return nodo;
  }

  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left), (double) itree_altura(nodo->right));
  nodo->max = calcular_max(nodo);

  int balance = itree_balance_factor(nodo);
  if (balance < -1 && izq > nodo->right->izq) {
    printf("Izq Izq: %lf\n", nodo->izq);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1 && izq <= nodo->left->izq) {
    printf("Der Der: %lf\n", nodo->izq);
    nodo = rotacion_a_derecha(nodo);
  } else if (balance < -1) {
    printf("Der Izq: %lf\n", nodo->izq);
    nodo->right = rotacion_a_derecha(nodo->right);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1) {
    printf("Izq Der: %lf\n", nodo->izq);
    nodo->left = rotacion_a_izquierda(nodo->left);
    nodo = rotacion_a_derecha(nodo);
  }
  return nodo;
}


ITree itree_eliminar(ITree nodo, double izq, double der) {
  if (itree_empty(nodo))
    return nodo;
  else if (nodo->izq == izq && nodo->der == der) {
    if (!nodo->left && !nodo->right) {
      free(nodo);
      nodo = NULL;
    } else if (nodo->left && nodo->right) {
      ITree minNodoDerecho = nodo->right;
      while (minNodoDerecho->left) {
        minNodoDerecho = minNodoDerecho->left;
      }
      nodo->izq = minNodoDerecho->izq;
      nodo->der = minNodoDerecho->der;
      nodo->right = itree_eliminar(nodo->right, minNodoDerecho->izq, minNodoDerecho->der);
    } else if (nodo->left || nodo->right) {
      ITree hijoNoNULL = (nodo->left) ? nodo->left : nodo->right;
      free(nodo);
      nodo = hijoNoNULL;
    }
  } else if (nodo->izq > izq) {
    nodo->left = itree_eliminar(nodo->left, izq, der);
  } else { 
    nodo->right = itree_eliminar(nodo->right, izq, der);
  }
  
  if (!nodo)
    return nodo;
  nodo->altura = 1 + (int) maximo((double) itree_altura(nodo->left), (double) itree_altura(nodo->right));

  int balance = itree_balance_factor(nodo);

  if (balance < -1 && itree_balance_factor(nodo->right) < 0) {
    printf("Izq Izq: %0.2f\n", nodo->izq);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1 && itree_balance_factor(nodo->left) > 0) {
    printf("Der Der: %0.2f\n", nodo->izq);
    nodo = rotacion_a_derecha(nodo);
  } else if (balance < -1) {
    printf("Der Izq: %0.2f\n", nodo->izq);
    nodo->right = rotacion_a_derecha(nodo->right);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1) {
    printf("Izq Der: %0.2f\n", nodo->izq);
    nodo->left = rotacion_a_izquierda(nodo->left);
    nodo = rotacion_a_derecha(nodo);
  }
  return nodo;

}


// int itree_contiene(ITree nodo, int dato) {
//   if (itree_empty(nodo)) return 0;
//   if (nodo->dato == dato) return 1;
//   return (nodo->dato > dato) ? itree_contiene(nodo->left, dato) : itree_contiene(nodo->right, dato);
// }


// void itree_recorrer_extra(ITree arbol, FuncionVisitanteExtra visit, void *extra) {
//   if (!itree_empty(arbol)) {
//     visit(arbol, extra);
//     itree_recorrer_extra(arbol->left, visit, extra);
//     itree_recorrer_extra(arbol->right, visit, extra);
//   }
// }

// void sumar_cantidad(ITree arbol, void* extra) {
//   (*((int*)extra))++;
// }

// int itree_nelementos(ITree nodo) {
//  int cantidad = 0;
//  itree_recorrer_extra(nodo, sumar_cantidad, &cantidad);
//  return cantidad;
// }



void itree_recorrer_dfs_aux(ITree arbol, FuncionVisitante visit) {
  if (!itree_empty(arbol)) {
    itree_recorrer_dfs_aux(arbol->left, visit);
    visit(arbol);
    itree_recorrer_dfs_aux(arbol->right, visit);
  }
}

void imprimir_entero(ITree nodo) {
  if (nodo) printf("[%lf, %lf]  ", nodo->izq, nodo->der);
  else printf("NULL");
}

void itree_recorrer_dfs(ITree arbol) {
  itree_recorrer_dfs_aux(arbol, imprimir_entero);
  puts("");
}

// void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit) {

// }



void pretty_print_aux(ITree nodo, int space) { 
  if (itree_empty(nodo)) 
    return; 
  space += 15; 
  pretty_print_aux(nodo->right, space); 
  printf("\n"); 
  for (int i = 15; i < space; i++) 
      printf(" "); 
  printf("[%0.0f, %0.0f]{%0.0f}(%d)", nodo->izq, nodo->der, nodo->max, itree_altura(nodo));
  pretty_print_aux(nodo->left, space); 
} 

void pretty_print(ITree nodo) {
  puts("");puts("");
  pretty_print_aux(nodo, 0);
  puts("");puts("");puts("");puts("");
}
  

int itree_minimo(ITree arbol) {
  while (arbol->left) {
    arbol = arbol->left;
  }
  return arbol->izq;
}



// int itree_acceder(ITree arbol, int pos) {
//   Pila pila = pila_crear();
//   int indice = -1, dato;
//   ITree nodoActual = arbol;
//   while (pos != indice) {
//     while (nodoActual) {
//       pila = pila_apilar(pila, nodoActual);
//       nodoActual = nodoActual->left;
//     }
//     nodoActual = pila_ultimo(pila);
//     pila_desapilar(&pila);
//     indice++;
//     dato = nodoActual->dato;
//     nodoActual = nodoActual->right;
//   }
//   return dato;
// }


/* 
FINAL EJ. 7
Al agregar varios elementos, el árbol resultante tendrá forma de lista 
solo si los elementos fueron agregados en forma ascendente o descendente.
Es decir, si los elementos son agregados ascendentemente, no existirán 
subárboles izquierdos, y si son agregados descendentemente, no existirán
subárboles derechos.

Al buscar un nodo en esa lista, se visitarán los nodos de forma consecutiva
hasta encontrarlo o hasta verificar que no está. Esto es, con los nodos
ordenados ascendentemente, si el elemento a buscar es menor al nodo actual, y
si es mayor en caso contrario.


EJ. 8
La búsqueda inorder es la que permite recorrer los elementos en forma
ordenada. Esto se debe a que siempre, en un árbol dado, la raíz del subárbol izquierdo
será menor que la raíz, la cual a su vez será menor que la raíz del subárbol derecho.
*/


ITree itree_intersecar(ITree arbol, double izq, double der) {
  // printf("intersecar [%.2f, %.2f] con ", izq, der); imprimir_entero(arbol); puts("");
  ITree interseccion = NULL;
  if (arbol) {
    if (der < arbol->izq) {
      // puts("0");
      if (arbol->left && izq <= arbol->left->max) {
        // puts("0.1");
        interseccion = itree_intersecar(arbol->left, izq, der);
      }
    } else if (izq > arbol->der) {
      if (arbol->right && izq <= arbol->right->max) {
        interseccion = itree_intersecar(arbol->right, izq, der);
      }
    }




    } else if (arbol->left && izq > arbol->left->max) {
      // puts("1");
      if (arbol->right && izq <= arbol->right->max) {
        // puts("1.1");
        interseccion = itree_intersecar(arbol->right, izq, der);
      }
    } else {
      // puts("2");
      interseccion = arbol;
    }
  }

  return interseccion;
}