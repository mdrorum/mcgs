/** \file fib.cpp
 * Generación de la serie de Fibonacci, donde cada término es la suma de los dos anteriores.
 * 
 * El usuario debe introducir la pareja de números iniciales y el número de iteraciones.
 *
 * <a href="http://es.wikipedia.org/wiki/Sucesi%C3%B3n_de_Fibonacci">Serie de Fibonacci en Wikipedia</a> 
 * 
 * \date 19 de Octubre de 2013

*/

// El archivo de cabecera "iostream" permite usar cout y cin.
#include <iostream>

//! Primer valor de la serie
int a;
//! Segundo valor de la serie
int b;
//! Número de términos de la serie a mostrar.
int limite;
//! Iteración actual.
int iter = 0;
/// Suma de los dos valores anteriores.
int suma;

//! La función principal solicita los dos números iniciales de la serie y el número de iteraciones
int main(){

    std::cout << "Introduzca la pareja de números iniciales de la serie, separados por un espacio: " << std::endl;
    std::cin >> a >> b; 
    std::cout << std::endl;

    std::cout << "Introduzca el número de iteraciones en la serie: " << std::endl;
    std::cin >> limite;
    std::cout << a << " " << b << " ";

    while (iter < limite-2) {
        iter++;
        suma = a + b;
        std::cout << suma << " ";
        a = b;
        b = suma;
    }
    std::cout << std::endl;
    return 0;
}

