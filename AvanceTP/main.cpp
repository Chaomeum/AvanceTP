#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "lista.hpp"
#include "Contribuyente.h"
#include "Empresa.h"
#include "Menu.h"
#include "MenuIndividuo.h"
#include "MenuEmpresa.h"
using namespace std;

int main() {
	int opcion;
	/*Interfaz de bienvenida*/
	for (int i = 0; i < 60; i++) cout << "=";
	cout << endl;
	cout << setw(50) << "Bienvenido a nuestro gestor de impuestos" << endl;
	for (int i = 0; i < 60; i++) cout << "-";
	cout << endl;
	cout << "Elija la opcion que desee ejecutar: " << endl;
	cout << setw(30) << "1. Ingresar como individuo" << endl;
	cout << setw(28) << "2. Ingresar como empresa" << endl;
	cout << setw(12) << "3. Salir" << endl;	
	for (int i = 0; i < 60; i++) cout << "-";
	cout << endl;
	cout << "Escriba la opcion aqui: ";
	cin >> opcion;		

	//Se limpia la pantalla cuando el usuario introduce una opcion
	system("CLS");

	//Creacion de instancias para mostrar el menu correspondiente a la opcion elegida
	Menu* menu = nullptr;

	//Se crean las listas que gestionaran los datos de cada tipo de usuario
	Lista<Empresa*>* lstEmpresa = new Lista<Empresa*> ;
	Lista<CContribuyente*>* lstContribuyente = new Lista<CContribuyente*> ;

	switch (opcion) {
	case 1:		
		//se pasa la lista Contribuyete como parametro en el constructor de menuIndividuo
		menu = new MenuIndividuo(lstContribuyente); 
		break;
	case 2:		
		//se pasa la lista Empresa como parametro en el constructor de menuEmpresa
		menu = new MenuEmpresa(lstEmpresa);
		break;
	case 3:
		cout << "Salir del programa" << endl;
		break;
	default:
		cout << "Ha ingresado una opcion invalida" << endl;
		break;
	}

	int operacion;
	do {
		if (menu != nullptr) {
			menu->mostrarMenu();
			cout << "Ingrese la operacion que desee ejecutar: ";
			cin >> operacion;
			menu->opcionSeleccionada(operacion);	
			cout << endl;
		}
	} while (operacion != 8);
	delete menu;

	return 0;
}