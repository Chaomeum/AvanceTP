#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
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

	switch (opcion) {
	case 1:
		cout << "Mostrar menu individuo" << endl;
		menu = new MenuIndividuo();
		break;
	case 2:
		cout << "Mostrar menu empresa" << endl;
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
			cout << "Ingrese el número de la opción que desea: ";
			cin >> operacion;
			menu->opcionSeleccionada(operacion);			
		}
	} while (operacion != 8);
	delete menu;

	return 0;
}