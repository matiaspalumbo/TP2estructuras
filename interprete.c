#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "itree.h"
#include "interprete.h"

#define STR_SIZE 60

void imprimir_enum(enum EstadoInput estado) {
  switch (estado) {
    case ComandoNoValido: puts("NoValido"); break;
    // case ComandoVacio: puts("ComandoVacio"); break;
    case IntervaloNoValido: puts("IntervaloNoValido"); break;
    case Salir: puts("Salir"); break;
    case RecorridoBFS: puts("RecorridoBFS"); break;
    case RecorridoDFS: puts("RecorridoDFS"); break;
    case Insertar: puts("Insertar"); break;
    case Eliminar: puts("Eliminar"); break;
    case Intersecar: puts("Intersecar"); break;
  }
}


enum EstadoInput validar_char(enum EstadoInput estado, char input, int c) {
  char* plantilla = "  [, ]";
  if (c == 0) {
    if (input == 'i')
      return Insertar;
    else if (input == 'e')
      return Eliminar;
    else
      return (input == '?') ? Intersecar : ComandoNoValido;
  }
  else if (plantilla[c] != input)
    return ComandoNoValido;
  else return estado;
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
    char* charsNoNumeros = malloc(sizeof(char)*6), *finalInput = malloc(sizeof(char)*STR_SIZE);
    int numEscaneos = sscanf(input, "%c%c%c%lf%c%c%lf%c%s", &charsNoNumeros[0], &charsNoNumeros[1], &charsNoNumeros[2],
                             izq, &charsNoNumeros[3], &charsNoNumeros[4], der, &charsNoNumeros[5], finalInput);
    if (numEscaneos == 8) {
      for (int i = 0; i < 6 && estado!= ComandoNoValido; i++)
        estado = validar_char(estado, charsNoNumeros[i], i);
      if (estado != ComandoNoValido && *izq > *der)
        estado = IntervaloNoValido;
    } else
      estado = ComandoNoValido;
    free(charsNoNumeros);
    free(finalInput);
  }
return estado;
}


void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  ITree interseccion;
  enum EstadoInput estado;
  double izq, der;
  fgets(input, STR_SIZE, stdin);
  estado = validar_input(input, &izq, &der);
  while  (estado != Salir) {
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
        interseccion = itree_intersecar(arbol, izq, der);
        if (interseccion) {
          printf("Si, ");
          imprimir_intervalo(interseccion);
          puts("");
        } else {
          puts("No");
        }
      break;
      case ComandoNoValido:
        puts("Comando no válido.");
      break;
      default:
        puts("El extremo izquierdo debe ser menor o igual al extremo derecho.");
    }
    fgets(input, STR_SIZE, stdin);
    estado = validar_input(input, &izq, &der);
  }
  free(input);
  itree_destruir(arbol);
}


