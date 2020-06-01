#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

enum EstadoInput {NoValido, Salir, RecorridoBFS, RecorridoDFS, Insertar, Eliminar, Intersecar};


void validar_char(enum EstadoInput* estado, char input, int c);

enum EstadoInput validar_input(char* input, double* izq, double* der);

void interface();


#endif /* __INTERPRETE_H__ */
