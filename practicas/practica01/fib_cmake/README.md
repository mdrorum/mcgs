Crear una carpeta y Copiar los archivos: fib.cpp, CMakeLists.txt y Doxyfile

Dentro de la anterior carpeta, crear otra con el nombre: build

Situarse en esa carpeta: cd build

Para generar el fichero Makefile basta con escribir en el promt: cmake ..

Para generar código y la documentación basta con escribir en el prompt: make

Para probar el programa, escribir en el prompt: ./fib

La documentación generada se encuentra en las carpetas: html y latex

html: contiene el fichero "fib_8cpp.html" con la documentación del programa, que puede verse en el archivo: doc.html

latex: para la creación de documentación pdf
