#ifndef __ITREE_H__
#define __ITREE_H__

/* Archivo de cabecera de la implementación de Árboles de Intervalos utilizando 
Arboles AVL ordenados lexicográficamente. */

typedef struct _ITNodo {
  double izq, der, max;
  int altura;
  struct _ITNodo *right;
  struct _ITNodo *left;
} ITNodo;

typedef ITNodo* ITree;

typedef void (*FuncionVisitante) (ITree arbol);


/* Crea un árbol de intervalos vacío. */
ITree itree_crear();

/* Destruye un árbol de intervalos. */
void itree_destruir(ITree nodo);

/* Indica si el árbol es vacío.*/
int itree_empty(ITree nodo);

/* Inserta un elemento en un árbol de intervalos. */
ITree itree_insertar(ITree arbol, double izq, double der);

/* Elimina un elemento de un árbol de intervalos. */
ITree itree_eliminar(ITree nodo, double izq, double der);

/* Determina si un intervalo se interseca con alguno de los elementos del 
árbol y, en caso afirmativo, retorna un puntero al nodo correspondiente. */
ITree itree_intersecar(ITree arbol, double izq, double der);

/* Realiza un recorrido primero en profundidad (DFS) in-order del árbol de intervalos, 
aplicando a cada nodo la funcion visitante dada como parámetro. */
void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit);

/* Realiza un recorrido primero a lo ancho (BFS) del árbol de intervalos, 
aplicando a cada nodo la funcion visitante dada como parámetro. */
void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit);

/* Función de tipo FuncionVisitante que dado un elemento de un arbol de 
intervalos, lo imprime. */
void imprimir_intervalo(ITree nodo);


#endif /* __ITREE_H__ */
