#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "itree.h"

#define N_TO_PRINT 10

// void imprimir_entero(int dato) {
//   printf("%d ", dato);
// }



int main() {

  srand(time(0));
  ITree raiz = itree_crear();
  int j;

  for (int i=0; i< N_TO_PRINT; i++) {
    j = rand()%(N_TO_PRINT*5);
    raiz = itree_insertar(raiz, j, j+rand()%N_TO_PRINT);
    itree_imprimir(raiz);
  }
  pretty_print(raiz);
// raiz = itree_insertar(raiz, 1, 5);
// itree_imprimir(raiz);
// raiz = itree_insertar(raiz, 2, 4);
// itree_imprimir(raiz);
// raiz = itree_insertar(raiz, 10, 15);
// itree_imprimir(raiz);
// raiz = itree_insertar(raiz, 9, 15);
// itree_imprimir(raiz);
// raiz = itree_insertar(raiz, 2, 9);
// itree_imprimir(raiz);

  itree_destruir(raiz);




  return 0;
}
