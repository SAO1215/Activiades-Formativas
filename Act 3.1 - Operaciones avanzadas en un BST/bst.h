/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 3.1 - Implementación de una lista ligada simple
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;
  int level, balance;
	Node<T>* succesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(stringstream&) const;
	void preorder(stringstream&) const;
  void postorder(stringstream&) const;
  void LbL(stringstream&) const;

  int height();
  void ancestors(stringstream&, T) const;
  int whatlevelamI(T);

	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				if(old->left != 0 && old->right != 0){
					succ = left->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
					}
					left = succ;
				} else if (old->right != 0){ // solo hijo der
						left = old->right;
				} else if (old->left != 0){ // solo hijo izq
						left = old->left;
				} else {
						left = 0;
				}
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				if(old->left != 0 && old->right != 0){ // dos hijos sucesor
					succ = right->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
					}
					right = succ;
				} else if (old->right != 0){ // solo hijo der
					right = old->right;
				} else if (old->left != 0){ // solo hijo izq
					right = old->left;
				} else {  // hoja
					right = 0;
				}
					delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::postorder(stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
    aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
    aux << " ";
	}
  
  aux << value;
}

template <class T>
void Node<T>::LbL(stringstream &aux) const {
	aux << value;
	if (left != 0) {
    aux << " ";
		left->LbL(aux);
	}
	if (right != 0) {
    aux << " ";
		right->LbL(aux);
	}
}

template <class T>
int Node<T>::height() {
  int le =0 , ri = 0;
  if (left != 0)
        le = left->height() + 1;
  if (right != 0)
        ri = right->height() + 1;
  if(le > ri)
        level = le;
  else
        level = ri;
  return level;
}

template <class T>
void Node<T>::ancestors(stringstream &aux, T val) const{

    if (left != 0 && val < value) {
      if (aux.tellp() != 1) {
			aux << " ";
		}
        aux << value;
        left->ancestors(aux, val);

    }
    if (right != 0 && val > value) {
      if (aux.tellp() != 1) {
			 aux << " ";
		}
        aux << value;
        right->ancestors(aux, val);
    }
}

template <class T>
int Node<T>::whatlevelamI(T val) {
	if (val == value) {
		return 1;
	} else if (val < value) {
		if(left != 0)
			return left->whatlevelamI(val) + 1;
	} else if (val > value) {
		if (right != 0)
		return right->whatlevelamI(val) + 1;
	}
	return -1;
}

template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	string inorder() const;
	string preorder() const;
  string postorder() const;
  string LbL() const;

  string visit();
  int height() const;
  string ancestors(T) const;
  int whatlevelamI(T);

};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
string BST<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::postorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::LbL() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->LbL(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::visit() {
  stringstream aux;

  aux << preorder() <<"\n";
  aux << inorder() <<"\n";
  aux << postorder() <<"\n";
  aux << LbL();
  
	return aux.str();
}

template <class T>
int BST<T>::height() const {
  return root->height() + 1;
}

template <class T>
string BST<T>::ancestors(T valor) const {
    stringstream aux;

    aux << "[";
    if (!empty()) {
        if(root->find(valor))
        root->ancestors(aux, valor);
    }
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val){
	if (root != 0) {
	 	int num = root->whatlevelamI(val);
		if(num < 0) return -1;
		return num;
	}
	else {
		return -1;
	}
}

#endif /* BST_H_ */