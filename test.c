#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "itree.h"

#define N_TO_PRINT 5


int main() {

  srand(time(0));
  ITree raiz = itree_crear();

  raiz = itree_insertar(raiz, 16, 20);
  raiz = itree_insertar(raiz, 8, 9);
  raiz = itree_insertar(raiz, 14, 23);

  // for (int i=0; i< 4; i++) {
    // j = rand()%(N_TO_PRINT*5);
    // raiz = itree_insertar(raiz, j, j+rand()%N_TO_PRINT);
    // raiz = itree_insertar(raiz, (i+1)*2, (i+1)*2+i*2);
    // itree_imprimir(raiz);
  // }

  pretty_print(raiz);


// imprimir_entero(itree_intersecar(raiz, 0.001, 1.55)); puts("");
// imprimir_entero(itree_intersecar(raiz, 0, 3)); puts("");
// imprimir_entero(itree_intersecar(raiz, 4, 5)); puts("");
// imprimir_entero(itree_intersecar(raiz, 16, 16)); puts("");


  itree_destruir(raiz);

  return 0;
}
