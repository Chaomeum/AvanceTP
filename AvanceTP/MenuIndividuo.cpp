#include "MenuIndividuo.h"

void MenuIndividuo::mostrarMenu() const
{
    cout << "===== MENU INDIVIDUO =====" << endl;
    cout << "1.- Agregar un nuevo contribuyente." << endl;
    cout << "2.- Calcular impuestos para un contribuyente." << endl;
    cout << "3.- Generar reporte de impuestos." << endl;
    cout << "4.- Ver lista de contribuyentes." << endl;
    cout << "5.- Ordenar contribuyentes por algún criterio." << endl;
    cout << "6.- Guardar datos en archivo." << endl;
    cout << "7.- Cargar datos desde archivo." << endl;
    cout << "8.- Salir del programa." << endl;
}

void MenuIndividuo::opcionSeleccionada(int opcion) const
{
    switch (opcion) {
        case 1:
            agregarNuevoContribuyente(lst);
            break;
        case 2:
            calcularImpuestosContribuyente(lst);
            break;
        case 3:
            generarReporteContribuyentes();
            break;
        case 4:
            mostrarContribuyentes(lst);
            break;
        case 5:
            ordenarContribuyentes(lst);
            break;
        case 6:
            guardarDatosContribuyentes();
            break;
        case 7:
            cargarDatosContribuyentes();
            break;
    }
}

//Opcion 1
void MenuIndividuo::agregarNuevoContribuyente(Lista<CContribuyente*>* lst) const
{
    CContribuyente* contribuyente = new CContribuyente();
    cout << "Ingresar Nombre:";
    cin >> contribuyente->nombre;

    cout << "Ingrese el numero de id:";
    cin >> contribuyente->id;

    cout << "Ingrese el numero de ingresos:";
    cin >> contribuyente->ingresos;

    cout << "Ingrese el numero de monto de venta:";
    cin >> contribuyente->montoVenta;

    bool idOcupada = false;
    for (int i = 0; i < lst->longitud(); i++) {
        CContribuyente* e = lst->obtenerPos(i);
        if (e->id == contribuyente->id) {
            idOcupada = true;
            break;
        }
    }

    if (!idOcupada) {
        lst->agregaInicial(contribuyente);
        cout << "Contribuyente agregado con exito." << endl;
    }
    else {
        cout << "Lo siento, la id que ingreso ya esta ocupada." << endl;
        delete contribuyente;
    }
}

//Opcion 2
void MenuIndividuo::calcularImpuestosContribuyente(Lista<CContribuyente*>* lst) const
{
    cout << "Ingrese el ID del contribuyente para calcular sus impuestos: ";
    int idContribuyente;
    cin >> idContribuyente;

    CContribuyente* contribuyente = nullptr;
    for (int i = 0; i < lst->longitud(); i++) {
        CContribuyente* e = lst->obtenerPos(i);
        if (e->id == idContribuyente) {
            contribuyente = e;
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
void MenuIndividuo::generarReporteContribuyentes() const
{
    cout << "Implementar logica de generar Reporte de clientes" << endl;
}

//Opcion 4
void MenuIndividuo::mostrarContribuyentes(Lista<CContribuyente*>* lst) const
{
    cout << "Metodo para mostrar contribuyentes" << endl;
    if (lst->esVacia()) {
        cout << "No hay contribuyentes para mostrar." << endl;
        return;
    }

    cout << "Lista de Contribuyentes:" << endl;
    for (int i = 0; i < lst->longitud(); i++) {
        CContribuyente* contribuyente = lst->obtenerPos(i);
        cout << "Nombre: " << contribuyente->nombre << endl;
        cout << "ID: " << contribuyente->id << endl;
        cout << "Ingresos: " << contribuyente->ingresos << endl;
        cout << "Monto de Venta: " << contribuyente->montoVenta << endl;
        cout << "---------------------------" << endl;
    }
}

//Opcion 5
void MenuIndividuo::ordenarContribuyentes(Lista<CContribuyente*>* lst) const
{
    cout << "Opcion 5 seleccionada: Ordenar contribuyentes." << endl;
    cout << "¿Por qué criterio desea ordenar?" << endl;
    cout << "1.- Por ingresos." << endl;
    cout << "2.- Por monto de venta." << endl;
    int opcionOrdenamiento;
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
}

//Opcion 6
void MenuIndividuo::guardarDatosContribuyentes() const
{
    cout << "Guardar Datos Contribuyentes en un archivo" << endl;
}

//Opcion 7
void MenuIndividuo::cargarDatosContribuyentes() const
{
    cout<< "Cargar Datos Contribuyentes desde un archivo" << endl;
}
