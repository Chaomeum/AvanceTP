#pragma once
#include <iostream>
#include "Menu.h"
#include "lista.hpp"
#include "Contribuyente.h"
using namespace std;

class MenuIndividuo : public Menu
{
private:
    Lista<CContribuyente*>* lst;

public:
    void mostrarMenu() const override;
    void opcionSeleccionada(int opcion) const override;

private:
    void agregarNuevoContribuyente(Lista<CContribuyente*>* lst) const;      //Opcion 1
    void calcularImpuestosContribuyente(Lista<CContribuyente*>* lst) const; //Opcion 2
    void generarReporteContribuyentes() const;                              //Opcion 3
    void mostrarContribuyentes(Lista<CContribuyente*>* lst) const;          //Opcion 4
    void ordenarContribuyentes(Lista<CContribuyente*>* lst) const;          //Opcion 5
    void guardarDatosContribuyentes() const;                                //Opcion 6
    void cargarDatosContribuyentes() const;                                 //Opcion 7
};

