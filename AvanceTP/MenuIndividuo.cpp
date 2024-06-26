#include "MenuIndividuo.h"

void MenuIndividuo::mostrarMenu() const
{
    FuncionesArch f;
    f.imprimeSimbolo(46, '-');
    cout << setw(31) << "MENU INDIVIDUO" << endl;
    f.imprimeSimbolo(46, '-');
    cout << "1.- Crear informacion de contribuyentes." << endl;
    cout << "2.- Calcular impuestos para un contribuyente." << endl;
    cout << "3.- Mostrar informacion de contribuyentes." << endl;
    cout << "4.- Ordenar contribuyentes por alg�n criterio." << endl;
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
        agregarNuevoContribuyente(lst, ht, arb);
        break;
    case 2:
        calcularImpuestosContribuyente(lst, ht);
        break;
    case 3:
        mostrarContribuyentes(lst, ht, arb);
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
void MenuIndividuo::agregarNuevoContribuyente(Lista<CContribuyente*>* lst, HashTabla<CContribuyente>* ht, ArbolBB<CContribuyente*>* arb) const
{
    cout << "Opcion 1: Crear informacion de contribuyentes" << endl;
    cout << endl;

    srand(time(0));
    CContribuyente c;
    /*Se generan datos para 50 a 300 contribuyentes*/
    int numContribuyentes = rand() % 250 + 50;
    for (int i = 0; i < numContribuyentes; ++i) {
        CContribuyente* contribuyente = new CContribuyente(c.generarContribuyente(i + 1));
        bool idOcupada = false;

        // Implementaci�n de iteradores
        for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
            if ((*it)->id == contribuyente->id) {
                idOcupada = true;
                break;
            }
        }

        if (!idOcupada) {
            lst->agregaInicial(contribuyente);
            arb->insertar(contribuyente);
            ht->insertC(contribuyente);
            cout << "El contribuyente " << contribuyente->nombre << " fue agregado con exito." << endl;
        }
        else {
            cout << "Lo sentimos, la ID " << contribuyente->id << " ya esta ocupada." << endl;
            delete contribuyente;
        }
    }
}

//Opcion 2
void MenuIndividuo::calcularImpuestosContribuyente(Lista<CContribuyente*>* lst , HashTabla<CContribuyente>* ht) const
{
    cout << "Opcion 2: Calcular impuestos por contribuyente" << endl;
    cout << endl;
    cout << "Ingrese el ID del contribuyente para calcular sus impuestos: ";
    int idContribuyente;
    cin >> idContribuyente;
    int opcionBusqueda;

    CContribuyente* contribuyente = nullptr;


    do {
        cout << "�Por que criterio desea buscar al contribuyente?" << endl;
        cout << "1.- Mediante Listas." << endl;
        cout << "2.- Mediante Tablas de Hash." << endl;
        cin >> opcionBusqueda;
        if (opcionBusqueda == 1) {
            /*Implementacion de iteradores*/
            for (Lista<CContribuyente*>::Iterador it = lst->begin(); it != lst->end(); ++it) {
                if ((*it)->id == idContribuyente) {
                    contribuyente = *it;
                    break;
                }
            }
        }
        else if (opcionBusqueda == 2){
            if (ht->containsC(idContribuyente)) {
                contribuyente = ht->getC(idContribuyente);
            }
        }
        else {
            cout << "Opci�n inv�lida." << endl;
        }
    } while (opcionBusqueda < 1 || opcionBusqueda > 2);
   

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
        cout << "No se encontr� ning�n contribuyente con el ID ingresado." << endl;
    }
}

//Opcion 3
void MenuIndividuo::mostrarContribuyentes(Lista<CContribuyente*>* lst, HashTabla<CContribuyente>* ht, ArbolBB<CContribuyente*>* arb) const
{
    int opcionOrdenamiento;
    cout << "Opcion 3: Mostrar informacion de contribuyentes." << endl;
    cout << endl;
    if (lst->esVacia()) {
        cout << "No hay contribuyentes para mostrar." << endl;
        return;
    }
    do {
        cout << "�Por que criterio desea mostrar a los contribuyentes?" << endl;
        cout << "1.- Mediante listas." << endl;
        cout << "2.- Mediante Tablas de Hash." << endl;
        cout << "3.- Mediante Arbol Binario." << endl << endl;
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
            cout << "Tabla de Hash de Contribuyentes:" << endl;
            cout << "---------------------------" << endl;
            ht->displayTableC();
            cout << endl;
        }
        else if (opcionOrdenamiento == 3) {

            cout << "�rbol Binario de Contribuyentes (InOrden):" << endl;
            cout << endl;
            arb->enOrden();
            cout << endl;
        }
        else {
            cout << "Opci�n inv�lida." << endl;
        }
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 3);
}

//Opcion 4
void MenuIndividuo::ordenarContribuyentes(Lista<CContribuyente*>* lst) const
{
    int opcionOrdenamiento;
    cout << "Opcion 4: Ordenar contribuyentes." << endl;
    cout << endl;
    do {
        cout << "�Por que criterio desea ordenar a los contribuyentes?" << endl;
        cout << "1.- Por ingresos.(Heap Sort)" << endl;
        cout << "2.- Por ingresos.(Quick Sort)" << endl;
        cout << "3.- Por monto de venta. (Heap Sort)" << endl;
        cout << "4.- Por monto de venta. (Quick Sort)" << endl << endl;
        cin >> opcionOrdenamiento;
        if (opcionOrdenamiento == 1) {
            lst->sortHeapPorIngresos();
            cout << "Contribuyentes ordenados por cantidad de ingresos. (HeapSort)" << endl;
        }
        else if (opcionOrdenamiento == 2) {
            lst->quickSortIngresos();
            cout << "Contribuyentes ordenados por cantidad de ingresos. (QuickSort)" << endl;
        }
        else if (opcionOrdenamiento == 3) {
            lst->sortHeapPorVentas();
            cout << "Contribuyentes ordenados por monto de venta. (HeapSort)" << endl;
        }
        else if (opcionOrdenamiento == 4) {
            lst->quickSortMontoVenta();
            cout << "Contribuyentes ordenados por monto de venta. (QuickSort)" << endl;
        }
        else {
            cout << "Opci�n inv�lida." << endl;
        }
    } while (opcionOrdenamiento < 1 || opcionOrdenamiento > 4);
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