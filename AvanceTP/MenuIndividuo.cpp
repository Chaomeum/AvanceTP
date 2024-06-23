#include "MenuIndividuo.h"

void MenuIndividuo::mostrarMenu() const
{
    FuncionesArch f;
    f.imprimeSimbolo(46, '-');
    cout << setw(31) << "MENU INDIVIDUO" << endl;
    f.imprimeSimbolo(46, '-');
    cout << "1.- Agregar un nuevo contribuyente." << endl;
    cout << "2.- Calcular impuestos para un contribuyente." << endl;
    cout << "3.- Ver lista de contribuyentes." << endl;
    cout << "4.- Ordenar contribuyentes por algún criterio." << endl;
    cout << "5.- Guardar datos en archivo." << endl;
    cout << "6.- Cargar datos desde archivo." << endl;
    cout << "7.- Salir del programa." << endl;
    f.imprimeSimbolo(46, '-');
}

void MenuIndividuo::opcionSeleccionada(int opcion) const
{
    FuncionesArch f;
    f.imprimeSimbolo(46, '-');
    switch (opcion) {
    case 1:
        agregarNuevoContribuyente(lst, arb);
        break;
    case 2:
        calcularImpuestosContribuyente(lst);
        break;
    case 3:
        mostrarContribuyentes(lst, arb);
        break;
    case 4:
        ordenarContribuyentes(lst);
        break;
    case 5:
        guardarDatosContribuyentes(lst);
        break;
    case 6:
        cargarDatosContribuyentes(lst);
        break;
    }
}

//Opcion 1
void MenuIndividuo::agregarNuevoContribuyente(Lista<CContribuyente*>* lst, ArbolBB<CContribuyente*>* arb) const
{
    cout << "Opcion 1: Agregar un nuevo contribuyente" << endl;
    cout << endl;
    CContribuyente* contribuyente = new CContribuyente();
    cout << "Ingrese el nombre del contribuyente: ";
    cin >> contribuyente->nombre;

    cout << "Ingrese el numero de ID: ";
    cin >> contribuyente->id;

    cout << "Ingrese el numero de ingresos: ";
    cin >> contribuyente->ingresos;

    cout << "Ingrese el numero de monto de venta: ";
    cin >> contribuyente->montoVenta;

    bool idOcupada = false;
    /*for (int i = 0; i < lst->longitud(); i++) {
        CContribuyente* e = lst->obtenerPos(i);
        if (e->id == contribuyente->id) {
            idOcupada = true;
            break;
        }
    }*/

    /*Implementacion de iteradores*/
    for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
        if ((*it)->id == contribuyente->id) {
            idOcupada = true;
            break;
        }
    }


    if (!idOcupada) {
        lst->agregaInicial(contribuyente);
        arb->insertar(contribuyente);
        cout << "El contribuyente fue agregado con exito." << endl;
    }
    else {
        cout << "Lo sentimos, la ID que ingreso ya esta ocupada." << endl;
        delete contribuyente;
    }
}

//Opcion 2
void MenuIndividuo::calcularImpuestosContribuyente(Lista<CContribuyente*>* lst) const
{
    cout << "Opcion 2: Calcular impuestos por contribuyente" << endl;
    cout << endl;
    cout << "Ingrese el ID del contribuyente para calcular sus impuestos: ";
    int idContribuyente;
    cin >> idContribuyente;

    CContribuyente* contribuyente = nullptr;

    /*for (int i = 0; i < lst->longitud(); i++) {
        CContribuyente* e = lst->obtenerPos(i);
        if (e->id == idContribuyente) {
            contribuyente = e;
            break;
        }
    }*/

    /*Implementacion de iteradores*/
    for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
        if ((*it)->id == idContribuyente) {
            contribuyente = *it;
            break;
        }
    }

    if (contribuyente != nullptr) {
        cout << "Contribuyente detectado:" << endl;
        cout << "Nombre: " << contribuyente->nombre << endl;
        cout << "ID: " << contribuyente->id << endl;
        cout << "Ingresos: " << contribuyente->ingresos << endl;
        cout << "Monto de Venta: " << contribuyente->montoVenta << endl;

        CImpuesto impuesto;
        double impuestosIngresos = impuesto.calcularImpuestosPorIngresos(contribuyente->ingresos);
        double impuestosVenta = impuesto.calcularImpuestosVenta(contribuyente->montoVenta);
        double impuestosTotales = impuestosIngresos + impuestosVenta;

        cout << "Impuestos de Ingresos: " << impuestosIngresos << endl;
        cout << "Impuestos de Venta: " << impuestosVenta << endl;
        cout << "Impuestos totales: " << impuestosTotales << endl;
    }
    else {
        cout << "No se encontró ningún contribuyente con el ID ingresado." << endl;
    }
}

