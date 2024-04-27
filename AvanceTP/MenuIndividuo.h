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
    void agregarNuevoContribuyente(Lista<CContribuyente*>* lst) const;
    void calcularImpuestosContribuyente(Lista<CContribuyente*>* lst) const;
    void mostrarContribuyentes(Lista<CContribuyente*>* lst) const;
    void ordenarContribuyentes(Lista<CContribuyente*>* lst) const;
};

