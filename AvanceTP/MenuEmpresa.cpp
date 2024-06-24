#include "MenuEmpresa.h"

void MenuEmpresa::mostrarMenu() const
{
    FuncionesArch f;
    f.imprimeSimbolo(58, '-');
    cout << setw(37) << "MENU EMPRESA" << endl;
    f.imprimeSimbolo(58, '-');
    cout << "1.- Crear informacion de empresas." << endl;
    cout << "2.- Calcular impuestos para una empresa." << endl;
    cout << "3.- Simular una cola a traves de un archivo" << endl;
    cout << "4.- Mostrar informacion de empresas." << endl;
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
        agregarNuevaEmpresa(lst, ht, arb);
        break;
    case 2:
        calcularImpuestosEmpresa(lst, ht);
        break;
    case 3:
        verEstadoImpuestosEmpresa(cola);
        break;
    case 4:
        mostrarEmpresas(lst, ht, arb);
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
void MenuEmpresa::agregarNuevaEmpresa(Lista<Empresa*>* lst, HashTabla<Empresa>* ht, ArbolBB<Empresa*>* arb) const
{
    cout << "Opcion 1: Crear informacion de empresas" << endl;
    cout << endl;
    
    srand(time(0));
    Empresa e;
    /*Se generan datos para 50 a 300 empresas*/
    int numEmpresas = rand() % 250 + 50;
    for (int i = 0; i < numEmpresas; ++i) {
        Empresa* empresa = new Empresa(e.generarEmpresa(i + 1));
        bool rucOcupada = false;

        // Implementación de iteradores
        for (Lista<Empresa*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
            if ((*it)->RUC == empresa->RUC) {
                rucOcupada = true;
                break;
            }
        }

        if (!rucOcupada) {
            lst->agregaInicial(empresa);
            ht->insertE(empresa);
            arb->insertar(empresa);
            /*ht->insert(empresa);*/
            cout << "El contribuyente " << empresa->nombre << " fue agregado con exito." << endl;
        }
        else {
            cout << "Lo sentimos, la RUC " << empresa->RUC << " ya esta ocupada." << endl;
            delete empresa;
        }
    }
}

//Opcion 2
void MenuEmpresa::calcularImpuestosEmpresa(Lista<Empresa*>* lst, HashTabla<Empresa>* ht) const
{
    cout << "Opcion 2: Calcular impuestos por empresa" << endl;
    cout << endl;
    cout << "Ingrese el RUC de la empresa para calcular sus impuestos: ";
    int rucEmpresa;
    cin >> rucEmpresa;
    int opcionBusqueda;
    
    Empresa* empresa = nullptr;

   
    do {
        cout << "¿Por que criterio desea buscar a la empresa?" << endl;
        cout << "1.- Mediante Listas." << endl;
        cout << "2.- Mediante Tablas de Hash." << endl;
        cin >> opcionBusqueda;
        if (opcionBusqueda == 1) {
            /*Implementacion de iteradores*/
            for (Lista<Empresa*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
                if ((*it)->RUC == rucEmpresa) {
                    empresa = *it;
                    break;
                }
            }
        }
        else if (opcionBusqueda == 2) {
            if (ht->containsE(rucEmpresa)) {
                empresa = ht->getE(rucEmpresa);
            }
        }
        else {
            cout << "Opción inválida." << endl;
        }
    } while (opcionBusqueda < 1 || opcionBusqueda > 2);


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
    cout << "Opcion 3: Simular una cola de empresas a traves de un archivo" << endl;
    cout << endl;
    ifstream arch("ArchivoEmpresas.csv", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo ArchivoEmpresas.csv" << endl;
        exit(1);
    }
    char* ptrNombre, * ptrCiudad, * ptrEstadoDeudor, car;
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
void MenuEmpresa::mostrarEmpresas(Lista<Empresa*>* lst, HashTabla<Empresa>* ht, ArbolBB<Empresa*>* arb) const
{
    int opcionOrdenamiento;
    cout << "Opcion 4: Mostrar empresas afiliadas." << endl;
    cout << endl;
    if (lst->esVacia()) {
        cout << "No hay empresas para mostrar." << endl;
        return;
    }

    cout << "Lista de empresas afiliadas:" << endl;
    cout << "---------------------------" << endl;

    do {
        cout << "¿Por que criterio desea mostrar a los contribuyentes?" << endl;
        cout << "1.- Mediante listas." << endl;
        cout << "2.- Mediante Hash Table." << endl;
        cout << "3.- Mediante Arboles Binarios." << endl << endl;
        cin >> opcionOrdenamiento;
        if (opcionOrdenamiento == 1) {


            cout << "Lista de empresas afiliadas:" << endl;
            cout << "---------------------------" << endl;


            /*Implementacion de iteradores*/
            for (Lista<Empresa*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
                cout << "Nombre: " << (*it)->nombre << endl;
                cout << "RUC: " << (*it)->RUC << endl;
                cout << "Ingresos: " << (*it)->ingresos << endl;
                cout << "Monto de Venta: " << (*it)->montoVenta << endl;
                cout << "Ciudad: " << (*it)->ciudad << endl;
                cout << "Estado deudor: " << (*it)->estadoDeudor << endl;
                cout << "---------------------------" << endl;
            }

        }
        else if (opcionOrdenamiento == 2) {
            cout << "Tabla de Hash de Empresas:" << endl;
            cout << "---------------------------" << endl;
            ht->displayTableE();
            cout << endl;
        }
        else if (opcionOrdenamiento == 3) {
            cout << "Árbol Binario de Empresas (InOrden):" << endl;
            cout << endl;
            arb->enOrden();
            cout << endl;
        }
        else {
            cout << "Opción inválida." << endl;
        }
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 3);
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
            lst->sortMergePorIngresos();
            cout << "Empresas ordenados por cantidad de ingresos." << endl;
        }
        else if (opcionOrdenamiento == 2) {
            lst->sortMergePorVentas();
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

    /*for (int i = 0; i < lst->longitud(); i++)
    {
        Empresa* e = lst->obtenerPos(i);
        arch << e->nombre << setw(8) << e->RUC << setw(15) << e->ingresos << setw(13) <<
            e->montoVenta << setw(12) << e->ciudad << setw(16) << e->estadoDeudor << endl;
    }*/

    /*Implementacion de iteradores*/
    for (Lista<Empresa*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
        arch << (*it)->nombre << setw(8) << (*it)->RUC << setw(15) << (*it)->ingresos << setw(13) <<
            (*it)->montoVenta << setw(12) << (*it)->ciudad << setw(16) << (*it)->estadoDeudor << endl;
    }
}
