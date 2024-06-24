#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "lista.hpp"
#include "FuncionesArch.h"
#include "Contribuyente.h"
#include "Empresa.h"
#include "Menu.h"
#include "MenuIndividuo.h"
#include "MenuEmpresa.h"
#include "HashTabla.h"
#include "ArbolBinario.h"

using namespace std;

int main() {
	int opcion;
	/*Interfaz de bienvenida*/
	FuncionesArch f;
	f.imprimeSimbolo(60, '=');
	cout << setw(50) << "Bienvenido a nuestro gestor de impuestos" << endl;
	f.imprimeSimbolo(60, '-');
	cout << "Elija la opcion que desee ejecutar: " << endl;
	cout << setw(30) << "1. Ingresar como individuo" << endl;
	cout << setw(28) << "2. Ingresar como empresa" << endl;
	cout << setw(12) << "3. Salir" << endl;
	f.imprimeSimbolo(60, '-');
	/*Validacion de la opcion ingresada*/
	do {
		cout << "Escriba la opcion aqui: ";
		cin >> opcion;

		// Verificar si la entrada falló
		if (cin.fail()) {
			cout << "Opcion invalida. Por favor ingrese un numero entero." << endl;
			cout << endl;
			// Limpiar el estado de error de cin y descartar el buffer de entrada
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue; // Volver al principio del bucle
		}

		if (opcion < 1 || opcion > 3) {
			cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl << endl;
		}
	} while (opcion < 1 || opcion > 3);

	/*Se limpia la pantalla cuando el usuario introduce una opcion valida*/
	system("CLS");

	/*Creacion de instancias para mostrar el menu correspondiente a la opcion elegida*/
	Menu* menu = nullptr;

	/*Se crean las listas que gestionaran los datos de cada tipo de usuario*/
	Lista<Empresa*>* lstEmpresa = new Lista<Empresa*>;
	Lista<CContribuyente*>* lstContribuyente = new Lista<CContribuyente*>;

	/*Se crean las tablas hash que gestionaran los datos de cada tipo de usuario*/
	HashTabla<CContribuyente>* hashContribuyente = new HashTabla<CContribuyente>;
	HashTabla<Empresa>* hashEmpresa = new HashTabla<Empresa>;

	/*Se crean los arboles binarios que gestionaran los datos de cada tipo de usuario*/
	ArbolBB<CContribuyente*>* arbolContribuyentes = new ArbolBB<CContribuyente*>([](CContribuyente* c) {
		cout << "Nombre: " << c->nombre << endl;
		cout << "ID: " << c->id << endl;
		cout << "Ingresos: " << c->ingresos << endl;
		cout << "Monto de Venta: " << c->montoVenta << endl;
		cout << "---------------------------" << endl;
		}, 
		[](CContribuyente* a, CContribuyente* b) -> int {
			return a->id - b->id;
		});

	ArbolBB<Empresa*>* arbolEmpresa = new ArbolBB<Empresa*>([](Empresa* c) {
		cout << "Nombre: " << c->nombre << endl;
		cout << "ID: " << c->RUC << endl;
		cout << "Ingresos: " << c->ingresos << endl;
		cout << "Monto de Venta: " << c->montoVenta << endl;
		cout << "---------------------------" << endl;
		}, 
		[](Empresa* a, Empresa* b) -> int {
			return a->RUC - b->RUC;
		});

	

	if (opcion == 1) {
		/*se pasa la lista Contribuyete como parametro en el constructor de menuIndividuo*/
		menu = new MenuIndividuo(lstContribuyente, hashContribuyente, arbolContribuyentes);
	}

	else if (opcion == 2) {
		/*se pasa la lista Empresa como parametro en el constructor de menuEmpresa*/
		menu = new MenuEmpresa(lstEmpresa, hashEmpresa, arbolEmpresa);
	}
	else {
		cout << "Salir del programa" << endl;
		delete lstEmpresa;  // Liberar memoria de la lista de empresas
		delete lstContribuyente;  // Liberar memoria de la lista de contribuyentes
		return 0;
	}
	/*Despliegue y ejecucion de las operaciones correspondientes a cada menu*/
	int operacion;
	do {
		if (menu != nullptr) {
			menu->mostrarMenu();
			cout << "Ingrese la operacion que desee ejecutar: ";
			cin >> operacion;

			// Verificar si la entrada falló
			if (cin.fail()) {
				cout << "Opcion invalida. Por favor ingrese un numero entero." << endl;
				cout << endl;
				// Limpiar el estado de error de cin y descartar el buffer de entrada
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue; // Volver al principio del bucle
			}

			menu->opcionSeleccionada(operacion);
			cout << endl;
		}
	} while (operacion != 7);
	delete menu;

	return 0;
}