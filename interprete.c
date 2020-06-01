#include "itree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 25

void imprimir_intervalo(double izq, double der) {
  printf("[%0.2f, %0.2f] ", izq, der);
}

int leer_intervalo(char *string, int *izq, int *der) {
  char buff[4];
  sscanf(string, "%[^[]%f, %f]", buff, *izq, *der);
  return (*izq <= *der);
}

void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  double izq, der;
  
  scanf(input);
  while (strcmp(input, "salir") != 0) {
    if (strcmp(input, "bfs") == 0) {
      itree_recorrer_bfs(arbol, imprimir_intervalo);
      puts("");
    } else if (strcmp(input, "dfs") == 0) {
      itree_recorrer_dfs(arbol, imprimir_intervalo);
      puts("");
    } else {
      if (leer_intervalo(input, &izq, &der)) {
        if (input[0] == 'i') arbol = itree_insertar(arbol, izq, der);
        else if (input[0] == 'e') arbol = itree_eliminar(arbol, izq, der);
        else if (input[0] == '?') {
        if (itree_intersecar(arbol, izq, der) == NULL) puts("No\n");
        else puts("Si\n");
        }
      } else puts("Intervalo no valido.\n");
    }
    scanf(input);
  }
  
  free(input);
  itree_destruir(arbol);
}

int main() {
  interface();
  return 0;
}