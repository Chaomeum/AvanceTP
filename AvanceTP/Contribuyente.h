#pragma once
#include "Impuesto.h"
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class CContribuyente
{
public:
    string nombre;
    int id;
    double ingresos;
    double montoVenta;
   
    CContribuyente() {
        this->nombre = "";
        this->id = 0;
        this->ingresos = 0.0;
        this->montoVenta = 0.0;    
    }

    /*Generador Dataset para Contribuyentes*/
    CContribuyente generarContribuyente(int id) {
        CContribuyente contribuyente;
        // El id se asignara de acuerdo al orden en que se genera el contribuyente
        contribuyente.id = id;
        // Se genera el nombre general del contribuyente
        contribuyente.nombre = "Contribuyente_" + intToString(id);
        // Los ingresos de los contribuyentes varia de 5000 a 25000 soles
        contribuyente.ingresos = rand() % 15000 + 5000; 
        // El monto de venta de los contribuyentes varia de 100 a 5000 soles
        contribuyente.montoVenta = rand() % 4900 + 100;
        return contribuyente;
    }

    string intToString(int num) {
        stringstream ss;
        ss << num;
        return ss.str();
    }

    string ToString() {
        stringstream ss;
        ss << "Nombre:\t" << this->nombre << endl;
        ss << "Numero de id:\t" << this->id << endl;
        ss << "Numero de ingresos:\t" << this->ingresos << endl;
        ss << "Numero de monto de venta:\t" << this->montoVenta << endl;
        return ss.str();
    }
};

