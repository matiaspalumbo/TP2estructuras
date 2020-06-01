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
