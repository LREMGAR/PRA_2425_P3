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

