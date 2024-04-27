#pragma once
#include "Impuesto.h"
#include <vector>
#include <string>
#include <sstream>
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

   /* void setNombre(string nombre) { this->nombre = nombre; }
    string getNombre() { return nombre;}
    void setIdentificacion(int id) { this->id = id; }
    int getIdentificacion() { return id; }


    void setIngresos(double ingresos) { this->ingresos = ingresos; }
    double getIngresos()  { return ingresos; }

    void setMontoVenta(double montoVenta) { this->montoVenta = montoVenta; }
    double getMontoVenta()  { return montoVenta; }
    */

    string ToString() {
        stringstream ss;
        ss << "Nombre:\t" << this->nombre << endl;
        ss << "Numero de id:\t" << this->id << endl;
        ss << "Numero de ingresos:\t" << this->ingresos << endl;
        ss << "Numero de monto de venta:\t" << this->montoVenta << endl;
        return ss.str();
    }
};

