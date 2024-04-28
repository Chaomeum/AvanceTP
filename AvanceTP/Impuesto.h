#pragma once
#include <iostream>
#include <functional>
using namespace std;

class CImpuesto
{
private:
	string nombre;
   
public:
	CImpuesto() {
		this->nombre = "";
	};
	void setNombre(std::string nombre) { this->nombre = nombre; }
	string getNombre() const { return nombre; }
    //Recursividad
    double calcularImpuestosPorIngresos(double ingresos) {

        if (ingresos < 2000) {
            return ingresos * 0.10; // 10% de impuestos
        }
        else if (ingresos >= 2000 && ingresos < 4000) {
            return ingresos * 0.20 + calcularImpuestosPorIngresos(ingresos - 2000); // 20% de impuestos
        }
        else {
            return ingresos * 0.30 + calcularImpuestosPorIngresos(ingresos - 4000); // 30% de impuestos
        }
    }

    //Recursividad
    double calcularImpuestosVenta(double montoVenta) {

        if (montoVenta < 200) {
            return montoVenta * 0.02; // 2% de impuestos
        }
        else if (montoVenta >= 200 && montoVenta < 400) {
            return montoVenta * 0.04 + calcularImpuestosVenta(montoVenta - 200); // 4% de impuestos
        }
        else {
            return montoVenta * 0.06 + calcularImpuestosVenta(montoVenta - 400); // 6% de impuestos
        }
    }
};
