#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avltree.h"

#define N_TO_PRINT 5

// void imprimir_entero(int dato) {
//   printf("%d ", dato);
// }



int main() {
  // BTree uno = btree_unir(1, btree_crear(), btree_crear());
  // BTree dos = btree_unir(2, uno, btree_crear());
  // BTree tres = btree_unir(3, btree_crear(), btree_crear());
  // BTree cuatro = btree_unir(4, dos, tres);
  // BTree cinco = btree_unir(5, btree_crear(), btree_crear());
  // BTree raiz = btree_unir(6, cuatro, cinco);
  srand(time(0));
  AVLTree raiz = avltree_crear();
  // int nums[N_TO_PRINT] = {1, 24, 16, 10, 8, 3, 4};
  int nums[N_TO_PRINT] = {1, 3, 0, 4, 5};
  for (int i=0; i <N_TO_PRINT; i++) {
    raiz = avltree_insertar(raiz, nums[i]);
    avltree_imprimir(raiz);
    printf("Nodo agregado: %d Altura de %d: %d\n", nums[i], raiz->dato, avltree_altura(raiz));
  }
  // printf("Nodo a eliminar: %d\n", nums[(N_TO_PRINT-1)/2]);
  // raiz = avltree_eliminar(raiz,3);
  // avltree_imprimir(raiz);
  raiz = avltree_eliminar(raiz, 0);
  avltree_imprimir(raiz);
  avltree_destruir(raiz);




  // BHeap heap = bheap_crear();
  // bheap_insertar(heap, 3);
  // bheap_insertar(heap, 1);
  // bheap_insertar(heap, 7);
  // bheap_insertar(heap, 0);
  // bheap_insertar(heap, 6);
  // bheap_insertar(heap, 10);
  // bheap_imprimir(heap);
  // bheap_eliminar_maximo(heap);
  // bheap_imprimir(heap);
  // bheap_destruir(heap);

//  int arr[101];
//  for (int i=1; i<=101; i++) {
//    arr[i] = rand() % 500;
//  }
//   size_t tamanio = 100;
//   for (int i=1;i<=tamanio; i++) printf("%d ", arr[i]);
//   puts("");
//   heapify(arr, tamanio);
//   for (int i=1;i<=tamanio; i++) printf("%d ", arr[i]);
//   puts("");

  // srand(time(0));
  // PCola pcola = cola_prioridad_crear();
  // for (int i=0; i<N_TO_PRINT; i++) {
  //   cola_prioridad_insertar(&pcola, rand()%(N_TO_PRINT+N_TO_PRINT/2)+1);
  //   cola_prioridad_imprimir(pcola);
  // }
  //  cola_prioridad_destruir(pcola);



  return 0;
}
