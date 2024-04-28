#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Menu.h"
#include "lista.hpp"
#include "Empresa.h"
#include "FuncionesArch.h"
using namespace std;

class MenuEmpresa : public Menu
{
private:
    Lista<Empresa*>* lst;
    
public:
    MenuEmpresa(Lista<Empresa*>* lista) : lst(lista) {}
    void mostrarMenu() const override;
    void opcionSeleccionada(int opcion) const override;
private:
    void agregarNuevaEmpresa(Lista<Empresa*>* lst) const;       //Opcion 1
    void calcularImpuestosEmpresa(Lista<Empresa*>* lst) const;  //Opcion 2
    void verEstadoImpuestosEmpresa(Lista<Empresa*>* lst) const; //Opcion 3
    void mostrarEmpresas(Lista<Empresa*>* lst) const;           //Opcion 4
    void ordenarEmpresas(Lista<Empresa*>* lst) const;           //Opcion 5
    void guardarDatosEmpresas(Lista<Empresa*>* lst) const;      //Opcion 6
};  

