#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class FuncionesArch
{
public:
	char* leeCadenaExacta(ifstream & arch, char delim);
	void imprimeSimbolo(int n, char car);
};

