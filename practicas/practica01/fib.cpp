/** * fib.cpp
    * Código que muestra la secuencia de Finonacii de la longitud dada *
    * By Óscar Romero *
*/
#include <iostream>

using namespace std;
int a, b;     //Los números que inician la serie
int limite;   //Número limite de iteraciones
int iter = 0; //Número de iteraciones
int suma;     //Suma de los números de la serie

int main(){
	std::cout << "Introduzca los numeros iniciales de la serie, separados por un espacio: " << std::endl;
	std:cin >> a >> b; 
	std::cout << endl;

	std::cout << "Introduzca el numero de iteraciones en la serie: " << std::endl;
	std::cin >> limite;
	std::cout << a << " " << b << " ";

	while (iter < limite-2) {
		iter++;
		suma = a + b;
		std::cout << suma << " ";
		a = b;
		b = suma;
	}
	std::cout << endl;
	return 0;
}

