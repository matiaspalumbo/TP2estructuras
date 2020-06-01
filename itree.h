#ifndef __ITREE_H__
#define __ITREE_H__


typedef struct _ITNodo {
  double izq, der, max;
  int altura;
  struct _ITNodo *right;
  struct _ITNodo *left;
} ITNodo;

typedef ITNodo* ITree;

typedef void (*FuncionVisitante) (ITree arbol);


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

ITree itree_insertar(ITree arbol, double izq, double der);

ITree itree_eliminar(ITree nodo, double izq, double der);

int itree_balance_factor(ITree arbol);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
int itree_contiene(ITree arbol, double dato);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit);

void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit);

int itree_altura(ITree nodo);

void itree_imprimir(ITree arbol);

void imprimir_intervalo(ITree nodo);

void pretty_print(ITree nodo);

int itree_minimo(ITree arbol);

ITree itree_intersecar(ITree arbol, double izq, double der);

#endif /* __ITREE_H__ */
