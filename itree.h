#ifndef __ITREE_H__
#define __ITREE_H__


typedef struct _ITNodo {
  int izq, der;
  int max, altura;
  struct _ITNodo* right;
  struct _ITNodo* left;
} ITNodo;

typedef ITNodo* ITree;

typedef void (*FuncionVisitante) (ITree arbol);

typedef void (*FuncionVisitanteExtra) (ITree dato, void *extra);

/**
 * Devuelve un arbol vacío.
 */
ITree itree_crear();

/**
 * Destruccion del árbol.
 */
void itree_destruir(ITree nodo);

/**
 * Indica si el árbol es vacío.
 */
int itree_empty(ITree nodo);

ITree itree_insertar(ITree nodo, int extIzq, int extDer);

ITree itree_eliminar(ITree nodo, int izq, int der);

int itree_altura_factor(ITree arbol);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
int itree_contiene(ITree arbol, int dato);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void itree_recorrer(ITree arbol, FuncionVisitante visit);

int itree_altura(ITree nodo);

int itree_altura(ITree nodo);

void itree_imprimir(ITree arbol);

int itree_minimo(ITree arbol);

int itree_acceder(ITree arbol, int pos);

#endif /* __ITREE_H__ */
