#pragma once
#include "Contribuyente.h"
#include "Empresa.h"
#include <functional>

using namespace std;

typedef unsigned int uint;

template <typename T>
class Lista {
    struct Nodo;
    Nodo* ini;
    uint    lon; // número de elementos en la lista

public:
    //--------------Clase iterador--------------
    class Iterador {
        Nodo* aux;
    public:
        Iterador(Nodo* aux = nullptr) : aux(aux) {}
        void operator ++ () { aux = aux->sig; }
        bool operator != (Iterador it) { return aux != it.aux; }
        T operator * () { return aux->elem; }
    };
    //------------Fin Clase iterador------------
    Lista();
    ~Lista();
    Iterador begin() { return Iterador(ini); };
    Iterador end() { return Iterador(nullptr); };
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

    void sortBubblePorIngresos();
    void sortBubblePorVenta();
    void sortHeapPorIngresos();
    void heapifyPorIngresos(CContribuyente** arr, uint n, uint root);
    void sortHeapPorVentas();
    void heapifyPorVentas(CContribuyente** arr, uint n, uint root);


    void mergePorIngresos(Empresa** arr, uint l, uint m, uint r);
    void sortMergePorIngresos();
    void mergeSortPorIngresos(Empresa** arr, uint l, uint r);

    void mergePorVentas(Empresa** arr, uint l, uint m, uint r);
    void sortMergePorVentas();
    void mergeSortPorVentas(Empresa** arr, uint l, uint r);

    void quickSortIngresos();
    void quickSortMontoVenta();

    int partition(vector<T>& , int , int , std::function<bool(const T&, const T&)> );
    void quickSort(vector<T>& , int , int , std::function<bool(const T&, const T&)> );

private:
    std::function<bool(const CContribuyente*, const CContribuyente*)> compIngresos;
    std::function<bool(const CContribuyente*, const CContribuyente*)> compMontoVenta;
};

template <typename T>
struct Lista<T>::Nodo {
    T       elem;
    Nodo* sig; // puntero apunta al siguiente nodo

