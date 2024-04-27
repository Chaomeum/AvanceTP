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

    double calcularImpuestosPorIngresos(double ingresos) const {
        double impuestos = 0.0;
        if (ingresos >= 1000 && ingresos < 2000) {
            impuestos = ingresos * 0.10; // 10% de impuestos
        }
        else if (ingresos >= 2000 && ingresos < 4000) {
            impuestos = ingresos * 0.20; // 20% de impuestos
        }
        else if (ingresos >= 4000) {
            impuestos = ingresos * 0.30; // 30% de impuestos
        }
        return impuestos;
    }

    double calcularImpuestosVenta(double montoVenta) const {
        double impuestos = 0.0;
        if (montoVenta >= 100 && montoVenta < 200) {
            impuestos = montoVenta * 0.02; // 2% de impuestos
        }
        else if (montoVenta >= 200 && montoVenta < 400) {
            impuestos = montoVenta * 0.04; // 4% de impuestos
        }
        else if (montoVenta >= 400) {
            impuestos = montoVenta * 0.06; // 6% de impuestos
        }
        return impuestos;
    }
};
