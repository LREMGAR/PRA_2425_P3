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
        HashTable(int size): n(0), max(size), table(nullptr) {
            if(size <= 0) throw std::runtime_error("Tamaño de la tabla invalido.");
            
            table = new ListLinked<TableEntry<V>>*[max];
            for(int i = 0; i < max; i++){
                table[i] = new ListLinked<TableEntry<V>>();
            }
        }

        // Destructor
        ~HashTable() {
            delete[] table;
        }

        // Capacidad total
        int capacity() {
            return max;
        }

         // Sobrecarga operador <<, imprimir contenido de la tabla
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            for (int i = 0; i < th.max; i++) {
                out << "Cubeta " << i << ": " << endl;
                //out << th.table[i] << std::endl; // suponiendo que ListLinked<T> sobrecarga <<
                out << "List => " << th.table[i] << endl << endl;
            }
            out << "\n"<< endl;
            return out;
        }

        // Sobrecarga operador [], devuelve el valor de la clave
        V operator[](std::string key) {
            return search(key);
        }
	
        //metodos heredados 
        //funcion insertar clave-valor
        void insert(std::string key, V value) override{
	        int pos = h(key);
	        ListLinked<TableEntry<V>>& posicion = table[pos];
	
	        for (int i = 0; i < table[pos].size(); i++) {
                if (table[pos].get(i).key == key) {
                    throw runtime_error("Key: " + key + ",ya existe");
                }
            }

            //en caso de aun no exista esa clave, crear un tableEntry completo y lo añade al final de la lista
            table[pos].append(TableEntry<V>(key, value));
            n++;	
        }

        int entries() override{
            return n;
        }

        V search(std::string key) override {
            int pos = h(key);
            ListLinked<TableEntry<V>>& posicion = table[pos];
            
            for (int i = 0; i < posicion.size(); i++) {
                TableEntry<V> entry = posicion.get(i);
                if(entry.key == key){
                    return entry.value;
                }
            }

            throw std::runtime_error("Key '" + key + "', no se ha encontrado.");
        }

        //funcion eliminar clave
        V remove(std::string key) override{
    	    int pos = h(key);
            ListLinked<TableEntry<V>>& posicion = table[pos];

	        for (int i = 0; i < posicion.size(); i++) {
                TableEntry<V> entry = posicion.get(i);
                if (entry.key == key) {
                    V value = entry.value;
                    posicion.remove(i);
                    n--;
                    return value;
                }  
            }
            throw std::runtime_error("Key '" + key + "', no se ha encontrado.");
        }
	
            
};

#endif

