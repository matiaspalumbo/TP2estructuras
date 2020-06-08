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
      imprimir_enum(estado);
      if (estado != ComandoNoValido && *izq > *der)
        estado = IntervaloNoValido;
    } else
      estado = ComandoNoValido;
    free(charsNoNumeros);
    free(finalInput);
  }
return estado;
}

// enum EstadoInput validar_input(char* input, double* izq, double* der) {
//   enum EstadoInput estado;
//   if (strcmp(input, "salir\n") == 0)
//     estado = Salir;
//   else if (strcmp(input, "bfs\n") == 0)
//     estado = RecorridoBFS;
//   else if (strcmp(input, "dfs\n") == 0)
//     estado = RecorridoDFS;
//   else {
//     estado = ComandoVacio;
//     int i = 0, j = 0, segundoNum = 0;
//     while (estado != ComandoNoValido && input[i] != '\0' && input[i] != '\n') {
//       if (j != 3 && j != 6) {
//         validar_char(&estado, input[i], j);
//         j++;
//         i++;
//       } else if ((input[i] > 47 && input[i] < 58) || input[i] == 45) {
//         input = &input[(segundoNum) ? 2 : 3];
//         sscanf(input, "%lf%[^\n]\n", ((segundoNum) ? der : izq), input);
//         if (j == 3)
//           segundoNum = 1;
//         j++;
//         i = 0;
//       } else
//         estado = ComandoNoValido;
//     }
//     if (estado != ComandoNoValido && estado != ComandoVacio && *izq > *der)
//       estado = IntervaloNoValido;
//   }
//   return estado;
// }


void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  ITree interseccion;
  enum EstadoInput estado;
  double izq, der;
  fgets(input, STR_SIZE, stdin);
  estado = validar_input(input, &izq, &der);
  imprimir_enum(estado);
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
        if (!interseccion)
          puts("No");
        else {
          printf("Si, ");
          imprimir_intervalo(interseccion);
          puts("");
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
    imprimir_enum(estado);
  }
  free(input);
  itree_destruir(arbol);
}


