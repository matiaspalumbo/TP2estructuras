#include <stdio.h>
#include <stdlib.h>
#include "../Practica4/avltree.h"

typedef struct _ITNodo {
  int izq, der;
  int max;
  struct _ITNodo* right;
  struct _ITNodo* left;
} ITNodo;

typedef ITNodo* ITree;

int intersecar(ITree int1, ITree int2) {
  return (int1->izq <= int2->izq) && (int1->der >= int2->izq) || 
  (int2->izq <= int1->izq) && (int2->der >= int1->izq);
}

