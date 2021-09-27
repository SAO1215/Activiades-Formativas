/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 2.1 - Implementación de una lista ligada simple
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:

	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
};
template <class T>
Link<T>::Link(T valor) : value(valor), next(0) {}

template <class T>
Link<T>::Link(T valor, Link* nxt) : value(valor), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}
template <class T>

class List {

public:

    List();
    List(const List<T>&);
	~List();

	string toString() const;

	void insertion(T);
	int search(T);
	void update(int, T);
	T deleteAt(int);

private:

    Link<T> *head;
    int size;

};
template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::insertion(T valor){

    Link<T> *nuevoLink, *p;

    nuevoLink = new Link<T>(valor);


    if (head == 0) {
        nuevoLink->next = head;
        head = nuevoLink;
        size++;
        return;
	}

    p = head;
    while (p->next != 0) {
		p = p->next;
	}

	nuevoLink->next = 0;
	p->next = nuevoLink;
    size++;
}

template <class T>
int List<T>::search(T valor){
    int indice;
    Link<T> *p;

    p = head;
    indice = 0;

    while (p != 0) {

		if (p->value == valor){
            return indice;
		}
		p = p->next;
		indice++;
	}
	return -1;

}

template <class T>
void List<T>::update(int position, T valor){
    int indice;
    Link<T> *p;

    p = head;
    indice = 0;

    while (p != 0) {

		if (indice == position){
            p->value = valor;
            return;
		}
		p = p->next;
		indice++;
	}

}

template <class T>
T List<T>::deleteAt(int position) {
    T valor;
    Link<T> *p, *temp;

    p = head;
    temp = p->next;
    valor = 0;
    int indice = 1;

    if (position != 0) {

        for(int i=0;i==i;i++) {
            if(indice == position) {
                valor = temp->value;
                p->next = temp->next;
                break;
            }
            p = p->next;
            temp = temp->next;
        }

    } else {

        head = p->next;
        delete p;
        return valor;
        }


    return valor;
}

template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}
#endif