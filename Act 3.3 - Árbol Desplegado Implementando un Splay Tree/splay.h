/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 3.3 - Árbol Desplegado: Implementando un Splay Tree
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;

template <class T>
class Node{
private:
	T value;
	Node *left, *right, *parent;
	unsigned int sze;
	Node<T>* succesor();
	Node<T>* R_rot(Node<T>*);
	Node<T>* L_rot(Node<T>*);

public:
	Node(T);
	Node(T,Node<T>*,Node<T>*,Node<T>*);

	Node<T>*add(T);
	Node<T>*find(T);
	Node<T>*remove(T);
  Node<T>* splay(Node<T>*,Node<T>*);
	void removeChilds();
  void preorder(stringstream&) const;
	void inorder(stringstream&) const;
  void print_tree(stringstream&) const;

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val): value(val),left(0),right(0),parent(0) {}

template <class T>
Node<T>::Node(T val,Node<T> *le,Node<T> *ri,Node<T> *p)
    : value(val),left(le),right(ri),parent(p){}

template<class T>
Node<T>* Node<T>::succesor(){
	Node<T> *le, *ri;
	le = left;
	ri = right;
	if(right == 0){
		if(left){
			left = 0;
		}
		if(le)
			le->parent = 0;
		return le;
	}
	if(right->left == 0){
		right = right->right;
		if(right)
			right->parent = parent;
		if(ri){
			ri->right = 0;
			ri->parent = 0;
		}
		return ri;
	}
	Node<T> *p, *c;
	p = right;
	c = right->left;
	while(c->left){
		p = c;
		c = c->left;
	}
	p->left = c->right;
	if(p->left)
		p->left->parent = p;
	c->right = 0;
	return c;
}

template <class T>
Node<T>* Node<T>::R_rot(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template<class T>
Node<T>* Node<T>::L_rot(Node<T>*x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::add(T val){
	if(val < value){
		if(left){
			return left->add(val);
		}
        else{
			left = new Node<T>(val);
			left->parent = this;
			return left;
		}
	}
    else{
		if(right){
			return right->add(val);
		}
        else{
			right = new Node<T>(val);
			right->parent = this;
			return right;
		}
	}
}

template<class T>
Node<T>* Node<T>::find(T val){
	if(val == value){
		return this;
	}
    else if (val < value){
		if(left)
			return left->find(val);
		else
			return this;
	}
    else if (val > value){
		if(right)
			return right->find(val);
		else
			return this;
	}
	return 0;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;
	if (val < value) {
		if (left) {
			if (left->value == val) {
				old = left;
				if(old->left && old->right){
					succ = left->succesor();
					if (succ) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					left = succ;
				} else if (old->right){
					old->right->parent = left->parent;
					left = old->right;

				} else if (old->left){
					old->left->parent = left->parent;
					left = old->left;
				} else {
					left = 0;
				}
				delete old;
				return this;
			} else {
				return left->remove(val);
			}
		}
	} else if (val > value) {
		if (right) {
			if (right->value == val) {
				old = right;
				if(old->left && old->right){
					succ = right->succesor();
					if (succ) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					right = succ;
				} else if (old->right){
					old->right->parent = right->parent;
					right = old->right;

				} else if (old->left){
					old->left->parent = right->parent;
					right = old->left;
				} else {  // hoja
					right = 0;
				}
				delete old;
				return this;
			} else {
				return right->remove(val);
			}
		}
	}
	return this;
}

template<class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent){
		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				R_rot(x->parent);
			}
            else{
				L_rot(x->parent);
			}
		}
        else{
			Node<T>*p = x->parent;
			Node<T>*g = p->parent;
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				R_rot(g);
				R_rot(p);
			}
            else if(p->right && g->right &&
			 x->value == p->right->value && p->value == g->right->value){
				L_rot(g);
				L_rot(p);
			}
            else if(p->left && g->right &&
			 x->value == p->left->value && p->value == g->right->value){
				R_rot(p);
				L_rot(g);
			}
            else{
				L_rot(p);
				R_rot(g);
			}
		}
	}
	return x;
}

template<class T>
void Node<T>::removeChilds(){
	if(left){
		left->removeChilds();
		delete left;
		left = 0;
	}
	if(right){
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << value;
	if (left) {
		aux << " ";
		left->preorder(aux);
	}
	if (right) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if(left){
		left->inorder(aux);
	}
	if(aux.tellp() != 1){
		aux<<" ";
	}
	aux<<value;
	if(right){
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(stringstream &aux) const {
	if (parent){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}
    else
		aux << "\n root " << value;
	if (left)
		aux << " left " << left->value;
	if (right)
		aux << " right " << right->value;
	aux << "\n";

	if (left) {
		left->print_tree(aux);
	}
	if (right) {
		right->print_tree(aux);
	}
}

//_________________________Clase SplayTree________________________

template<class T>
class SplayTree{
private:
	Node<T> *root;
	int sze;

public:
	SplayTree();
	~SplayTree();

	bool empty() const;
  void removeAll();
  //Metodos tarea
	void add(T);
	bool find(T);
	void remove(T);
	int size() const;
  //Strings
	string preorder() const;
  string inorder() const;
  string print_tree() const;
};

template <class T>
SplayTree<T>::SplayTree():root(0){
	sze = 0;
}

template<class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template<class T>
bool SplayTree<T>::empty() const{
	return (root == 0);
}

template<class T>
void SplayTree<T>::removeAll(){
	if(root){
		root->removeChilds();
	}
	delete root;
	root = 0;
	sze = 0;
}

//_________________________Metodos Tarea________________________
template<class T>
void SplayTree<T>::add(T val){
	if(root){
		Node<T>* newNode = root->add(val);
		root = root->splay(root, newNode);
	}
    else{
		root = new Node<T>(val);
	}
	sze++;
}

template<class T>
bool SplayTree<T>::find(T val){
	if(root){
		Node<T>* Fnd_val = root->find(val);
		if (Fnd_val == 0) return false;
		root = root->splay(root, Fnd_val);
		return(root->value == val);
	}
    else{
		return false;
	}
}

template<class T>
void SplayTree<T>::remove(T val){
	if(root){
		if(val == root->value){
			Node<T> *succ = root->succesor();
			if(succ){
				succ->left = root->left;
				succ->right = root->right;
				succ->parent = 0;
				if(succ->left)
					succ->left->parent = succ;
				if(succ->right)
					succ->right->parent = succ;
			}
			delete root;
			root = succ;
		}
        else {
			Node<T>*p = root->remove(val);
			if (p)
				root = root->splay(root, p);
		}
	}
	sze--;
}

template <class T>
int SplayTree<T>::size() const{
	return sze;
}

//_________________________String________________________
template<class T>
string SplayTree<T>::preorder() const{
	stringstream aux;
	aux<<"[";
	if(!empty()){
		root->preorder(aux);
	}
	aux<<"]";
	return aux.str();
}

template<class T>
string SplayTree<T>::inorder() const{
	stringstream aux;
	aux<<"[";
	if(!empty()){
		root->inorder(aux);
	}
	aux<<"]";
	return aux.str();
}

template<class T>
string SplayTree<T>::print_tree() const{
	stringstream aux;
	aux<<"\n ====================== ";
	if(!empty()){
		root->print_tree(aux);
	}
	aux<<" ==================== \n";
	return aux.str();
}

#endif