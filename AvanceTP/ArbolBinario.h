#ifndef __ARBOLBB_HPP__
#define __ARBOLBB_HPP__

#include <functional>
using namespace std;

template <class T>
class NodoArb {
public:
	T elemento;
	NodoArb* izq;
	NodoArb* der;
};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp; //Lambda

	NodoArb<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparación


private:
	bool _buscar(NodoArb<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	NodoArb<T>* _obtener(NodoArb<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _obtener(nodo->der, e);
			}
			else {
				return _obtener(nodo->izq, e);
			}
		}
	}
	bool _insertar(NodoArb<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new NodoArb<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false;
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(NodoArb<T>* nodo) {
		if (nodo != nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(NodoArb<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(NodoArb<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	//agregar el recorrido por niveles

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(NodoArb<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
	int _altura(NodoArb<T>* nodo) {
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario

		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}

	int _minimo(NodoArb<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);
	}
	int _maximo(NodoArb<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}
	// Agregar el predecesor y sucesor

	bool _eliminar(NodoArb<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) {
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {
				return _eliminar(nodo->izq, e);
			}
			else { // r==0 es porque se encontró el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) {//caso 1
					nodo = nullptr;
					delete nodo;
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2 (solo tiene hijo derecho)
					NodoArb<T>* der = nodo->der;//guardar la referencia al hijo derecho
					delete nodo;//liberar la memoria del nodo
					nodo = der;	//reemplar el nodo con su hijo derecho
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3
					NodoArb<T>* izq = nodo->izq;
					delete nodo;
					nodo = izq;
					return true;
				}
				else { //caso 4
					//reempla el nodo por su sucesor
					NodoArb<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}
public:
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = [](T a, T b)->int {return a - b; };
		raiz = nullptr;
	}
	ArbolBB(void(*otroPunteroAFuncion)(T), Comp _comparar) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = _comparar;
		raiz = nullptr;
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	int Minimo() {
		return _minimo(raiz);
	}
	int Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
};

#endif
