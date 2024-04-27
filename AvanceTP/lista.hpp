#pragma once

#include <functional>

using namespace std;

typedef unsigned int uint;

template <typename T>
class Lista {
    struct Nodo;
    typedef function<int(T, T)> Comp;
    Nodo*   ini;
    uint    lon; // número de elementos en la lista
    Comp    comparar; // lambda de criterio de comparación

public:
    Lista(): ini(nullptr), lon(0), comparar([](T a,T b) {return a - b;}) {}
    Lista(Comp comparar): ini(nullptr), lon(0), comparar(comparar) {}
    ~Lista();

    uint    longitud();

    bool    esVacia();

    void    agregaInicial(T elem);
    void    agregaPos(T elem, uint pos);
    void    agregaFinal(T elem);

    void    modificarInicial(T elem);
    void    modificarPos(T elem, uint pos);
    void    modificarFinal(T elem);

    void    eliminaInicial();
    void    eliminaPos(uint pos);
    void    eliminaFinal();

    T       obtenerInicial();
    T       obtenerPos(uint pos);
    T       obtenerFinal();

    T       buscar(T elem);

    T* toArrayPointer();

    void sortShellPorIngresos();

    void sortShellPorVenta();
};

template <typename T>
struct Lista<T>::Nodo {
    T       elem;
    Nodo*   sig; // puntero apunta al siguiente nodo

    Nodo(T elem = nullptr, Nodo* sig = nullptr): elem(elem), sig(sig) {}
};

template <typename T>
Lista<T>::~Lista() {
    Nodo* aux = ini;
    while (ini != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
}

template <typename T>
uint Lista<T>::longitud() {
    return lon;
}

template <typename T>
bool Lista<T>::esVacia() {
    return lon == 0;
}

template <typename T>
void Lista<T>::agregaInicial(T elem) {
    Nodo* nuevo = new Nodo(elem, ini);
    if (nuevo != nullptr) {
        ini = nuevo;
        lon++;
    }
}

template <typename T>
void Lista<T>::agregaPos(T elem, uint pos) {
    if (pos > lon) return;
    if (pos == 0) {
        agregaInicial(elem);
    } else {
        Nodo* aux = ini;
        for (int i = 1; i < pos; i++) {
            aux = aux->sig;
        }
        Nodo* nuevo = new Nodo(elem, aux->sig);
        if (nuevo != nullptr) {
            aux->sig = nuevo;
            lon++;
        }
    }
}

template <typename T>
void Lista<T>::agregaFinal(T elem) {
    agregarPos(elem, lon); // ;)
}

template <typename T>
void Lista<T>::modificarInicial(T elem) {
    if (lon > 0) {
        ini->elem = elem;
    }
}

template <typename T>
void Lista<T>::modificarPos(T elem, uint pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->sig;
        }
        aux->elem = elem;
    }
}

template <typename T>
void Lista<T>::modificarFinal(T elem) {
    modificar(elem, lon - 1);
}

template <typename T>
void Lista<T>::eliminaInicial() {
    if (lon > 0) {
        Nodo* aux = ini;
        ini = ini->sig;
        delete aux;
        lon--;
    }
}

template <typename T>
void Lista<T>::eliminaPos(uint pos) {

}

template <typename T>
void Lista<T>::eliminaFinal() {

}

template <typename T>
T Lista<T>::obtenerInicial() {
    return obtenerPos(0);
}

template <typename T>
T Lista<T>::obtenerPos(uint pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->sig;
        }
        return aux->elem;
    } else {
        return NULL;
    }
}

template <typename T>
T Lista<T>::obtenerFinal() {
    return obtenerPos(lon - 1);
}

template <typename T>
T Lista<T>::buscar(T elem) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (comparar(aux->elem, elem) == 0) {
            return aux->elem;
        }
        aux = aux->sig;
    }
    return NULL;
}

template <typename T>
T* Lista<T>::toArrayPointer() {
    if (lon == 0) return nullptr;

    T* array = new T[lon];
    Nodo* actual = ini;
    uint i = 0;
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }
    return array;
}

template <typename T>
void Lista<T>::sortShellPorIngresos() {
    // Convertir la lista en un array de punteros a contribuyentes
    CContribuyente** array = new CContribuyente * [lon];
    Nodo* actual = ini;
    uint i = 0;
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    // Aplicar el algoritmo de ordenación Shell al array
    uint n = lon;
    for (uint intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (uint i = intervalo; i < n; i += 1) {
            CContribuyente* temp = array[i];
            uint j;
            for (j = i; j >= intervalo && array[j - intervalo]->ingresos < temp->ingresos; j -= intervalo) {
                array[j] = array[j - intervalo];
            }
            array[j] = temp;
        }
    }

    // Actualizar la lista con los contribuyentes ordenados
    actual = ini;
    for (uint i = 0; i < n; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array; // Liberar memoria del array dinámico
}
template <typename T>
void Lista<T>::sortShellPorVenta() {
    // Convertir la lista en un array de punteros a contribuyentes
    CContribuyente** array = new CContribuyente * [lon];
    Nodo* actual = ini;
    uint i = 0;
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    // Aplicar el algoritmo de ordenación Shell al array
    uint n = lon;
    for (uint intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (uint i = intervalo; i < n; i += 1) {
            CContribuyente* temp = array[i];
            uint j;
            for (j = i; j >= intervalo && array[j - intervalo]->montoVenta < temp->montoVenta; j -= intervalo) {
                array[j] = array[j - intervalo];
            }
            array[j] = temp;
        }
    }

    // Actualizar la lista con los contribuyentes ordenados
    actual = ini;
    for (uint i = 0; i < n; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array; // Liberar memoria del array dinámico
}