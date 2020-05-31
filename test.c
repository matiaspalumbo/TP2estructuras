#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "itree.h"

#define N_TO_PRINT 5

// void imprimir_entero(int dato) {
//   printf("%d ", dato);
// }



int main() {

  srand(time(0));
  ITree raiz = itree_crear();
  // int nums[N_TO_PRINT] = {1, 24, 16, 10, 8, 3, 4};
  // int nums[N_TO_PRINT] = {1, 3, 0, 4, 5};
  // for (int i=0; i <N_TO_PRINT; i++) {
    // raiz = avltree_insertar(raiz, nums[i]);
    // avltree_imprimir(raiz);
    // printf("Nodo agregado: %d Altura de %d: %d\n", nums[i], raiz->izq, avltree_altura(raiz));
  // }
  // printf("Nodo a eliminar: %d\n", nums[(N_TO_PRINT-1)/2]);
  // raiz = avltree_eliminar(raiz,3);
  // avltree_imprimir(raiz);

  



  return 0;
}
