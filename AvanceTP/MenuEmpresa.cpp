#include "MenuEmpresa.h"

void MenuEmpresa::mostrarMenu() const
{
    cout << "===== MENU EMPRESA =====" << endl;
    cout << "1.- Agregar una nueva empresa." << endl;
    cout << "2.- Calcular impuestos para una empresa." << endl;
    cout << "3.- Ver estado de declaracion de impuestos de una empresa" << endl;
    cout << "4.- Generar reporte de impuestos." << endl;
    cout << "5.- Ver lista de empresas miembro." << endl;
    cout << "6.- Ordenar empresas por algún criterio." << endl;
    cout << "7.- Guardar datos en archivo." << endl;
    cout << "8.- Salir del programa." << endl;
}


void MenuEmpresa::opcionSeleccionada(int opcion) const
{
    switch (opcion) {
    case 1:
        agregarNuevaEmpresa(lst);
        break;
    case 2:
        calcularImpuestosEmpresa(lst);
        break;
    case 3:
        verEstadoImpuestosEmpresa(lst);
        break;
    case 4:
        generarReporteEmpresa();
        break;
    case 5:
        mostrarEmpresas(lst);
        break;
    case 6:
        ordenarEmpresas(lst);
        break;
    case 7:
        guardarDatosEmpresas();
        break;
    }
}

//Opcion 1
void MenuEmpresa::agregarNuevaEmpresa(Lista<Empresa*>* lst) const
{
    cout << "Opcion 1" << endl;
}

//Opcion 2
void MenuEmpresa::calcularImpuestosEmpresa(Lista<Empresa*>* lst) const
{
    cout << "Opcion 2" << endl;
}

//Opcion 3
void MenuEmpresa::verEstadoImpuestosEmpresa(Lista<Empresa*>* lst) const
{
    cout << "Opcion 3" << endl;
}

//Opcion 4
void MenuEmpresa::generarReporteEmpresa() const
{
    cout << "Opcion 4" << endl;
}

//Opcion 5
void MenuEmpresa::mostrarEmpresas(Lista<Empresa*>* lst) const
{
    cout << "Opcion 5" << endl;
}

//Opcion 6
void MenuEmpresa::ordenarEmpresas(Lista<Empresa*>* lst) const
{
    cout << "Opcion 6" << endl;
}

//Opcion 7
void MenuEmpresa::guardarDatosEmpresas() const
{
    cout << "Opcion 7" << endl;
}
