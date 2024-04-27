#pragma once
#include <iostream>
using namespace std;

class Menu
{
public:
    virtual void mostrarMenu() const = 0;
    virtual void opcionSeleccionada(int opcion) const = 0;
};