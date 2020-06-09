# Makefile para el Trabajo Practico 2 de Estructuras de Datos y Algoritmos I

# Macros.
INTERPRETE_MAIN = interprete
ITREE = itree.c
COLA = cola.c
INTERPRETE = interprete.c
FLAGS = -Wall -Wextra -Werror -std=c99 -g


# Ejecutable del Interprete.
$(INTERPRETE_MAIN) : main.c $(COLA:.c=.o) $(ITREE:.c=.o) $(INTERPRETE:.c=.o)
	gcc $(FLAGS) -o $@ $^

# Archivo objeto del Interprete.
$(INTERPRETE:.c=.o) : $(INTERPRETE) $(INTERPRETE:.c=.h) $(ITREE:.c=.h)
	gcc $(FLAGS) -c $(INTERPRETE)

# Archivo objeto de la implementación de Árboles de Intervalos.
$(ITREE:.c=.o) : $(ITREE) $(ITREE:.c=.h) $(COLA:.c=.h)
	gcc $(FLAGS) -c $(ITREE)

# Archivo objeto de la implementación de Colas.
$(COLA:.c=.o) : $(COLA) $(COLA:.c=.h)
	gcc $(FLAGS) -c $(COLA)

# Destino simbólico que borra todos los archivos con extensión .o cuando se invoca.
clean: 
	rm *.o

.PHONY : clean
