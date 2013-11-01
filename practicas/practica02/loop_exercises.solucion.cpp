/** \file loop_exercises.solucion.cpp
  * Practica 2 del Máster Universitario de computación gráfica y simulación
  * Ejercicios con bucles, Range-loops aplicados en vectores y maps
  * \date 1 de Noviembre de 2013
  */

#include <iostream>
#include <vector>
#include <map>
#include <math.h>       /* Para el uso de floor */

int main()
{
    //! Sin usar la sintaxis c++11:

	std::cout << "\033[33m" << "SOLUCIONES DE LA PRACTICA 2 del MUCGS" << std::endl << std::endl;
	std::cout << "\033[33m" << "Primera parte: Sin código c++11" << "\033[0m" << std::endl << std::endl;

    //! Ejercicio 1: Crea un bucle que imprime de 1 a 5.

	std::cout << "Ejercicio 1: Bucle con salida 1 al 5" << std::endl;
	for ( int i = 1; i <= 5; i++ )
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
    
    //! Ejercicio 2: Crea un bucle con un iterador a un vector que muestra cadenas de texto.

	std::cout << "Ejercicio 2: Bucle que recorre un vector de cadenas imprimiéndolas" << std::endl;
	std::vector< std::string > mi_vector = { //! Define el vector de cadenas
	"Lunes", "Martes", "Miércoles", "Jueves", "Viernes" }; //! Añade los dias lectivos mucgs al vector
	std::vector< std::string >::iterator mi_it_vector = mi_vector.begin(); //! Define iterador y lo inicializa
	for ( ; mi_it_vector != mi_vector.end(); mi_it_vector++ ) //! Recorre el vector e imprime sus elementos
	{
		std::cout << *mi_it_vector << " "; 
	}
	std::cout << std::endl << std::endl;

	
    //! Ejercicio 3: Crea un bucle que extrae cadenas y numeros de un map y los guarda en otro map como char* y entero.

	std::cout << "Ejercicio 3: Bucle que toma un map de string/float y genera un map char*/int" << std::endl;
	std::map< std::string, float > mi_map_sf = { //! Define el map de string/float y rellena con cotizaciones
	{ "Euro", 1.0f }, 
	{ "Dolar", 0.73f },
	{ "Libra", 1.18f },
	{ "Yen", 0.01f } };
	std::cout << "Contenido del map compuesto por string/float" << std::endl;
	std::map< const char*, int > mi_map_ci; //! Define el map char*/int
	std::map< std::string, float >::iterator mi_it_map = mi_map_sf.begin(); //! Define iterador y lo inicializa
	for(; mi_it_map != mi_map_sf.end(); mi_it_map++) //! Recorre el map y convierte sus elementos
	{
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl; //! Muestra el contenido
		const char* mi_char = mi_it_map->first.c_str(); //! Define char y convierte string de puntero a char
		mi_map_ci[mi_char] = (int)mi_it_map->second; //! Guarda el float como int
	}
	std::cout << "Contenido del map compuesto por char/integer" << std::endl;
	std::map< const char*, int >::iterator mi_it_ci = mi_map_ci.begin(); //! Define iterador y lo inicializa
	for(; mi_it_ci != mi_map_ci.end(); mi_it_ci++)
	{
		std::cout << mi_it_ci->first << " - " << mi_it_ci->second << std::endl;
	}
	std::cout << std::endl;
  
    //! Ejercicio 4. Cambia el map anterior añadiendo "yeah!" y redondeando los números

	std::cout << "Ejercicio 4: Bucle que toma un map de string/float en el que añade yeah! y redondea" << std::endl;
	std::cout << "Contenido del map string/float antes de la modificación" << std::endl;
	mi_it_map = mi_map_sf.begin(); //! Vuelve a colocar el iterador al comienzo del map
	for (; mi_it_map != mi_map_sf.end(); mi_it_map++) //! Muestra el map antes de modifcarlo
	{
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl;
	}
		std::cout << "Contenido del map string/float después de la modificación" << std::endl;
	mi_it_map = mi_map_sf.begin(); //! Vuelve a colocar el iterador al comienzo del map
	for (; mi_it_map != mi_map_sf.end(); mi_it_map++)
	{
		std::string mi_str_mod = mi_it_map->first + "yeah!"; //! Añade "yeah! al string
		int mi_int = floor( mi_it_map->second + 0.5 ); //! Redondea la cotizacion
		mi_map_sf.erase( mi_it_map); //! Borra el elemento 
		mi_map_sf.insert( std::make_pair( mi_str_mod, mi_int ) ); //! Inserta el elemento modificado
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl;
	}
	std::cout << std::endl << std::endl;
      
    //! Ejercicio 5: Transformar los ejercicios 1, 2 y 3 en Range-loops de c++11.

	std::cout << "\033[33m" << "Segunda parte: Con código c++11" << "\033[0m" << std::endl << std::endl;
	std::cout << "Ejercicio 1: Bucle con salida 1 al 5 usando Range-Based Loop " << std::endl;
	for( auto i : { 1, 2, 3, 4, 5 } ) //! Bucle de 1 a 5 usando Range-loops sobre un vector
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Ejercicio 2: Bucle que muestra las cadenas de un vector usando Range vector" << std::endl;
	for ( auto mi_dia : mi_vector ) //! Recorre el vector dias lectivos mucgs e imprime sus elementos
	{
		std::cout << mi_dia << " "; 
	}
	std::cout << std::endl << std::endl;

	std::cout << "Ejercicio 3: Bucle cambia maps string/float->char*/int usando Range map" << std::endl;
	mi_map_sf.clear(); //! Borra los monedas con los yeah!	
	mi_map_sf = { //! Vuelve a rellenar con cotizaciones
	{ "Euro", 1.0f }, 
	{ "Dolar", 0.73f },
	{ "Libra", 1.18f },
	{ "Yen", 0.01f } };
	std::cout << "Contenido del map compuesto por string/float" << std::endl;
	mi_it_map = mi_map_sf.begin(); //! Inicializa iterador del map string/float
	for( auto mi_moneda : mi_map_sf ) //! Recorre el map y convierte sus elementos
	{
		std::cout << mi_moneda.first << " - " << mi_moneda.second << std::endl; //! Muestra el contenido
		const char* mi_char = mi_it_map->first.c_str(); //! Define char y convierte string de puntero a char
		mi_map_ci[mi_char] = (int)mi_it_map->second; //! Guarda el float como int
	}
	std::cout << "Contenido del map compuesto por char/integer" << std::endl;
	mi_it_ci = mi_map_ci.begin(); //! Inicializa el iterador del map char/int
	for( auto mi_moneda : mi_map_ci )
	{
		std::cout << mi_moneda.first << " - " << mi_moneda.second << std::endl;
	}
	std::cout << std::endl;
	    
    //! Ejercicio 6: Bucle que muestra una piramide de asteriscos de altura dada.    
    //!	
    //!	               **
    //!	              ****
    //!	             ******
    //!	            ********
    //!	           **********
    //!	          ************

	std::cout << "Ejercicio 5: Piramide de estrellas" << std::endl;
	int altura;
	std::cout << "Dime cuantas filas : ";
	std::cin >> altura;
	for ( int fila = 0; fila < altura; fila++ ) //! Recorre toda la altura
	{
		for ( int col = 1; col < altura - fila; col++ ) //! Recorre las columnas
			std::cout << ' ';                           //! Espacios de 1 a altura - fila
		for ( int col = 0; col <=  2*fila; col++ )      //! Recorre la fila
			std::cout << '*';                           //! Asteriscos doble que el numero de filas + 1
		std::cout << std::endl;
	}
	return 0;
}
