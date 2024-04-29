#include "MenuEmpresa.h"

void MenuEmpresa::mostrarMenu() const
{
    FuncionesArch f;    
    f.imprimeSimbolo(58, '-');
    cout << setw(37) << "MENU EMPRESA" << endl;
    f.imprimeSimbolo(58, '-');
    cout << "1.- Agregar una nueva empresa." << endl;
    cout << "2.- Calcular impuestos para una empresa." << endl;
    cout << "3.- Simular una cola a traves de un archivo" << endl; 
    cout << "4.- Ver lista de empresas miembro." << endl;
    cout << "5.- Ordenar empresas por algún criterio." << endl;
    cout << "6.- Guardar datos en archivo." << endl;
    cout << "7.- Salir del programa." << endl;
    f.imprimeSimbolo(58, '-');
}

void MenuEmpresa::opcionSeleccionada(int opcion) const
{
    FuncionesArch f;
    f.imprimeSimbolo(58, '-');
    switch (opcion) {
    case 1:
        agregarNuevaEmpresa(lst);
        break;
    case 2:
        calcularImpuestosEmpresa(lst);
        break;
    case 3:
        verEstadoImpuestosEmpresa(cola);
        break;   
    case 4:
        mostrarEmpresas(lst);
        break;
    case 5:
        ordenarEmpresas(lst);
        break;
    case 6:
        guardarDatosEmpresas(lst);
        break;
    }
}

//Opcion 1
void MenuEmpresa::agregarNuevaEmpresa(Lista<Empresa*>* lst) const
{
    cout << "Opcion 1: Agregar una nueva empresa" << endl;
    cout << endl;
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
    cout << "Opcion 2: Calcular impuestos por empresa" << endl;
    cout << endl; 
    cout << "Ingrese el RUC de la empresa para calcular sus impuestos: ";
    int rucEmpresa;
    cin >> rucEmpresa;

    Empresa* empresa = nullptr;
    for (int i = 0; i < lst->longitud(); i++)
    {
        Empresa* e = lst->obtenerPos(i);
        if (e->RUC == rucEmpresa) {
            empresa = e;
            break;
        }
    }

    if (empresa != nullptr) {
        cout << "Contribuyente detectado:" << endl;
        cout << "Nombre: " << empresa->nombre << endl;
        cout << "RUC: " << empresa->RUC << endl;
        cout << "Ingresos: " << empresa->ingresos << endl;
        cout << "Monto de Venta: " << empresa->montoVenta << endl;
        cout << "Ciudad: " << empresa->ciudad << endl;
        cout << "Estado deudor: " << empresa->estadoDeudor << endl;

        CImpuesto impuesto;
        double impuestosIngresos = impuesto.calcularImpuestosPorIngresos(empresa->ingresos);
        double impuestosVenta = impuesto.calcularImpuestosVenta(empresa->montoVenta);
        double impuestosTotales = impuestosIngresos + impuestosVenta;

        cout << "Impuestos de Ingresos: " << impuestosIngresos << endl;
        cout << "Impuestos de Venta: " << impuestosVenta << endl;
        cout << "Impuestos totales: " << impuestosTotales << endl;
    }
    else {
        cout << "No se encontró ninguna empresa con el RUC ingresado." << endl;
    }
}

//Opcion 3
void MenuEmpresa::verEstadoImpuestosEmpresa(Cola<Empresa*>* cola) const
{
    cout << "Opcion 3: Ver estado de impuestos de empresas" << endl;
    cout << endl;
    ifstream arch("ArchivoEmpresas.csv", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo ArchivoEmpresas.csv" << endl;
        exit(1);
    }
    char* ptrNombre, * ptrCiudad, *ptrEstadoDeudor, car;
    int ruc;
    double ingresos, monto;
    FuncionesArch f;
    //Cargamos datos del archivo a la cola
    cola = new Cola<Empresa*>();
    while (1) {
        Empresa* empresa = new Empresa();
        ptrNombre = f.leeCadenaExacta(arch, ',');
        if (arch.eof()) break;
        arch >> ruc >> car >> ingresos >> car >> monto >> car;
        ptrCiudad = f.leeCadenaExacta(arch, ',');
        ptrEstadoDeudor = f.leeCadenaExacta(arch, '\n');
        empresa->nombre = ptrNombre;
        empresa->RUC = ruc;
        empresa->ingresos = ingresos;
        empresa->montoVenta = monto;
        empresa->ciudad = ptrCiudad;
        empresa->estadoDeudor = ptrEstadoDeudor;

        cola->enqueue(empresa);
    }

    //Mostramos la cola en un archivo
    ofstream archCola("EmpresasEnCola.txt", ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo EmpresasEnCola.txt" << endl;
        exit(1);
    }
    //
    Empresa* elem;
    archCola << "Cola de empresas:" << endl;
    do {
        elem = cola->dequeue();
        archCola << elem->ToString() << endl;
    } while (!cola->esVacia());
    delete cola;
    cin.get();
}

//Opcion 4
void MenuEmpresa::mostrarEmpresas(Lista<Empresa*>* lst) const
{
    cout << "Opcion 4: Mostrar empresas afiliadas." << endl;
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

//Opcion 5
void MenuEmpresa::ordenarEmpresas(Lista<Empresa*>* lst) const
{   
    int opcionOrdenamiento;
    cout << "Opcion 5: Ordenar Empresas." << endl;
    cout << endl;
    do {
        cout << "¿Por que criterio desea ordenar a las empresas?" << endl;
        cout << "1.- Por ingresos." << endl;
        cout << "2.- Por monto de venta." << endl << endl;
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
            cout << "Opcion no valida." << endl;
        }        
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 2);   
}

//Opcion 6
void MenuEmpresa::guardarDatosEmpresas(Lista<Empresa*>* lst) const
{
    FuncionesArch f;
    cout << "Opcion 6: Guardar datos recopilados en archivo" << endl;
    cout << endl;
    ofstream arch("ListaEmpresas.txt", ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo ListaEmpresas.txt" << endl;
        exit(1);
    }
    arch << "Informacion recopilada sobre empresas en el gestor de impuestos" << endl;
    f.imprimeSimbolo(75, '-');
    arch << "Nombre" << setw(13) << "Numero RUC" << setw(13) << "Ingresos" << setw(15) << "Monto Venta"
        << setw(10) << "Ciudad" << setw(18) << "Estado deudor" << endl;
    f.imprimeSimbolo(75, '-');

    for (int i = 0; i < lst->longitud(); i++)
    {
        Empresa* e = lst->obtenerPos(i);
        arch << e->nombre << setw(8) << e->RUC << setw(15) << e->ingresos << setw(13) <<
            e->montoVenta << setw(12) << e->ciudad << setw(16) << e->estadoDeudor << endl;
    }
}
