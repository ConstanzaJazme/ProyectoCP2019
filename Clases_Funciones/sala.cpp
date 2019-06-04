#include <iostream>
#include <vector>
#include "sala.h"

using namespace std;

Sala::Sala()//constructor
{
        Nombre = "";
}
Sala::Sala(string nombre)
{
        Nombre = nombre;
}
void Sala::setNombre(string nombre)
{
        Nombre = nombre;
}
string Sala::getNombre()
{
        return Nombre;
}
