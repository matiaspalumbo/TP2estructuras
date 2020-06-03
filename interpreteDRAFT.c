#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "itree.h"
#include "interprete.h"

#define STR_SIZE 100

void imprimir_enum(enum EstadoInput estado) {
  switch (estado) {
    case Salir: puts("Salir"); break;
    case RecorridoBFS: puts("RecorridoBFS"); break;
    case RecorridoDFS: puts("RecorridoDFS"); break;
    case Insertar: puts("Insertar"); break;
    case Eliminar: puts("Eliminar"); break;
    case Intersecar: puts("Intersecar"); break;
    case ComandoNoValido: puts("ComandoNoVálido"); break;
    case IntervaloNoValido: puts("IntervaloNoValido"); break;
    case ComandoVacio: puts("ComandoVacio"); break;
  }
}


void validar_char(enum EstadoInput* estado, char input, int c) {
  char* buff = "  [0, 0]\n";
  if (c == 0) {
    if (input == 'i')
      *estado =  Insertar;
    else if (input == 'e')
      *estado = Eliminar;
    else
      *estado = (input == '?') ? Intersecar : ComandoNoValido;
  }
  else if (buff[c] != input)
    *estado = ComandoNoValido;
}


enum EstadoInput validar_input(char* input, double* izq, double* der) {
  enum EstadoInput estado;
  if (strcmp(input, "salir\n") == 0)
    estado = Salir;
  else if (strcmp(input, "bfs\n") == 0)
    estado = RecorridoBFS;
  else if (strcmp(input, "dfs\n") == 0)
    estado = RecorridoDFS;
  else {
    char *buff = malloc(sizeof(char)*STR_SIZE);
    strcpy(buff, input);
    estado = Salir;
    int i = 0, j = 0, segundoNum = 0;
    while (estado != ComandoNoValido && estado != ComandoVacio && estado != IntervaloNoValido && input[i] != '\0') {
      if (j != 3 && j != 6) {
        validar_char(&estado, input[i], j);
        j++;
        i++;
      } else {
      if ((input[i] > 47 && input[i] < 58) || input[i] == 45) {
        memcpy(buff, &input[(segundoNum) ? 2 : 3], strlen(input) - ((segundoNum) ? 1 : 2)); 
        sscanf(buff, "%lf%[^\n]", ((segundoNum) ? der : izq), input);
        if (j == 3)
          segundoNum = 1;
        j++;
        i = 0;
      } else
        estado = ComandoNoValido;
      }
    }
    free(buff);
    if ((estado == Insertar || estado == Eliminar || estado == Intersecar) && (*izq) > (*der))
      estado = IntervaloNoValido;
    else if (estado == Salir)
      estado = ComandoVacio;
  }
  return estado;
}


void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  enum EstadoInput estado;
  double izq, der;
  fgets(input, STR_SIZE, stdin);
  estado = validar_input(input, &izq, &der);
  while (estado != Salir) {
    // imprimir_enum(estado);
    switch(estado) {
      case RecorridoBFS:
        itree_recorrer_bfs(arbol, imprimir_intervalo);
        puts("");
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
      case ComandoNoValido:
        puts("Comando no válido.");
      break;
      case IntervaloNoValido:
        puts("El extremo izquierdo debe ser menor o igual que el extremo derecho."); 
      break;
      default:
        puts("Por favor, inserte un comando.");
    }
    fgets(input, STR_SIZE, stdin);
    estado = validar_input(input, &izq, &der);
  }
  free(input);
  itree_destruir(arbol);
}


