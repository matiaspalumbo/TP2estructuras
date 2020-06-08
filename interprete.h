#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

// enum EstadoInput {Salir, RecorridoBFS, RecorridoDFS, Insertar, Eliminar, Intersecar, IntervaloNoValido, ComandoNoValido, ComandoVacio};
enum EstadoInput {ComandoNoValido, IntervaloNoValido, Salir, RecorridoBFS, RecorridoDFS, Insertar, Eliminar, Intersecar};

// typedef struct _Estados {
  // enum EstadoInput estado;
  // enum TipoError tipoError;
// } Estados;


enum EstadoInput validar_char(enum EstadoInput estado, char input, int c);

enum EstadoInput validar_input(char* input, double* izq, double* der);

void interface();


#endif /* __INTERPRETE_H__ */
