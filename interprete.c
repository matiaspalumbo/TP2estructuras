#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "itree.h"
#include "interprete.h"

#define STR_SIZE 100


void validar_char(enum EstadoInput* estado, char input, int c) {
  char* buff = "  [0, 0]\n";
  if (c == 0) {
    if (input == 'i')
      *estado =  Insertar;
    else if (input == 'e')
      *estado = Eliminar;
    else
      *estado = (input == '?') ? Intersecar : NoValido;
  }
  else if (buff[c] != input)
    *estado = NoValido;
}


enum EstadoInput validar_input(char* input, double* izq, double* der) {
  if (strcmp(input, "salir\n") == 0)
    return Salir;
  else if (strcmp(input, "bfs\n") == 0)
    return RecorridoBFS;
  else if (strcmp(input, "dfs\n") == 0)
    return RecorridoDFS;
  else {
    char *buff = malloc(sizeof(char)*STR_SIZE);
    strcpy(buff, input);
    enum EstadoInput estado = Salir;
    int i = 0, j = 0, segundoNum = 0;
    while (estado != NoValido && input[i] != '\0') {
      if (j != 3 && j != 6) {
        validar_char(&estado, input[i], j);
        j++;
        i++;
      } else {
      if (input[i] > 47 && input[i] < 58) {
        memcpy(buff, &input[(segundoNum) ? 2 : 3], strlen(input) - ((segundoNum) ? 1 : 2)); 
        sscanf(buff, "%lf%[^\n]", ((segundoNum) ? der : izq), input);
        if (j == 3) {
          segundoNum = 1;
          j = 4;
        } else j = 7;
        i = 0;
      } else
        estado = NoValido;
      }
    }
    free(buff);
    if ((estado == Insertar || estado == Eliminar || estado == Intersecar) && (*izq) > (*der))
      estado = NoValido;
    return (estado == Salir) ? NoValido : estado;
  }
}


void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  enum EstadoInput estado;
  double izq, der;
  fgets(input, STR_SIZE, stdin);
  estado = validar_input(input, &izq, &der);
  while  (estado != Salir) {
    switch(estado) {
      case RecorridoBFS:
      break;
      case RecorridoDFS:
        itree_recorrer_dfs(arbol, imprimir_intervalo);
        puts("");
      break;
      case Insertar:
        arbol = itree_insertar(arbol, izq, der);
      break;
      case Eliminar:
        arbol = itree_eliminar(arbol, izq, der);
      break;
      case Intersecar:
        if (!itree_intersecar(arbol, izq, der))
          puts("No");
        else
          puts("Si");
      break;
      default:
        puts("Entrada no válida.");
    }
    fgets(input, STR_SIZE, stdin);
    estado = validar_input(input, &izq, &der);
  }
  free(input);
  itree_destruir(arbol);
}


