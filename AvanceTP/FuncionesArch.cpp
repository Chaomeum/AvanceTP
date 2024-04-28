#include "FuncionesArch.h"

char* FuncionesArch::leeCadenaExacta(ifstream& arch, char delim)
{
    char buffer[500], * cadena;
    arch.getline(buffer, 500, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy_s(cadena, strlen(buffer) + 1, buffer);
    return cadena;
}
