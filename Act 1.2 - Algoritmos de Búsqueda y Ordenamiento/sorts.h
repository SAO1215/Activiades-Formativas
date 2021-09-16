/* 
 * 
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 1.2 - Algoritmos de Búsqueda y Ordenamiento
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef sorts_h
#define sorts_h

#include <vector>
#include <iostream>
#include <list>

using namespace std;

//Template de la clase sorts
template < class T >
class Sorts {
  //Funciones de apoyo
  private:
    void swap(vector<T>&v, int, int); 
    void copyArray(vector<T>& , vector<T>& , int , int );
    void mergeArray(vector<T>& A, vector<T>& B, int i, int j, int k);
    void mergeSplit(vector<T>& , vector<T>& , int , int );    
    
  public:
    void ordenaSeleccion(vector<T>&);
    void ordenaBurbuja(vector<T>&);
    void ordenaMerge(vector<T>&);
    int busqBinaria(vector<T>&, int);
    int busqSecuencial(vector<T>&, int);

};

//Funcion swap: cambia de posición dos elementos del vector
template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j) {
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

//Usa el megodo de seleccion para ordenar un vector
template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v){ 
  int pos;
  for (int i = 0; i < v.size(); i++) {
		pos = i;
		for (int j = i; j <= v.size() - 1; j++) {
			if (v[j] < v[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			swap(v, i, pos);
		}
	}
}

//Usa el metodo de burbuja para ordenar un vector
template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v) {

    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = v.size() - 1; j > i; j--) {
            if (v[j] < v[j - 1]) {
                swap(v, j, j - 1);
            }
        }
    }
}

//Se usa como mascara para la funcion mergeSplit 
template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v) {
	vector<T> aux(v.size());

	mergeSplit(v, aux, 0, v.size() - 1);
}

//Esta funcion recibe dos vectores, sus indices y usa recursividad para dividirlos
template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

//Esta funcion combina y ordena los elementos
template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high) {

	int i = low;
	int j = mid + 1;
	int k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

//Esta funcion hace una copia del array
template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

//Esta funcion busca un elemento con el metodo secuencial
template <class T>
int Sorts<T>::busqSecuencial(vector<T> &v, int val) {
    for (int i = v.size(); i >= 0; i--) {
        if (val == v[i])
            return i;
    }
    return -1;
}

//Esta funcion busca un elemento con busqueda binaria
template <class T>
int Sorts<T>::busqBinaria(vector<T> &v, int val) {
  ordenaSeleccion(v);
	int mid;
	int low = 0;
	int high = v.size() - 1;

	while (high > low) {
		mid = (high + low) / 2;
		if (val == v[mid]) {
			return mid;
		} else if (val < v[mid]) {
			high = mid - 1;
		} else if (val > v[mid]) {
			low = mid + 1;
		}
	}
	return -1;
}

#endif
