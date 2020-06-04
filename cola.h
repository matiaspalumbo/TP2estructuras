#ifndef __SCOLA_H__
#define __SCOLA_H__

#include <stddef.h>
#include "itree.h"

/* Archivo de cabecera de la implementación de la estructura Cola usando 
nodos simplemente enlazados donde el tipo de dato es un Arbol de Intervalos, 
y una estructura auxiliar con el primer y último elemento. */


typedef struct _CNodo {
  ITNodo *dato;
  struct _CNodo *sig;
} CNodo;

typedef struct _Cola {
  CNodo *primero;
  CNodo *ultimo;
} *Cola;
/* primero: indica el índice de la posición del primer elemento de la cola, es decir, la posición del elemento a eliminar cuando se invoque desencolar; 
ultimo: indica el índice de la posición de último elemento de la cola, ie, si se invoca encolar, el elemento debe ser insertado en el casillero siguiente al que indica la variable. */



// Crea una nueva cola.
Cola cola_crear();

// Determina si la cola está vacía.
int cola_es_vacia(Cola cola);

// Toma una cola y devuelve el elemento en la primera posición.
ITNodo *cola_primero(Cola cola);

// Toma una cola y un elemento y agrega el elemento al fin de la cola.
void cola_encolar(Cola cola, ITNodo *dato);

// Toma una cola y elimina su primer elemento.
void cola_desencolar(Cola cola);

// Libera la memoria requerida para la cola.
void cola_destruir(Cola cola);


#endif /* __SCOLA_H__ */
