/* 
 * 
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 1.1 Funciones Iterativas, Recursivas y su análisis de Complejidad
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones
{
public:
    Funciones();
    int sumaIterativa(int n);
    int sumaRecursiva(int n);
    int sumaDirecta(int n);
};

Funciones::Funciones(){}

int Funciones::sumaIterativa(int n){
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i;
	}
	return sum;
}

int Funciones::sumaRecursiva(int n){
	if (n == 0) {
		return 0;
	} else {
		return n + sumaRecursiva(n - 1);
	}
}

int Funciones::sumaDirecta(int n){
  int sum = (n*(n+1))/2;
  return sum;
}

#endif
