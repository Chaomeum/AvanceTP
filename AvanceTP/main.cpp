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

		if (opcion < 1 || opcion > 3) {
			cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl << endl;
		}
	} while (opcion < 1 || opcion > 3);

	/*Se limpia la pantalla cuando el usuario introduce una opcion valida*/
	system("CLS");

	/*Creacion de instancias para mostrar el menu correspondiente a la opcion elegida*/
	Menu* menu = nullptr;

	/*Se crean las listas que gestionaran los datos de cada tipo de usuario*/
	Lista<Empresa*>* lstEmpresa = new Lista<Empresa*> ;
	Lista<CContribuyente*>* lstContribuyente = new Lista<CContribuyente*> ;

	if (opcion == 1) {
		/*se pasa la lista Contribuyete como parametro en el constructor de menuIndividuo*/
		menu = new MenuIndividuo(lstContribuyente);
	}
	else if (opcion == 2) {
		/*se pasa la lista Empresa como parametro en el constructor de menuEmpresa*/
		menu = new MenuEmpresa(lstEmpresa);
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
			menu->opcionSeleccionada(operacion);	
			cout << endl;
		}
	} while (operacion != 7);
	delete menu;

	return 0;
}