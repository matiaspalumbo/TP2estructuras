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

int comp_intervalos(int izq1, int izq2) {
  return izq1 - izq2;
}

