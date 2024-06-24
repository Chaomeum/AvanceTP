#ifndef __GRAFO_HPP__
#define __GRAFO_HPP__

#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class CGrafo {
private:
    class CArco {
    public:
        T info;
        int v; //indice del vertice de llegada
        CArco(int vLlegada) : v(vLlegada) {
            // No inicializamos 'info' con 'vacio' aquí
        }
    };
    class CVertice {
    public:
        T info;
        vector<CArco*> ady; //Lista de adyacencia
        CVertice() {
            // No inicializamos 'info' con 'vacio' aquí
        }
    };

    vector<CVertice*> vertices;

public:
    CGrafo() {}

    int adicionarVertice(T info) {
        CVertice* vert = new CVertice();
        vert->info = info;
        vertices.push_back(vert);
        return vertices.size() - 1;
    }

    int cantidadVertices() {
        return vertices.size();
    }

    T obtenerVertice(int v) {
        return vertices[v]->info;
    }

    void modificarVertice(int v, T info) {
        vertices[v]->info = info;
    }

    void adicionarArco(int v, int vLlegada) {
        CVertice* ver = vertices[v];
        CArco* arc = new CArco(vLlegada);
        ver->ady.push_back(arc);
    }

    int cantidadArcos(int v) {
        return vertices[v]->ady.size();
    }

    T obtenerArco(int v, int apos) {
        return vertices[v]->ady[apos]->info;
    }

    void modificarArco(int v, int apos, T info) {
        vertices[v]->ady[apos]->info = info;
    }

    int obtenerVerticeLlegada(int v, int apos) {
        return vertices[v]->ady[apos]->v;
    }
};

#endif // !__GRAFO_HPP__
