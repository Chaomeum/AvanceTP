#pragma once
#include "Impuesto.h"
#include <string>
#include <sstream>
using namespace std;

class Empresa
{
public :
	string nombre;
	int RUC;
	double ingresos;
	double montoVenta;
	string ciudad;
	string estadoDeudor;

	Empresa() {
		this->nombre = "";
		this->RUC = 0;
		this->ingresos = 0.0;
		this->montoVenta = 0.0;
		this->ciudad = "";
		this->estadoDeudor = "";
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

