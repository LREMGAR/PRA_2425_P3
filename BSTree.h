#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        
	//atributos
	int nelem; //numero de elementos almacenados en el arbol
	BSNode<T> *root; //nodo raiz del arbol

	//metodo busqueda, llamada recursiva busca y devuelve el elemento e
	BSNode<T>* search(BSNode<T>* n, T e) const{
		if(n==nullptr) throw std::runtime_error("Elemento no encontrado");
		if(e < n->elem) return search(n->izquierda, e);
		if(e > n->elem) return search(n->derecha, e);
		return n;
	
	}

	//metodo insercion ordenada de e, devuelve nodo que encabeza dicho sub-arbol modificado.
	BSNode<T>* insert(BSNode<T>* n, T e){
		if(n==nullptr) return new BSNode<T>(e);
		if(e == n->elem) throw std::runtime_error("Elemento duplicado");
		if(e < n->elem) n->izquierda = insert(n->izquierda, e);
		else n->derecha = insert(n->derecha, e);
		return n;
	}

	//recorrido inorder del sub-arbol cuya raiz es n para imprimir los eelementos ordenados de menor a mayor
	void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if(n!=nullptr){
			print_inorder(out, n->izquierda);
			out << n->elem << "";
			print_inorder(out, n->derecha);

		}
	
	}

	//metodo recursivo para eliminacion de elementos
	//en caso de eliminar un nodo con dos sucesores, aplicara la politica de reemplazo por el elemento maximo del subarbol izquierdo.
	BSNode<T>* remove(BSNode<T>* n, T e){
		if(n==nullptr) throw std::runtime_error("Elemento no encontrado");

		if(e < n->elem) n->izquierda = remove(n->izquierda, e);
		else if(e > n->elem) n->derecha = remove(n->derecha, e);
		else{
			if(n->izquierda != nullptr && n->derecha != nullptr){
				n->elem = max(n->izquierda);
				n->izquierda = remove_max(n->izquierda);
			}
			else{
				BSNode<T>* temp = (n->izquierda != nullptr)? n->izquierda : n->derecha;
				delete n;
				return temp;
			}

		}

		return n;
	}

	//metodo recursivo que devuelve el elem maximo contenido en sub-arbol con raiz n
	T max(BSNode<T>* n) const{
		if(n==nullptr) throw std::runtime_error("Arbol vacio");
		if(n->derecha != nullptr){
			return max(n->derecha);
		}
		return n->elem;

	}

	//metodo recursivo que elimina el elem maximo contenido en sub-arbol con raiz n
	BSNode<T>* remove_max(BSNode<T>* n){
		if(n->derecha == nullptr){
			BSNode<T>* temp = n->izquierda;
			delete n;
			return temp;
		}
		n->derecha = remove_max(n->derecha);
		return n;
	}

	//metodo recursivo para liberacion de memoria dinamica
	void delete_cascade(BSNode<T>* n){
		if(n != nullptr){
			delete_cascade(n->izquierda);
			delete_cascade(n->derecha);
			delete n;
		}

	}



    public:
        // miembros públicos
	
	//metodo constructor, crea un abb vacio
	BSTree(): nelem(0), root(nullptr){}

	//funcion que devuelve el numero de elementos del arbol
	int size()const{
		return nelem;
	}

	//metodo destructor
	~BSTree(){
		delete_cascade(root);
	}


	//busca y devuelve el elemento contenido por el nodo devuelto por el metodo privado. actua como metodo lanzadera
	T search(T e) const{
		return search(root, e)->elem;
	}

	//sobrecarga operador [], actua como interfaz al metodo search
	T operator[](T e) const{
		return search(e);
	}


	//inserta elemento e de manera ordenada. actua como metodo lanzaderadel metodo privado recursivo
	void insert (T e){
		root = insert(root, e);
		nelem++;
	}

	//elimina elemento del arbol
	void remove(T e){
		root = remove(root, e);
		nelem--;
	}

	//sobrecarga operador <<, mostrar contenido del arbol
	friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst){
		bst.print_inorder(out, bst.root);
		return out;
	}

};

#endif
