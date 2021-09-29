/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 2.1 - Implementación de una lista ligada simple
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);

        T value;
        DLink<T> *previous;
        DLink<T> *next;

        friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt): value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source): value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList{
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
    public:
    // Constructores
        DList();
        DList(const DList<T>&);
        ~DList();
    // Metodo
        void insertion(T);
        int search(T);
        void update(int, T);
        T deleteAt(int);
    // Strings 
        string toStringForward() const;
        string toStringBackward() const;

};

template <class T>
DList<T>::DList(): head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    DLink<T> *p, *q;
    p = head;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
void DList<T>::insertion(T valor){
    DLink<T> *newLink;
    newLink = new DLink<T>(valor);

    if (head == 0) {
        head = newLink;
        tail = newLink;
        size++;
        return;

    }else{
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
int DList<T>::search(T valor){
    int indice;
    DLink<T> *p;
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
void DList<T>::update(int posicion, T valor){
    int indice;
    DLink<T> *p;

    p = head;
    indice = 0;

    while (p != 0) {

        if (indice == posicion){
            p->value = valor;
            return;
        }
        p = p->next;
        indice++;
    }
}

template <class T>
T DList<T>::deleteAt(int posicion) {
  DLink<T> *p, *c;
  T valor;
  p = head;
  c = head -> next;
  int i = 1;

    if (posicion == 0){
      head = p->next;
      p->next->previous = 0;
      size--;
      delete p;
      return valor;
    }
    else{
      while (i < posicion){
        p = c;
        c = c -> next;
        }
      valor = c -> value;
      p -> next = c -> next;
      c -> next -> previous = p;
      delete c;
      size--;
      return valor;
    }
}


template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;
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

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;
    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

#endif