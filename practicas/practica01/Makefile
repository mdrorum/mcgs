## Compilador a usar, en este caso C++
CC=g++
#Objetivos
OBJ = fib.cpp
#Mensaje1
MSG1 = "Compilando programa..."
MSG2 = "Generando documentación..."

all: mensaje1 fib.exe mensaje2 doc

fib.exe: $(OBJ)
	$(CC) fib.cpp -o fib
#	$(CC) $^ -o $@

doc: $(OBJ)
	doxygen Doxyfile

mensaje1: 
	@echo $(MSG1)

mensaje2:
	@echo $(MSG2)
	

