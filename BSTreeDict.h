#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;
template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict(){
            delete tree;
        }

        friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
            out << *bs.tree;
            return out;
        }

        V operator[](string key){
            return search(key);
        }

        // inicializo metodos heredados
        void insert(string key, V value) override{
            TableEntry<V> prueba(key, V());
            
            bool existe = false;
            
            try{
                tree->search(prueba);
                existe = true;
            } catch (const runtime_error&){
                existe = false;
            }
        
            if(existe){
                throw runtime_error("La key ya existe");
            } else {
                TableEntry<V> entrada(key, value);
                tree->insert(entrada);
            }
        }

        V search(string key) override{
            TableEntry<V> prueba(key, V());

            try{
                TableEntry<V> result = tree->search(prueba);
                return result.value;
            } catch (const runtime_error&){
                throw runtime_error("La key no se ha encontrado");
            }
        }
        
        V remove(string key) override {
            TableEntry<V> prueba(key, V());
        
            try {
                TableEntry<V> found = tree->search(prueba);
                V valueToReturn = found.value;
                tree->remove(prueba);
            
                return valueToReturn;
            } catch (const runtime_error&) {
                throw runtime_error("La key no se ha encontrado");
            }
        }

        int entries() override {
            return tree->size();
        }

        
};

#endif
