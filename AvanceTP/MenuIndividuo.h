#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Menu.h"
#include "lista.hpp"
#include "HashTabla.h"
#include "ArbolBinario.h"
#include "FuncionesArch.h"
#include "Contribuyente.h"
using namespace std;

class MenuIndividuo : public Menu
{
private:
    Lista<CContribuyente*>* lst;
    HashTabla<CContribuyente>* ht;   
    ArbolBB<CContribuyente*>* arb;

public:

    MenuIndividuo(Lista<CContribuyente*>* lista, HashTabla<CContribuyente>* ht, ArbolBB<CContribuyente*>* arbol) : lst(lista), ht(ht), arb(arbol) {}
 
    void mostrarMenu() const override;
    void opcionSeleccionada(int opcion) const override;

private:
    void agregarNuevoContribuyente(Lista<CContribuyente*>* lst, HashTabla<CContribuyente>* ht, ArbolBB<CContribuyente*>* arb) const;    //Opcion 1
    void calcularImpuestosContribuyente(Lista<CContribuyente*>* lst, HashTabla<CContribuyente>* ht) const;                              //Opcion 2
    void mostrarContribuyentes(Lista<CContribuyente*>* lst, HashTabla<CContribuyente>* ht, ArbolBB<CContribuyente*>* arb) const;        //Opcion 3
    void ordenarContribuyentes(Lista<CContribuyente*>* lst) const;                                                                      //Opcion 4
    void guardarDatosContribuyentes(Lista<CContribuyente*>* lst) const;                                                                 //Opcion 5
    void cargarDatosContribuyentes(Lista<CContribuyente*>* lst) const;                                                                  //Opcion 6
};

