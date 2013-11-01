#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <math.h>       /* Para el uso de floor */
#define RESET   "\033[0m"       /* Resetea */
#define YELLOW  "\033[33m"      /* Amarillo */

int main()
{
    
    // non-c++11 syntax:

	std::cout << YELLOW << "SOLUCIONES DE LA PRACTICA 2 DEL MUCGS" << RESET << std::endl << std::endl;
	std::cout << YELLOW << "Primera parte: Sin código c++11" << RESET << std::endl << std::endl;

    // 1. create a for loop that prints numbers 1 to 5

	std::cout << "Ejercicio 1: Bucle con salida 1 al 5" << std::endl;
	for ( int i = 1; i <= 5; i++ )
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
    
    // 2. create a for loop that iterates through a vector of strings and print
    // them

	std::cout << "Ejercicio 2: Bucle que recorre un vector de cadenas imprimiéndolas" << std::endl;
	std::vector< std::string > mi_vector = { // Define el vector de cadenas
	"Lunes", "Martes", "Miércoles", "Jueves", "Viernes" }; // Añade los dias lectivos mucgs al vector
	std::vector< std::string >::iterator mi_it_vector = mi_vector.begin(); // Define iterador y lo inicializa
	for ( ; mi_it_vector != mi_vector.end(); mi_it_vector++ ) // Recorre el vector e imprime sus elementos
	{
		std::cout << *mi_it_vector << " "; 
	}
	std::cout << std::endl << std::endl;

	
    // 3. create a for loop that gets a map of <string, float> and returns a
    // new map of of (char*, int)

	std::cout << "Ejercicio 3: Bucle que toma un map de string/float y genera un map char*/int" << std::endl;
	std::map< std::string, float > mi_map_sf = { // Define el map de string/float y rellena con cotizaciones
	{ "Euro", 1.0f }, 
	{ "Dolar", 0.73f },
	{ "Libra", 1.18f },
	{ "Yen", 0.01f } };
	std::cout << "Contenido del map compuesto por string/float" << std::endl;
	std::map< const char*, int > mi_map_ci; // Define el map char*/int
	std::map< std::string, float >::iterator mi_it_map = mi_map_sf.begin(); // Define iterador y lo inicializa
	for(; mi_it_map != mi_map_sf.end(); mi_it_map++) // Recorre el map y convierte sus elementos
	{
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl; // Muestra el contenido
		const char* mi_char = mi_it_map->first.c_str(); // Define char y convierte string de puntero a char
		mi_map_ci[mi_char] = (int)mi_it_map->second; // Guarda el float como int
	}
	std::cout << "Contenido del map compuesto por char/integer" << std::endl;
	std::map< const char*, int >::iterator mi_it_ci = mi_map_ci.begin(); // Define iterador y lo inicializa
	for(; mi_it_ci != mi_map_ci.end(); mi_it_ci++)
	{
		std::cout << mi_it_ci->first << " - " << mi_it_ci->second << std::endl;
	}
	std::cout << std::endl;
  
    // 4. create a for loop that gets a map of <string, float> and updates the
    // same map so that it adds "yeah!" to each string and rounds the float
    // number. transform it in place.
    // You can't modify the key, therefore new key-value pairs must be inserted
    // and the old ones deleted.

	std::cout << "Ejercicio 4: Bucle que toma un map de string/float en el que añade yeah! y redondea" << std::endl;
	std::cout << "Contenido del map string/float antes de la modificación" << std::endl;
	mi_it_map = mi_map_sf.begin(); // Vuelve a colocar el iterador al comienzo del map
	for (; mi_it_map != mi_map_sf.end(); mi_it_map++)
	{
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl;
	}
		std::cout << "Contenido del map string/float después de la modificación" << std::endl;
	mi_it_map = mi_map_sf.begin(); // Vuelve a colocar el iterador al comienzo del map
	for (; mi_it_map != mi_map_sf.end(); mi_it_map++)
	{
		std::string mi_str_mod = mi_it_map->first + "yeah!"; // Añade "yeah! al string
		int mi_int = floor( mi_it_map->second + 0.5 ); // Redondea la cotizacion
		mi_map_sf.erase( mi_it_map); // Borra el elemento 
		mi_map_sf.insert( std::make_pair( mi_str_mod, mi_int ) ); // Inserta el elemento modificado
		std::cout << mi_it_map->first << " - " << mi_it_map->second << std::endl;
	}
	std::cout << std::endl << std::endl;
      
    // 5. transform exercises 1, 2 and 3 to ranged for loops. use as much
    // c++11 syntax as you can

	std::cout << YELLOW << "Segunda parte: Con código c++11" << RESET << std::endl << std::endl;
	std::cout << "Ejercicio 1: Bucle con salida 1 al 5 usando Range-Based Loop " << std::endl;
	for( auto i : { 1, 2, 3, 4, 5 } )
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Ejercicio 2: Bucle que muestra las cadenas de un vector usando Range vector" << std::endl;
	for ( auto mi_dia : mi_vector ) // Recorre el vector dias lectivos mucgs e imprime sus elementos
	{
		std::cout << mi_dia << " "; 
	}
	std::cout << std::endl << std::endl;

	std::cout << "Ejercicio 3: Bucle cambia maps string/float->char*/int usando Range map" << std::endl;
	mi_map_sf.clear(); // Borra los monedas con los yeah!	
	mi_map_sf = { // Vuelve a rellenar con cotizaciones
	{ "Euro", 1.0f }, 
	{ "Dolar", 0.73f },
	{ "Libra", 1.18f },
	{ "Yen", 0.01f } };
	std::cout << "Contenido del map compuesto por string/float" << std::endl;
	mi_it_map = mi_map_sf.begin(); // Inicializa iterador del map string/float
	for( auto mi_moneda : mi_map_sf ) // Recorre el map y convierte sus elementos
	{
		std::cout << mi_moneda.first << " - " << mi_moneda.second << std::endl; // Muestra el contenido
		const char* mi_char = mi_it_map->first.c_str(); // Define char y convierte string de puntero a char
		mi_map_ci[mi_char] = (int)mi_it_map->second; // Guarda el float como int
	}
	std::cout << "Contenido del map compuesto por char/integer" << std::endl;
	mi_it_ci = mi_map_ci.begin(); // Inicializa el iterador del map char/int
	for( auto mi_moneda : mi_map_ci )
	{
		std::cout << mi_moneda.first << " - " << mi_moneda.second << std::endl;
	}
	std::cout << std::endl;
	    
    // 6. write a for loop that prints a pyramid of height N, like this:    
    //	
    //	               **
    //	              ****
    //	             ******
    //	            ********
    //	           **********
    //	          ************

	std::cout << "Ejercicio 5: Piramide de estrellas" << std::endl;
	int altura;
	std::cout << "Dime cuantas filas : ";
	std::cin >> altura;
	for ( int fila = 0; fila < altura; fila++ ) // Recorre toda la altura
	{
		for ( int col = 1; col < altura - fila; col++ ) // Recorre las columnas
			std::cout << ' ';                           // Espacios de 1 a altura - fila
		for ( int col = 0; col <=  2*fila; col++ )      // Recorre la fila
			std::cout << '*';                           // Asteriscos doble que el numero de filas + 1
		std::cout << std::endl; // Desactiva parpadeo
	}
	return 0;
}
