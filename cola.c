#include "cola.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* Archivo con la implementación de la estructura cola. */


Cola cola_crear() {
  Cola cola = malloc(sizeof(Cola));
  cola->primero = NULL;
  cola->ultimo = NULL;
  return cola;
}

int cola_es_vacia(Cola cola) {
  return cola->ultimo == NULL;
}

ITNodo *cola_primero(Cola cola) {
  return cola->primero->dato;
}

void cola_encolar(Cola cola, ITNodo *dato) {
  CNodo *nuevoNodo = malloc(sizeof(CNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  if (cola_es_vacia(cola))
    cola->primero  = nuevoNodo;
  else
    cola->ultimo->sig = nuevoNodo;
  cola->ultimo = nuevoNodo;
}

void cola_desencolar(Cola cola) {
  if (!cola_es_vacia(cola)) {
    CNodo *nodoAEliminar = cola->primero;
    if (cola->ultimo == cola->primero) cola->ultimo = NULL;
    cola->primero = cola->primero->sig;
    free(nodoAEliminar);
  }
}

void cola_destruir(Cola cola) {
  for (CNodo *nodo = cola->primero; nodo != NULL; nodo = nodo->sig)
    free(nodo);
  free(cola);
}