#ifndef __ITREE_H__
#define __ITREE_H__

/* Archivo de cabecera de la implementación de Árboles de Intervalos utilizando 
Arboles AVL ordenados de acuerdo a la primera componente del intervalo. */


typedef struct {
  double izq, der;
} Intervalo;

// typedef struct _ITNodo {
//   Intervalo intv;
//   double max;
//   int altura;
//   struct _ITNodo *right;
//   struct _ITNodo *left;
// } ITNodo;


typedef struct _ITNodo {
  double izq, der, max;
  int altura;
  struct _ITNodo *right;
  struct _ITNodo *left;
} ITNodo;

typedef ITNodo* ITree;

typedef void (*FuncionVisitante) (ITree arbol);


/* Crea un árbol de intervalos vacíos. */
ITree itree_crear();

/* Destruye un árbol de intervalos. */
void itree_destruir(ITree nodo);

/* Inserta un intervalo en un árbol de intervalos. */
ITree itree_insertar(ITree arbol, double izq, double der);

/* Elimina un intervalo de un árbol de intervalos. */
ITree itree_eliminar(ITree nodo, double izq, double der);

/* Determina si un intervalo se intersecta con alguno de los intervalos del 
árbol y, en caso afirmativo, retorna un puntero al nodo correspondiente. */
ITree itree_intersecar(ITree arbol, double izq, double der);

/* Recorrido primero en profundidad (DFS) del árbol de intervalos, 
visita cada nodo utilizando la funcion pasada. */
void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit);

/* Recorrido primero a lo ancho (BFS) del árbol de intervalos, 
visita cada nodo utilizando la funcion pasada. */
void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit);


/* Funciones auxiliares sobre arboles de intervalos. */

/* Indica si el árbol es vacío.*/
int itree_empty(ITree nodo);

/* Función del tipo FuncionVisitante que dado un nodo de un arbol de 
intervalos, imprime el intervalo de forma significativa. */
void imprimir_intervalo(ITree nodo);

void pretty_print(ITree nodo); // BORRAR

int itree_minimo(ITree arbol); // BORRAR

/* Devuelve la altura del nodo pasado, si es vacío retorna -1. */
int itree_altura(ITree nodo);

/* Calcula el balance factor del nodo pasado. */
int itree_balance_factor(ITree nodo);

int itree_contiene(ITree arbol, double dato); // BORRAR

#endif /* __ITREE_H__ */
