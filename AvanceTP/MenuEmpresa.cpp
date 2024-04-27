#include "MenuEmpresa.h"

void MenuEmpresa::mostrarMenu() const
{
    cout << "===== MENU EMPRESA =====" << endl;
    cout << "1.- Agregar un nuevo contribuyente." << endl;
    cout << "2.- Calcular impuestos para un contribuyente." << endl;
    cout << "3.- Generar reporte de impuestos." << endl;
    cout << "4.- Ver lista de contribuyentes." << endl;
    cout << "5.- Ordenar contribuyentes por algún criterio." << endl;
    cout << "6.- Guardar datos en archivo." << endl;
    cout << "7.- Cargar datos desde archivo." << endl;
    cout << "8.- Salir del programa." << endl;
}