#include <iostream>
#include "bots.h"
#include <set>
#define _LADO 10

void pinta_escenario()
{
	//Llena la pila ordenada de robots
	
	for ( int col = 0; col < _LADO + 2; col++ ) // Primera fila de X
        	std::cout << 'X'; 
	std::cout << std::endl;
	for ( int fila = 0; fila < _LADO; fila++ ) //! Recorre toda la altura
        {
		std::cout << 'X'; // Primera X de la fila
		for ( int col = 0; col < _LADO; col++ ) // Espacios en blanco
                        std::cout << ' '; 
		std::cout << 'X'; //! Espacios de 1 a altura - fila
                std::cout << std::endl;
        }
	for ( int col = 0; col < _LADO + 2; col++ ) // Primera fila de X
                        std::cout << 'X'; 
	std::cout << std::endl;

}



int main (int argc, char* argv[])
{
	
	int myints[] = {9,14,17,4,52};
  std::set<int> myset (myints,myints+5);


  std::set<int>::iterator it;

  std::cout << "myset contains:";
  for ( it=myset.begin() ; it != myset.end(); it++ )
    std::cout << " " << *it;

  std::cout << std::endl;

	bots mi_bots = bots(_LADO, _LADO); // Tamaño del campo 10x10, usa la pila
	// bots *mi_bots = new bots(10,10) // al monticulo

	mi_bots.generate(1,4); // Número de equipos y número de miembros por equipo, usa la pila
	// mi_bots->generate(3,10); // al monticulo

	
	while (true) 
	{
		mi_bots.step();
		mi_bots.for_each_bot([] (const bot & b) {
			//std::cout << b.get_team() << "\t"; // std::endl;
			//std::cout << b.get_x() << "\t";
			//std::cout << b.get_y() << "\t";
			//std::cout << b.get_energy() << "\t";
			//std::cout << std::endl;    
		});
		
		//pinta_escenario(mis_bots_ord);
		pinta_escenario();

		while ( std::cin.get() != ' ' );
		std::cout << "\x1B[2J\x1B[H";

	}
	return 0;
}
