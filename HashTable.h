#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h" 

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;   // número de elementos almacenados
    int max; // número total de cubetas
    ListLinked<TableEntry<V>>* table; // array de listas enlazadas

    // Función hash: suma de ASCII % max
    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Capacidad total
    int capacity() {
        return max;
    }
	

    //funcion insertar clave-valor
    void insert(std::string key, V value){
	int pos = h(key);
	TableEntry<V> entry(key,value);
	
	if(!table[pos].search(entry)){ //si no existe 
		table[pos].append(entry);
		n++;
	} else{ //si existe, actualizamos valor
		int idx = table[pos].indexOf(entry);
		table[pos].set(idx, entry);
	}	
    }

    //funcion buscar clave
    bool search(std::string key){
    	int pos = h(key);
	TableEntry<V> entry(key, V());
	return table[pos].search(entry);
    }

    //funcion eliminar clave
    void remove(std::string key){
    	int pos = h(key);
	TableEntry<V> entry(key, V());
	if(table[pos].search(entry)){ //si pos no esta vacia
		int idx = table[pos].indexOf(entry);
		table[pos].remove(idx);
		n--;
	} else{
		throw std::runtime_error("Clave no encontrada");
	}
    }

    // Sobrecarga operador <<
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        for (int i = 0; i < th.max; i++) {
            out << "Cubeta " << i << ": ";
            out << th.table[i] << std::endl; // suponiendo que ListLinked<T> sobrecarga <<
        }
        return out;
    }

    // Sobrecarga operador []
    V operator[](std::string key) {
        int pos = h(key);
        // Buscar en la lista correspondiente
        for (int i = 0; i < table[pos].size(); i++) { 
            TableEntry<V> entry = table[pos].get(i);
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Clave no encontrada en la tabla hash");
	
     }	
    };

#endif

