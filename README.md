# TP2estructuras



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
