#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        T elem; //elemento tipo T almacenado en el nodo
		BSNode<T>* izquierda; //puntero al nodo izquierdo
		BSNode<T>* derecha; //puntero al nodo derecho
	
			//metodo constructor, crea nodo con puntero a los nodos sucesores por defecto
	BSNode(T elem, BSNode<T>* izquierda = nullptr, BSNode<T>* derecha = nullptr): elem(elem), izquierda(izquierda), derecha(derecha){}


		//sobrecarga operador << para imprimir el nodo por pantalla
		friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
		out<<bsn.elem;
		return out;
	}
    
};

#endif
