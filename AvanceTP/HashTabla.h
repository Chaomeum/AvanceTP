#ifndef HASHTABLA_H
#define HASHTABLA_H

#include <list>
#include <iostream>
#include "Contribuyente.h"

template <typename T>
class HashTabla {
private:
    std::list<T*> table[300]; // Tabla hash de listas de punteros a T

public:
    void insert(T* elemento) {
        int index = funcionHash(elemento->id); // Usar el id para el hash
        table[index].push_back(elemento);
    }
    //Para contribuyentes
    bool containsC(int id) {
        int index = funcionHash(id);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->id == id) {
                return true;
            }
        }
        return false;
    }
    //Para empresas
    bool containsE(int RUC) {
        int index = funcionHash(RUC);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->RUC == RUC) {
                return true;
            }
        }
        return false;
    }

    // Para contribuyentes
    T* getC(int id) {
        int index = funcionHash(id);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return nullptr; // No se encontró el elemento
    }
    // Para empresas
    T* getE(int RUC) {
        int index = funcionHash(RUC);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->RUC == RUC) {
                return *it;
            }
        }
        return nullptr; // No se encontró el elemento
    }


    void displayTableC() {
        for (int i = 0; i < 300; i++) {
            std::cout << "Index " << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                std::cout << (*it)->nombre << " (" << (*it)->id << ") -> ";
            }
            std::cout << std::endl;
        }
    }

    void displayTableE() {
        for (int i = 0; i < 300; i++) {
            std::cout << "Index " << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                std::cout << (*it)->nombre << " (" << (*it)->RUC << ") -> ";
            }
            std::cout << std::endl;
        }
    }

private:
    int funcionHash(int num) {
        const unsigned int A = 2654435769u; // Constante de multiplicación sugerida por Knuth
        unsigned int hash = num * A;
        return hash % 300; // 300: tamaño de la tabla hash       
    }
};

#endif // HASHTABLA_H
