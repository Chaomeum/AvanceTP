#include "MenuEmpresa.h"

void MenuEmpresa::mostrarMenu() const
{
    for (int i = 0; i < 58; i++) cout << "-";
    cout << endl;;
    cout << setw(37) << "MENU EMPRESA" << endl;
    for (int i = 0; i < 58; i++) cout << "-";
    cout << endl;
    cout << "1.- Agregar una nueva empresa." << endl;
    cout << "2.- Calcular impuestos para una empresa." << endl;
    cout << "3.- Ver estado de declaracion de impuestos de una empresa" << endl;
    cout << "4.- Generar reporte de impuestos." << endl;
    cout << "5.- Ver lista de empresas miembro." << endl;
    cout << "6.- Ordenar empresas por algún criterio." << endl;
    cout << "7.- Guardar datos en archivo." << endl;
    cout << "8.- Salir del programa." << endl;
    for (int i = 0; i < 58; i++) cout << "-";
    cout << endl;
}


void MenuEmpresa::opcionSeleccionada(int opcion) const
{
    for (int i = 0; i < 58; i++) cout << "-";
    cout << endl;
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
    Empresa* empresa = new Empresa();
    cout << "Ingrese el nombre de la empresa: ";
    cin >> empresa->nombre;

    cout << "Ingrese el RUC de la empresa: ";
    cin >> empresa->RUC;

    cout << "Ingresa los ingresos de la empresa: ";
    cin >> empresa->ingresos;

    cout << "Ingresa el monto de venta de la empresa: ";
    cin >> empresa->montoVenta;

    cout << "Ingresa el nombre de la ciudad de la empresa: ";
    cin >> empresa->ciudad;

    cout << "Ingresa el estado deudor de la empresa: ";
    cin >> empresa->estadoDeudor;

    bool rucOcupada = false;
    for (int i = 0; i < lst->longitud(); i++)
    {
        Empresa* b = lst->obtenerPos(i);
        if (b->RUC == empresa->RUC) {
            rucOcupada = true;
            break;
        }
    }

    if (!rucOcupada) {
        lst->agregaInicial(empresa);
        cout << "La empresa fue agregada con exito" << endl;
    }
    else {
        cout << "La RUC ingresada ya existe, no se pudo agregar la empresa" << endl;
        delete empresa;
    }
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
    cout << "Opcion 5: Mostrar empresas afiliadas." << endl;
    cout << endl;
    if (lst->esVacia()) {
        cout << "No hay empresas para mostrar." << endl;
        return;
    }

    cout << "Lista de empresas afiliadas:" << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < lst->longitud(); i++) {
        Empresa* empresa = lst->obtenerPos(i);
        cout << "Nombre: " << empresa->nombre << endl;
        cout << "RUC: " << empresa->RUC << endl;
        cout << "Ingresos: " << empresa->ingresos << endl;
        cout << "Monto de Venta: " << empresa->montoVenta << endl;
        cout << "Ciudad: " << empresa->ciudad << endl;
        cout << "Estado deudor: " << empresa->estadoDeudor << endl;
        cout << "---------------------------" << endl;
    }
}

//Opcion 6
void MenuEmpresa::ordenarEmpresas(Lista<Empresa*>* lst) const
{   
    int opcionOrdenamiento;
    cout << "Opcion 6: Ordenar Empresas." << endl;
    cout << endl;
    do {
        cout << "¿Por qué criterio desea ordenar?" << endl;
        cout << "1.- Por ingresos." << endl;
        cout << "2.- Por monto de venta." << endl;
        cin >> opcionOrdenamiento;
        if (opcionOrdenamiento == 1) {
            lst->sortBubblePorIngresos();
            cout << "Empresas ordenados por cantidad de ingresos." << endl;
        }
        else if (opcionOrdenamiento == 2) {
            lst->sortBubblePorVenta();
            cout << "Empresas ordenadas por monto de venta." << endl;
        }
        else {
            cout << "Opción inválida." << endl;
        }        
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 2);   
}

//Opcion 7
void MenuEmpresa::guardarDatosEmpresas() const
{
    cout << "Opcion 7" << endl;
}
