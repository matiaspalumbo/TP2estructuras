#include "itree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 30

void imprimir_intervalo(double izq, double der) {
  printf("[%f, %f] ", izq, der);
}

void leer_intervalo(char *string, int *izq, int *der) {
  char buff[4];
  sscanf(string, "%[^[]%d, %d]", buff, *izq, *der);
}

int main() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  ITree aux;
  
  scanf(input);
  while (strcmp(input, "salir") != 0) {
    if (strcmp(input, "bfs") == 0) {
      itree_recorrer_bfs(arbol, imprimir_intervalo);
      puts("");
    } else if (strcmp(input, "dfs") == 0) {
      itree_recorrer_dfs(arbol, imprimir_intervalo);
      puts("");
    } else {
      double izq, der;
      leer_intervalo(input, &izq, &der);
      if (input[0] == 'i') arbol = itree_insertar(arbol, izq, der);
      else if (input[0] == 'e') arbol = itree_eliminar(arbol, izq, der);
      else if (input[0] == '?') {
        aux = itree_intersecar(arbol, izq, der);
        if (aux == NULL) puts("Si");
        else puts("No");
      }
    }
    scanf(input);
  }
  
  free(input);
  itree_destruir(arbol);

  return 0;
}