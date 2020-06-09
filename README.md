  
  
  if (balance < -1 && (izq > nodo->right->izq || (izq == nodo->right->izq && der > nodo->right->der))) {
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1 && (izq < nodo->left->izq || (izq == nodo->left->izq && der < nodo->left->der))) {
    nodo = rotacion_a_derecha(nodo);
  } else if (balance < -1) {
    nodo->right = rotacion_a_derecha(nodo->right);
    nodo = rotacion_a_izquierda(nodo);
  } else if (balance > 1) {
    nodo->left = rotacion_a_izquierda(nodo->left);
    nodo = rotacion_a_derecha(nodo);
  }


        /* El intervalo en cuestión no se interseca con la raíz del árbol, pero si su subárbol izquierdo es no vacío
      y el ext. izq. está acotado por el máximo de la raíz del subárbol izquierdo, entonces es posible que haya
      intersección en el subárbol izquierdo.*/




// void pretty_print_aux(ITree nodo, int space) { 
//   if (itree_empty(nodo)) 
//     return; 
//   space += 15; 
//   pretty_print_aux(nodo->right, space); 
//   printf("\n"); 
//   for (int i = 15; i < space; i++) 
//       printf(" "); 
//   printf("[%0.0f, %0.0f]{%0.0f}(%d)", nodo->izq, nodo->der, nodo->max, itree_altura(nodo));
//   pretty_print_aux(nodo->left, space); 
// } 

// void pretty_print(ITree nodo) {
//   puts("");puts("");
//   pretty_print_aux(nodo, 0);
//   puts("");puts("");puts("");puts("");
// }




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



// printf("Izq Der: ");imprimir_intervalo(nodo);puts("");

void imprimir_enum(enum EstadoInput estado) {
  switch (estado) {
    case ComandoNoValido: puts("NoValido"); break;
    case IntervaloNoValido: puts("IntervaloNoValido"); break;
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
*/# TP2estructuras







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
