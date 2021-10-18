/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 3.2 - Árbol Heap: Implementando una fila priorizada
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T>
class Heap {
private:
	T *content;
	unsigned int sze;
	unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int);
	~Heap();
  void clear();
	bool full() const;

  //Metodos Tarea
	void push(T);
	T pop();
  bool empty() const;
  int top();
  int size();
	string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
	sze = sze;
	content = new T[sze];

	count = 0;
}

template <class T>
Heap<T>::~Heap() {
	delete [] content;
	content = 0;
	sze = 0;
	count = 0;
}

template <class T>
void Heap<T>::clear() {
	count = 0;
}

template <class T>
bool Heap<T>::full() const {
	return (count == sze);
}
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = content[i];
	content[i] = content[j];
	content[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && content[le] < content[min]) {
		min = le;
	}
	if (ri <= count && content[ri] < content[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

//_________________________Metodos Tarea________________________\\

template <class T>
void Heap<T>::push(T val) {
	unsigned int pos;

	pos = count;
	count++;
	while (pos > 0 && val < content[parent(pos)]) {
		content[pos] = content[parent(pos)];
		pos = parent(pos);
	}
	content[pos] = val;
}

template <class T>
T Heap<T>::pop() {
	T aux = content[0];

	content[0] = content[--count];
	heapify(0);
	return aux;
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
int Heap<T>::size() {
	return count;
}

template <class T>
int Heap<T>::top() {
	return content[0];
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << content[i];
	} aux << "]";
	return aux.str();
}

#endif 