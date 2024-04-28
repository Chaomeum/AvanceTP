#pragma once
#include "Menu.h"
#include "lista.hpp"
#include "Empresa.h"

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
    void generarReporteEmpresa() const;                         //Opcion 4
    void mostrarEmpresas(Lista<Empresa*>* lst) const;           //Opcion 5
    void ordenarEmpresas(Lista<Empresa*>* lst) const;           //Opcion 6
    void guardarDatosEmpresas() const;                          //Opcion 7
};  

