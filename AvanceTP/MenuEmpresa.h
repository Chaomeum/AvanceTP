#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Menu.h"
#include "lista.hpp"
#include "Empresa.h"
#include "Cola.h"
#include "HashTabla.h"
#include "ArbolBinario.h"
#include "FuncionesArch.h"
using namespace std;

class MenuEmpresa : public Menu
{
private:
    Lista<Empresa*>* lst;
    Cola<Empresa*>* cola;
    HashTabla<Empresa>* ht;
    ArbolBB<Empresa*>* arb;
public:
    MenuEmpresa(Lista<Empresa*>* lista, HashTabla<Empresa>* ht,ArbolBB<Empresa*>* arbol) : lst(lista), ht(ht), arb(arbol) {}
    void mostrarMenu() const override;
    void opcionSeleccionada(int opcion) const override;
private:    
    void agregarNuevaEmpresa(Lista<Empresa*>* lst, HashTabla<Empresa>* ht, ArbolBB<Empresa*>* arb) const;    //Opcion 1
    void calcularImpuestosEmpresa(Lista<Empresa*>* lst, HashTabla<Empresa>* ht) const;                       //Opcion 2
    void verEstadoImpuestosEmpresa(Cola<Empresa*>* cola) const;                                     //Opcion 3
    void mostrarEmpresas(Lista<Empresa*>* lst, HashTabla<Empresa>* ht, ArbolBB<Empresa*>* arb) const;        //Opcion 4
    void ordenarEmpresas(Lista<Empresa*>* lst) const;                                               //Opcion 5
    void guardarDatosEmpresas(Lista<Empresa*>* lst) const;                                          //Opcion 6
};

