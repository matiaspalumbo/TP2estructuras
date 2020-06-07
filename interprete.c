#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "itree.h"
#include "interprete.h"

#define STR_SIZE 100

void imprimir_enum(enum EstadoInput estado) {
  switch (estado) {
    case ComandoNoValido: puts("NoValido"); break;
    case ComandoVacio: puts("ComandoVacio"); break;
    case IntervaloNoValido: puts("IntervaloNoValido"); break;
    case Salir: puts("Salir"); break;
    case RecorridoBFS: puts("RecorridoBFS"); break;
    case RecorridoDFS: puts("RecorridoDFS"); break;
    case Insertar: puts("Insertar"); break;
    case Eliminar: puts("Eliminar"); break;
    case Intersecar: puts("Intersecar"); break;
  }
}


void validar_char(enum EstadoInput* estado, char input, int c) {
  char* plantilla = "  [0, 0]\n";
  if (c == 0) {
    if (input == 'i')
      *estado =  Insertar;
    else if (input == 'e')
      *estado = Eliminar;
    else
      *estado = (input == '?') ? Intersecar : ComandoNoValido;
  }
  else if (plantilla[c] != input)
    *estado = ComandoNoValido;
}


// PREGUNTAR QUE PASA CON SSCANF si en por ejemplo sscanf(input, "%c [%lf%[^\n]\n", ((segundoNum) ? der : izq), input) si el string no es de esa forma
enum EstadoInput validar_input(char* input, double* izq, double* der) {
  enum EstadoInput estado;
  if (strcmp(input, "salir\n") == 0)
    estado = Salir;
  else if (strcmp(input, "bfs\n") == 0)
    estado = RecorridoBFS;
  else if (strcmp(input, "dfs\n") == 0)
    estado = RecorridoDFS;
  else {
    estado = ComandoVacio;
    // int i = 0, j = 0, segundoNum = 0;
    char comando, espacio1, corcheteOpen, coma, espacio2, corcheteClosed;
    printf("%d\n", sscanf(input, "%c%c%c%lf%c%c%lf%c\n", &comando, &espacio1, &corcheteOpen, izq, &coma, &espacio2, der, &corcheteClosed));
    // printf("%c", comando);printf("%c", espacio1);printf("%c", corcheteOpen);printf("%lf", *izq);printf("%c", coma);printf("%c", espacio2);printf("%lf", *der);printf("%c\n", corcheteClosed);
  //   while (estado != ComandoNoValido && input[i] != '\0' && input[i] != '\n') {
  //     if (j != 3 && j != 6) {
  //       validar_char(&estado, input[i], j);
  //       j++;
  //       i++;
  //     } else if ((input[i] > 47 && input[i] < 58) || input[i] == 45) {
  //       input = &input[(segundoNum) ? 2 : 3];
        // sscanf(input, "%lf%[^\n]\n", ((segundoNum) ? der : izq), input);
  //       if (j == 3)
  //         segundoNum = 1;
  //       j++;
  //       i = 0;
  //     } else
  //       estado = ComandoNoValido;
  //   }
  //   if (estado != ComandoNoValido && estado != ComandoVacio && *izq > *der)
  //     estado = IntervaloNoValido;
  // }
    if (comando == 'i') estado = Insertar;
    else if (comando == 'e') estado = Eliminar;
    else estado = Intersecar;
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
  while  (estado != Salir) {
    switch(estado) {
      case RecorridoBFS:
        // itree_recorrer_bfs(arbol, imprimir_intervalo);
        itree_recorrer_bfs(arbol, doNothing);
        puts("");
      break;
      case RecorridoDFS:
        itree_recorrer_dfs(arbol, doNothing);
        puts("");
      break;
      case Insertar:
        pretty_print(arbol);
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
        puts("Entrada no válida.");
      break;
      case IntervaloNoValido:
        puts("El extremo izquierdo....");
      break;
      default:;
    }
    fgets(input, STR_SIZE, stdin);
    estado = validar_input(input, &izq, &der);
  }
  free(input);
  itree_destruir(arbol);
}


