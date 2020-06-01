#include "itree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 40

void imprimir_intervalo(ITree arbol) {
  if (!itree_empty(arbol)) printf("[%f, %f] ", arbol->izq, arbol->der);
}

// int leer_intervalo(char *string, char buff[], double **izq, double **der) {
//   sscanf(string, "%2s%lf, %lf]", buff, *izq, *der);
//   printf("%lf, %lf\n", **izq, **der);
//   return (**izq <= **der);
//   return 1;
// }

void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  double izq, der;
  char buff;

  scanf("%s", input);
  while (strcmp(input, "salir") != 0) {
    if (strcmp(input, "bfs") == 0) {
    //   itree_recorrer_bfs(arbol, imprimir_intervalo);
      puts("");
    } else if (strcmp(input, "dfs") == 0) {
      itree_recorrer_dfs(arbol, imprimir_intervalo);
      puts("");
    } else {
      printf("%c, %c", input[0], input[1]);
      sscanf(input, "%c[%lf,%lf]", &buff, &izq, &der);
      // printf("%f, %f\n", izq, der);
      if (izq <= der) {
        if (input[0] == 'i') {
          arbol = itree_insertar(arbol, izq, der);
          // printf("%f, %f\n", izq, der);
        }
        else if (input[0] == 'e') arbol = itree_eliminar(arbol, izq, der);
        else if (input[0] == '?') {
          if (itree_intersecar(arbol, izq, der) == NULL) puts("No");
          else puts("Si");
        }
      } else puts("Intervalo no valido.");
    }
    scanf("%s", input);
  }
  
  free(input);
  itree_destruir(arbol);
}

int main() {
  interface();
  return 0;
}