    Nodo(T elem = nullptr, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};


template <typename T>
Lista<T>::Lista() {
    lon = 0;
    ini = nullptr;
    // Definir los comparadores para ordenar por ingresos y monto de venta
    compIngresos = [](const CContribuyente* a, const CContribuyente* b) {
        return a->ingresos < b->ingresos;
        };

    compMontoVenta = [](const CContribuyente* a, const CContribuyente* b) {
        return a->montoVenta < b->montoVenta;
        };
}

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
    }
    else {
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
    }
    else {
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

template <typename T>
void Lista<T>::sortBubblePorIngresos() {
    Empresa** array = new Empresa * [lon];
    Nodo* actual = ini;
    uint i = 0;

    // Convertir la lista en un array de punteros a empresas o contribuyentes
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }


    // Aplicar el algoritmo de ordenación Bubble al array
    for (uint i = 0; i < lon - 1; i++) {
        for (uint j = 0; j < lon - i - 1; j++) {
            if (array[j]->ingresos > array[j + 1]->ingresos) {
                Empresa* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    // Actualizar la lista con las empresas ordeandas
    actual = ini;
    for (uint i = 0; i < lon; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array;
}


template <typename T>
void Lista<T>::sortBubblePorVenta() {
    Empresa** array = new Empresa * [lon];
    Nodo* actual = ini;
    uint i = 0;

    // Convertir la lista en un array de punteros a empresas 
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }


    // Aplicar el algoritmo de ordenación Bubble al array
    for (uint i = 0; i < lon - 1; i++) {
        for (uint j = 0; j < lon - i - 1; j++) {
            if (array[j]->montoVenta > array[j + 1]->montoVenta) {
                Empresa* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    // Actualizar la lista con las empresas ordenados
    actual = ini;
    for (uint i = 0; i < lon; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array;
}


template <typename T>
void Lista<T>::sortHeapPorIngresos() {
    // Convertir la lista en un array de punteros a contribuyentes
    CContribuyente** array = new CContribuyente * [lon];
    Nodo* actual = ini;
    uint i = 0;
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    // Aplicar el algoritmo de ordenación Heap (heapsort) al array
    uint n = lon;
    for (uint i = n / 2; i > 0; i--) {
        heapifyPorIngresos(array, n, i - 1);
    }
    for (uint i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapifyPorIngresos(array, i, 0);
    }

    // Actualizar la lista con los contribuyentes ordenados
    actual = ini;
    for (uint i = 0; i < n; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array; // Liberar memoria del array dinámico
}

// Función auxiliar para mantener la propiedad de max-heap
template <typename T>
void Lista<T>::heapifyPorIngresos(CContribuyente** arr, uint n, uint root) {
    uint largest = root;
    uint left = 2 * root + 1;
    uint right = 2 * root + 2;

    if (left < n && arr[left]->ingresos > arr[largest]->ingresos) {
        largest = left;
    }
    if (right < n && arr[right]->ingresos > arr[largest]->ingresos) {
        largest = right;
    }

    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapifyPorIngresos(arr, n, largest);
    }
}
template <typename T>
void Lista<T>::sortHeapPorVentas() {
    // Convertir la lista en un array de punteros a contribuyentes
    CContribuyente** array = new CContribuyente * [lon];
    Nodo* actual = ini;
    uint i = 0;
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    // Aplicar el algoritmo de ordenación Heap (heapsort) al array
    uint n = lon;
    for (uint i = n / 2; i > 0; i--) {
        heapifyPorVentas(array, n, i - 1);
    }
    for (uint i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapifyPorVentas(array, i, 0);
    }

    // Actualizar la lista con los contribuyentes ordenados
    actual = ini;
    for (uint i = 0; i < n; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array; // Liberar memoria del array dinámico
}

// Función auxiliar para mantener la propiedad de max-heap
template <typename T>
void Lista<T>::heapifyPorVentas(CContribuyente** arr, uint n, uint root) {
    uint largest = root;
    uint left = 2 * root + 1;
    uint right = 2 * root + 2;

    if (left < n && arr[left]->montoVenta > arr[largest]->montoVenta) {
        largest = left;
    }
    if (right < n && arr[right]->montoVenta > arr[largest]->montoVenta) {
        largest = right;
    }

    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapifyPorVentas(arr, n, largest);
    }
}

template <typename T>
void Lista<T>::mergePorIngresos(Empresa** arr, uint l, uint m, uint r) {
    uint n1 = m - l + 1;
    uint n2 = r - m;

    // Arrays temporales
    Empresa** L = new Empresa * [n1];
    Empresa** R = new Empresa * [n2];

    // Copiar datos a los arrays temporales L[] y R[]
    for (uint i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (uint j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge de los arrays temporales en arr[l..r]
    uint i = 0; // Indice inicial de L[]
    uint j = 0; // Indice inicial de R[]
    uint k = l; // Indice inicial de arr[]

    while (i < n1 && j < n2) {
        if (L[i]->ingresos <= R[j]->ingresos) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar memoria de los arrays temporales
    delete[] L;
    delete[] R;
}

template <typename T>
void Lista<T>::sortMergePorIngresos() {
    Empresa** array = new Empresa * [lon];
    Nodo* actual = ini;
    uint i = 0;

    // Convertir la lista en un array de punteros a empresas
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    mergeSortPorIngresos(array, 0, lon - 1);

    // Actualizar la lista con las empresas ordenadas
    actual = ini;
    for (uint i = 0; i < lon; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array;
}

template <typename T>
void Lista<T>::mergeSortPorIngresos(Empresa** arr, uint l, uint r) {
    if (l >= r) {
        return;
    }
    uint m = l + (r - l) / 2;
    mergeSortPorIngresos(arr, l, m);
    mergeSortPorIngresos(arr, m + 1, r);
    mergePorIngresos(arr, l, m, r);
}

template <typename T>
void Lista<T>::mergePorVentas(Empresa** arr, uint l, uint m, uint r) {
    uint n1 = m - l + 1;
    uint n2 = r - m;

    // Arrays temporales
    Empresa** L = new Empresa * [n1];
    Empresa** R = new Empresa * [n2];

    // Copiar datos a los arrays temporales L[] y R[]
    for (uint i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (uint j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge de los arrays temporales en arr[l..r]
    uint i = 0; // Indice inicial de L[]
    uint j = 0; // Indice inicial de R[]
    uint k = l; // Indice inicial de arr[]

    while (i < n1 && j < n2) {
        if (L[i]->montoVenta <= R[j]->montoVenta) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar memoria de los arrays temporales
    delete[] L;
    delete[] R;
}

template <typename T>
void Lista<T>::sortMergePorVentas() {
    Empresa** array = new Empresa * [lon];
    Nodo* actual = ini;
    uint i = 0;

    // Convertir la lista en un array de punteros a empresas
    while (actual != nullptr) {
        array[i] = actual->elem;
        actual = actual->sig;
        i++;
    }

    mergeSortPorVentas(array, 0, lon - 1);

    // Actualizar la lista con las empresas ordenadas
    actual = ini;
    for (uint i = 0; i < lon; i++) {
        actual->elem = array[i];
        actual = actual->sig;
    }

    delete[] array;
}

template <typename T>
void Lista<T>::mergeSortPorVentas(Empresa** arr, uint l, uint r) {
    if (l >= r) {
        return;
    }
    uint m = l + (r - l) / 2;
    mergeSortPorVentas(arr, l, m);
    mergeSortPorVentas(arr, m + 1, r);
    mergePorVentas(arr, l, m, r);
}

template <typename T>
void Lista<T>::quickSortIngresos() {
    vector<CContribuyente*> elementos;
    for (Nodo* nodo = ini; nodo != nullptr; nodo = nodo->sig) {
        elementos.push_back(nodo->elem);
    }
    quickSort(elementos, 0, elementos.size() - 1, compIngresos);
    Nodo* nodo = ini;
    for (size_t i = 0; i < elementos.size(); ++i) {
        nodo->elem = elementos[i];
        nodo = nodo->sig;
    }
}

template <typename T>
void Lista<T>::quickSortMontoVenta() {
    vector<CContribuyente*> elementos;
    for (Nodo* nodo = ini; nodo != nullptr; nodo = nodo->sig) {
        elementos.push_back(nodo->elem);
    }
    quickSort(elementos, 0, elementos.size() - 1, compMontoVenta);
    Nodo* nodo = ini;
    for (size_t i = 0; i < elementos.size(); ++i) {
        nodo->elem = elementos[i];
        nodo = nodo->sig;
    }
}

// Función de partición para el quickSort
template <typename T>
int Lista<T>::partition(vector<T>& arr, int low, int high, std::function<bool(const T&, const T&)> comp) {
    T pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Función recursiva quickSort
template <typename T>
void Lista<T>::quickSort(vector<T>& arr, int low, int high, std::function<bool(const T&, const T&)> comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSort(arr, low, pi - 1, comp);
        quickSort(arr, pi + 1, high, comp);
    }
}