//Opcion 3
void MenuIndividuo::mostrarContribuyentes(Lista<CContribuyente*>* lst, ArbolBB<CContribuyente*>* arb) const
{
    int opcionOrdenamiento;
    cout << "Opcion 3: Mostrar contribuyentes." << endl;
    cout << endl;
    if (lst->esVacia()) {
        cout << "No hay contribuyentes para mostrar." << endl;
        return;
    }
    do {
        cout << "¿Por que criterio desea mostrar a los contribuyentes?" << endl;
        cout << "1.- Mediante listas." << endl;
        cout << "2.- Mediante Arbol Binario." << endl << endl;
        cin >> opcionOrdenamiento;
        if (opcionOrdenamiento == 1) {

            cout << "Lista de Contribuyentes :" << endl;
            cout << "---------------------------" << endl;
            /*Implementacion de iteradores*/
            for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
                cout << "Nombre: " << (*it)->nombre << endl;
                cout << "ID: " << (*it)->id << endl;
                cout << "Ingresos: " << (*it)->ingresos << endl;
                cout << "Monto de Venta: " << (*it)->montoVenta << endl;
                cout << "---------------------------" << endl;
            }

        }
        else if (opcionOrdenamiento == 2) {

            cout << "Árbol Binario de Contribuyentes (InOrden):" << endl;
            cout << endl;
            arb->enOrden();
            cout << endl;
        }
        else {
            cout << "Opción inválida." << endl;
        }
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 2);
}

//Opcion 4
void MenuIndividuo::ordenarContribuyentes(Lista<CContribuyente*>* lst) const
{
    int opcionOrdenamiento;
    cout << "Opcion 4: Ordenar contribuyentes." << endl;
    cout << endl;
    do {
        cout << "¿Por que criterio desea ordenar a los contribuyentes?" << endl;
        cout << "1.- Por ingresos." << endl;
        cout << "2.- Por monto de venta." << endl << endl;
        cin >> opcionOrdenamiento;
        if (opcionOrdenamiento == 1) {
            lst->sortShellPorIngresos();
            cout << "Contribuyentes ordenados por cantidad de ingresos." << endl;
        }
        else if (opcionOrdenamiento == 2) {
            lst->sortShellPorVenta();
            cout << "Contribuyentes ordenados por monto de venta." << endl;
        }
        else {
            cout << "Opción inválida." << endl;
        }
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 2);
}

//Opcion 5
void MenuIndividuo::guardarDatosContribuyentes(Lista<CContribuyente*>* lst) const
{
    cout << "Opcion 5: Guardar Datos Contribuyentes en un archivo" << endl;
    cout << endl;
    ofstream arch("listaContribuyentes.txt", ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo listaContribuyentes.txt" << endl;
        exit(1);
    }
    arch << "Informacion recopilada sobre contribuyentes en el gestor de impuestos" << endl;
    for (int i = 0; i < 50; i++) arch << "-";
    arch << endl;
    arch << "Nombre" << setw(13) << "Numero ID" << setw(13) << "Ingresos" << setw(15) << "Monto Venta" << endl;
    for (int i = 0; i < 50; i++) arch << "-";
    arch << endl;

    /*for (int i = 0; i < lst->longitud(); i++)
    {
        CContribuyente* e = lst->obtenerPos(i);
        arch << left << setw(10) << e->nombre << right << fixed << setprecision(2) << setw(7) << e->id << setw(15)
            << e->ingresos << setw(13) << e->montoVenta << endl;
    }*/

    /* Implementacion de iteradores */
    for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
        arch << left << setw(10) << (*it)->nombre << right << fixed << setprecision(2) << setw(7) << (*it)->id << setw(15)
            << (*it)->ingresos << setw(13) << (*it)->montoVenta << endl;
    }
}

//Opcion 6
void MenuIndividuo::cargarDatosContribuyentes(Lista<CContribuyente*>* lst) const
{
    cout << "Opcion 6: Cargar Datos Contribuyentes desde un archivo" << endl;
    cout << endl;
    ifstream arch("ArchivoContribuyentes.csv", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo ArchivoContribuyentes.csv" << endl;
        exit(1);
    }
    char* ptrNombre, car;
    int id;
    double ingresos, monto;
    FuncionesArch f;
    int lon = lst->longitud();
    while (1) {
        CContribuyente* contribuyente = new CContribuyente();
        ptrNombre = f.leeCadenaExacta(arch, ',');
        if (arch.eof()) break;
        arch >> id >> car >> ingresos >> car >> monto;
        arch.get();
        contribuyente->nombre = ptrNombre;
        contribuyente->id = id;
        contribuyente->ingresos = ingresos;
        contribuyente->montoVenta = monto;

        lst->agregaPos(contribuyente, lon);
        lon++;
    }
}