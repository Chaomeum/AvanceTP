#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Menu.h"
#include "lista.hpp"
#include "FuncionesArch.h"
#include "Contribuyente.h"
using namespace std;

class MenuIndividuo : public Menu
{
private:
    Lista<CContribuyente*>* lst;

public:
    MenuIndividuo(Lista<CContribuyente*>* lista) : lst(lista) {}
    void mostrarMenu() const override;
    void opcionSeleccionada(int opcion) const override;

private:
    void agregarNuevoContribuyente(Lista<CContribuyente*>* lst) const;      //Opcion 1
    void calcularImpuestosContribuyente(Lista<CContribuyente*>* lst) const; //Opcion 2
    void mostrarContribuyentes(Lista<CContribuyente*>* lst) const;          //Opcion 3
    void ordenarContribuyentes(Lista<CContribuyente*>* lst) const;          //Opcion 4
    void guardarDatosContribuyentes(Lista<CContribuyente*>* lst) const;     //Opcion 5
    void cargarDatosContribuyentes(Lista<CContribuyente*>* lst) const;      //Opcion 6
};

