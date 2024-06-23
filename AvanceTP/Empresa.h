#pragma once
#include "Impuesto.h"
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class Empresa
{
public :
	string nombre;
	int RUC;
	double ingresos;
	double montoVenta;
	int ciudadInt;
	string ciudad;
	string estadoDeudor;

	Empresa() {
		this->nombre = "";
		this->RUC = 0;
		this->ingresos = 0.0;
		this->montoVenta = 0.0;
		this->ciudadInt = 0;
		this->ciudad = "";
		this->estadoDeudor = "";
	}

	/*Generador Dataset para Contribuyentes*/
	Empresa generarEmpresa(int id) {
		Empresa empresa;	
		empresa.RUC = rand() % 20000 + 9000;
		// Se genera el nombre general de la empresa
		empresa.nombre = "Empresa" + intToString(id);
		// Los ingresos de las empresas varia de 15000 a 25000 soles
		empresa.ingresos = rand() % 10000 + 15000;
		// El monto de venta de las empresas varia de 2000 a 10000 soles
		empresa.montoVenta = rand() % 8000 + 2000;
		// La ciudad se elige entre cuatro opciones
		empresa.ciudadInt = rand() % 4 + 1;
		switch (empresa.ciudadInt) {
		case 1:
			empresa.ciudad = "Lima";
			break;
		case 2:
			empresa.ciudad = "Arequipa";
			break;
		case 3:
			empresa.ciudad = "Cuzco";
			break;
		case 4:
			empresa.ciudad = "Ica";
			break;
		}
		empresa.estadoDeudor = (rand() % 2 == 0) ? "true" : "false";
		return empresa;
	}

	string intToString(int num) {
		stringstream ss;
		ss << num;
		return ss.str();
	}

	string ToString() {
		stringstream ss;
		ss << "Nombre:\t" << this->nombre << endl;
		ss << "Numero de RUC:\t" << this->RUC << endl;
		ss << "Numero de ingresos:\t" << this->ingresos << endl;
		ss << "Numero de monto de venta:\t" << this->montoVenta << endl;
		ss << "Nombre de ciudad:\t" << this->ciudad << endl;
		ss << "Estado deudor:\t" << this->estadoDeudor << endl;
		return ss.str();
	}
};
