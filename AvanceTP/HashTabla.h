#ifndef HASHTABLA_H
#define HASHTABLA_H

#include <list>
#include <iostream>
#include "Contribuyente.h"

class HashTabla {
private:
    std::list<CContribuyente*> table[300];

public:
    void insert(CContribuyente* contribuyente) {
        int index = funcionHash(contribuyente->id); // Usar el id para el hash
        table[index].push_back(contribuyente);
    }

    bool contains(int id) {
        int index = funcionHash(id);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->id == id) {
                return true;
            }
        }
        return false;
    }

    CContribuyente* get(int id) {
        int index = funcionHash(id);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return nullptr; // No se encontró el contribuyente
    }

    void displayTable() {
        for (int i = 0; i < 300; i++) {
            std::cout << "Index " << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                std::cout << (*it)->nombre << " (" << (*it)->id << ") -> ";
            }
            std::cout << std::endl;
        }
    }

private:
    int funcionHash(int id) {
        const unsigned int A = 2654435769u; // Constante de multiplicación sugerida por Knuth
        unsigned int hash = id * A;
        return hash % 300; // 300: tamaño de la tabla hash       
    }
};

#endif // HASHTABLA_H
