// ConsoleApplication15.cpp: define el punto de entrada de la aplicación de consola.
// Programado por Alfonso García Criado y Óscar Romero García

#include "stdafx.h"
#include <iostream>
#include <vector>

/* La siguiente clase libera la memoria asociada a un puntero 
	Los mensajes precedidos de ">" provienen de las clases
*/

template <class autoBorra> class borraPuntero
{
public:
	borraPuntero()
	{
		miPuntero = new autoBorra();
		std::cout << "> Puntero creado\n";
	}

	~borraPuntero()
	{
		delete miPuntero;
		std::cout << "> Puntero borrado\n";
	}
private:
	autoBorra *miPuntero;
};

/* La siguente clase hace move*/

class cortaPega
{
public:
	// crea instancia
	cortaPega(const std::string &_cadena)
	{ 
		cadena = _cadena;
	}

	// crea copia de otra instancia
	cortaPega(const cortaPega & copy)
	{
		cadena = copy.cadena;
	}

	// cambia el target del punto
	cortaPega(cortaPega &&copy)
	{
		std::cout << "> Posicion de memoria inicial de cadena1: \t";
		std::cout << reinterpret_cast<const void*>((const void*)&cadena) << std::endl;
		std::cout << "> Posicion de memoria de cadena 2 antes de mover: \t";
		std::cout << reinterpret_cast<const void*>((const void*)&copy.cadena) << std::endl;
		cadena = move(copy.cadena);
		std::cout << "> Posicion de memoria de cadena 2 despues de mover: \t";
		std::cout << reinterpret_cast<const void*>((const void*)&cadena) << std::endl;
		std::cout << "> Nota : La posicion de memoria de final cadena 2 es la misma que la de cadena 1\n";
	}

	void posicionMemoria()
	{
		std::cout << "Posicion de memoria de la variable cadenaX: ";
		std::cout << reinterpret_cast<const void*>((const void*)&cadena) << "\n";
	}

private:
	std::string cadena;

};

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Inicio de la secuencia de borrado de puntero\n";
	// Uso de RAII para dar ambito a la clase autoBorra
	{
		borraPuntero<std::string> point;
		std::cout << "Se ha creado el puntero al instanciar la clase\n";
	}

	std::cout << "Se ha salido del ambito de la clase y el puntero se ha borrado por el destructor de la clase.\n\n";
	std::string cadena1 = "Texto1";
	std::string cadena2 = "Texto2";
	cortaPega move1(cadena1);
	move1.posicionMemoria(); 
	cortaPega move2 = std::move(move1);
	move2.posicionMemoria();
	system("PAUSE");
	return 0;
}
