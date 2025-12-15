#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h" 
using namespace std;
template <typename V>
class HashTable : public Dict<V> {
    private:
        int n;   // número de elementos almacenados
        int max; // número total de cubetas
        ListLinked<TableEntry<V>>* table; // array de listas enlazadas

        // Función hash: suma de ASCII % max
        int h(string key) {
            int sum = 0;
            for (int i = 0; i < key.length(); i++) {
                sum += int(key.at(i));
            }
            return sum % max;
        }

    public:
        // Constructor
        HashTable(int size): n{0}, max{size}, table{new ListLinked<TableEntry<V>>[max]} {}

        // Destructor
        ~HashTable() {
            delete[] table;
        }

        // Capacidad total
        int capacity() {
            return max;
        }

         // Sobrecarga operador <<, imprimir contenido de la tabla
        friend ostream& operator<<(ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            for (int i = 0; i < th.max; i++) {
                out << "Cubeta " << i << ": " << endl << endl;
                //out << th.table[i] << std::endl; // suponiendo que ListLinked<T> sobrecarga <<
                out << "List => " << th.table[i] << endl << endl;
            }
            
            return out;
        }

        // Sobrecarga operador [], devuelve el valor de la clave
        V operator[](string key) {
            return search(key);
        }
	
        //metodos heredados 
        //funcion insertar clave-valor
        void insert(const string& key, const V& value) override{
	        int pos = h(key);
	        ListLinked<TableEntry<V>>& posicion = table[pos];
	
	        for (int i = 0; i < posicion.size(); i++) {
                if (posicion.get(i).key == key) {
                    throw runtime_error("Key: " + key + ",ya existe");
                }
            }

            //en caso de aun no exista esa clave, crear un tableEntry completo y lo añade al final de la lista
            posicion.prepend(TableEntry<V>(key, value));
            n++;	
        }

        int entries() const override{
            return n;
        }

        V search(const string& key) const override{
            int pos = h(key);
            ListLinked<TableEntry<V>>& posicion = table[pos];
            
            for (int i = 0; i < posicion.size(); i++) {
                TableEntry<V> entry = posicion.get(i);
                if(entry.key == key){
                    return entry.value;
                }
            }

            throw runtime_error("Key '" + key + "', no se ha encontrado.");
        }

        //funcion eliminar clave
        V remove(const string& key) override{
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

