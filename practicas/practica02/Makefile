## Compilador a usar, en este caso C++
CC=g++ 
#Objetivos
OBJ = loop_exercises.solucion.cpp
#Mensaje1
MSG1 = "Compilando programa..."
MSG2 = "Generando documentación..."

all: mensaje1 loop_exercises.solucion mensaje2 doc

loop_exercises.solucion: $(OBJ)
	$(CC) $^ -o $@ -std=c++0x

doc: $(OBJ)
	doxygen Doxyfile

mensaje1: 
	@echo $(MSG1)

mensaje2:
	@echo $(MSG2)
	

