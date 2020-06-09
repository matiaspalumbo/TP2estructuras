#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__
# include "itree.h"

enum EstadoInput {ComandoNoValido, IntervaloNoValido, Salir, RecorridoBFS, RecorridoDFS, Insertar, Eliminar, Intersecar};


enum EstadoInput validar_char(enum EstadoInput estado, char input, int c);

enum EstadoInput validar_input(char* input, Intervalo* intv);

void interface();


#endif /* __INTERPRETE_H__ */
