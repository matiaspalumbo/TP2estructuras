#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "interprete.h"

#define STR_SIZE 60


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


enum EstadoInput validar_input(char* input, Intervalo *intv) {
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
                             &(intv->izq), &charsNoNumeros[3], &charsNoNumeros[4], &(intv->der), &charsNoNumeros[5], finalInput);
    if (numEscaneos == 8) {
      estado = Salir;
      for (int i = 0; i < 6 && estado!= ComandoNoValido; i++) {
        estado = validar_char(estado, charsNoNumeros[i], i);
      }
      if (estado != ComandoNoValido && intv->izq > intv->der)
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
  Intervalo* intv = malloc(sizeof(Intervalo));
  fgets(input, STR_SIZE, stdin);
  estado = validar_input(input, intv);
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
        arbol = itree_insertar(arbol, intv);
      break;
      case Eliminar:
        arbol = itree_eliminar(arbol, intv);
      break;
      case Intersecar:
        interseccion = itree_intersecar(arbol, intv);
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
    estado = validar_input(input, intv);
  }
  free(input);
  free(intv);
  itree_destruir(arbol);
}


