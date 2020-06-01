#include "itree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STR_SIZE 100

void imprimir_intervalo(ITree arbol) {
  if (!itree_empty(arbol)) printf("[%lf, %lf] ", arbol->izq, arbol->der);
}


// int leer_intervalo(char *string, char buff[], double **izq, double **der) {
//   sscanf(string, "%2s%lf, %lf]", buff, *izq, *der);
//   printf("%lf, %lf\n", **izq, **der);
//   return (**izq <= **der);
//   return 1;
// }


// int validar_input(char* input) {
//   int first = (input[0] == 'i' || input[0] == 'e' || input[0] == '?') && input[1] == ' ';
//   printf("validar: %d\n", atoi(&input[2]));
//   int second;
//   if (input[2] == '0') second = 1;
//   else second = (isdigit(atoi(&input[2])) == 0) ? 0 : isdigit(atoi(&input[2]));
//   return first && second;
// }

enum EstadoInput {NoValido, Salir, RecorridoBFS, RecorridoDFS, Insertar, Eliminar, Intersecar};

void imprimir_enum(enum EstadoInput estado) {
  switch (estado) {
    case NoValido: puts("NoValido"); break;
    case Salir: puts("Salir"); break;
    case RecorridoBFS: puts("RecorridoBFS"); break;
    case RecorridoDFS: puts("RecorridoDFS"); break;
    case Insertar: puts("Insertar"); break;
    case Eliminar: puts("Eliminar"); break;
    case Intersecar: puts("Intersecar"); break;
  }
}

/* validar_input: (hacer enum para diferentes casos)
[SI EL INTERVALO ES VÁLIDO QUE YA LO ALMACENE?]
- igual a "salir"
- igual a "bfs"
- igual a "dfs"
Sino, debe verificar que:
- 1er char == 'i', 'e', '?'
- 2do char == ' '
- 3er char == '['
- después de eso, viene un número que puede o no tener punto en el medio (contador de puntos)? (funcion auxiliar que escanee numeros?)
- 1er char después del num. == ','
- 2do char después del num. == ' '
- después, viene otro número que puede o no tener punto en el medio
- 1er char después del segundo num. == ']'
- 2do char después del segundo num. == '\n'
*/

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
  // char buff[STR_SIZE];
  // double izq1, der1;
  if (strcmp(input, "salir\n") == 0)
    return Salir;
  else if (strcmp(input, "bfs\n") == 0)
    return RecorridoBFS;
  else if (strcmp(input, "dfs\n") == 0)
    return RecorridoDFS;
  else {
    char *buff = malloc(sizeof(char)*STR_SIZE);
    // char *buff = malloc(sizeof(char)*STR_SIZE);
    strcpy(buff, input);
    // puts("Entró al else");
    enum EstadoInput estado = Salir;
    int i = 0, j = 0, segundoNum = 0;
    while (estado != NoValido && input[i] != '\0') {
      // printf("iterando... [i: %d, j: %d] - %c - %d\n", i, j, input[i], (int) input[i]);
        // printf("segundoNum: %d\n", segundoNum);
        // printf("buff: %s\n", input);
      if (j != 3 && j != 6) {
        validar_char(&estado, input[i], j);
        j++;
        i++;
      } else {
        // printf("entró al else de los números: %c\n", input[i]);
      if (input[i] > 47 && input[i] < 58) {
        // printf("segundoNum: %d\n", segundoNum);
        // printf("1- buffer: %s - input: %s\n", buff, input);
        memcpy(buff, &input[((segundoNum) ? 2 : 3)], strlen(input) - ((segundoNum) ? 1 : 2)); 
        // input = &input[3];
        // printf("2- buffer: %s - input: %s\n", buff, input);
        // input[0] = '\0';
        // printf("3- buffer: %s - input: %s\n", buff, input);
        // subbuff[4] = '\0';
        sscanf(buff, "%lf%[^\n]", ((segundoNum) ? der : izq), input);
        // printf("4- buffer: %s - input: %s\n", buff, input);
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


// Cambiar las funciones que recorren para que directamente impriman!!!

void interface() {
  char *input = malloc(sizeof(char) * STR_SIZE);
  ITree arbol = itree_crear();
  enum EstadoInput estado;
  double izq, der;
  do {
    fgets(input, STR_SIZE, stdin);
    estado = validar_input(input, &izq, &der);
    // imprimir_enum(estado);
    switch(estado) {
      case RecorridoBFS:
        // itree_recorrer_bfs(arbol, imprimir_intervalo);
      break;
      case RecorridoDFS:
        itree_recorrer_dfs(arbol);
        // pretty_print(arbol);
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
      default:;
        puts("Intervalo no valido.");
    }
  } while  (estado != Salir);
  free(input);
  itree_destruir(arbol);
}



// enum ValidezInput validar_input(char* input) {
//   int valido = 1, i = 0, j = 0;
//   while (valido && input[i] != '\0') {
//     if (j != 3 && j != 5) {
//       valido = validar_char(input[j], j);
//       j++;
//       i++;
//     } else {
//       valido = (input[i] == '0') ? 1 : (isdigit(atoi(&input[i])) != 0);
//       if (valido == 0 && i > 3) {
//         j++;
//         valido = 1;
//       }
//       i++;
//     }
//   }
//   return valido;
// }

// int validar_char(char input, int c) {
//   char* buff = "  [0.0, 0.0]\n";
//   return (c != 0) ? (buff[c] == input) : (input == 'i' || input == 'e' || input == '?');
//   // switch (c) {
//   //   case 0:
//   //     return input == 'i' || input == 'e' || input == '?';
//   //   case 1:
//   //     return input == ' ';
//   //   case 2:
//   //     return input == '[';
//   //   case 3:
//   //     return input == ',';
//   //   case 4:
//   //     return input == ']';
//   //   default:
//   //     return 0;
//   // }
// }
// ---------


// void interface() {
//   char *input = malloc(sizeof(char) * STR_SIZE);
//   ITree arbol = itree_crear();
//   double izq, der;
//   char buff[4];
  
//   fgets(input, STR_SIZE, stdin);
//   while (strcmp(input, "salir\n") != 0) {
//     printf("%d\n", (int) strlen(input));
//     printf("%s\n", input);
//     if (strcmp(input, "bfs\n") == 0) {
//     //   itree_recorrer_bfs(arbol, imprimir_intervalo);
//       puts("");
//     } else if (strcmp(input, "dfs\n") == 0) {
//       itree_recorrer_dfs(arbol, imprimir_entero);
//       puts("");
//     } else if (validar_input(input)) {
//       sscanf(input, "%[^[][%lf, %lf]", buff, &izq, &der);
//       printf("%s\n", buff);
//       printf("[%lf, %lf]\n", izq, der);
//       if (izq <= der) {
//         if (input[0] == 'i') arbol = itree_insertar(arbol, izq, der);
//         else if (input[0] == 'e') arbol = itree_eliminar(arbol, izq, der);
//         else if (input[0] == '?') {
//           if (itree_intersecar(arbol, izq, der) == NULL) puts("No");
//           else puts("Si");
//         }
//       } else puts("Intervalo no valido.");
//     }
//     fgets(input, STR_SIZE, stdin);
//   }
  
//   free(input);
//   itree_destruir(arbol);
// }


int main() {
  interface();
  // double izq = 0.0, der = 0.0;
  // char *input = malloc(sizeof(char) * STR_SIZE);
  // fgets(input, STR_SIZE, stdin);
  // imprimir_enum(validar_input(input, &izq, &der));
  // printf("[%.10lf, %.10lf]\n", izq, der);
  // free(input);
  return 0;
}