#include <iostream>
#include <vector>
#include <xlnt/xlnt.hpp>
#include "curso.h"
#include "funciones.h"

using namespace std;
using namespace xlnt;

Curso::Curso()//constructor
{
        Codigo = "0";
        Nombre = "S.N";
        ID_Docente = "0";
        Bloques = "0";
}
Curso::Curso(string codigo, string nombre, string idDocente, string bloques)//constructor
{
        Codigo = codigo;
        Nombre = nombre;
        ID_Docente = idDocente;
        Bloques = bloques;
}
string Curso::getCodigo()
{
        return Codigo;
}
string Curso::getNombre()
{
        return Nombre;
}
string Curso::getID_Docente()
{
        return ID_Docente;
}
string Curso::getBloques()
{
        return Bloques;
}
void Curso::setCodigo(string codigo)
{
        Codigo = codigo;
}
void Curso::setNombre(string nombre)
{
        Nombre = nombre;
}
void Curso::setID_Docente(string idDocente)
{
        ID_Docente = idDocente;
}
void Curso::setBloques(string bloques)
{
        Bloques = bloques;
}
void Curso::imprimirCurso(Docente profesor)
{
        cout << "Curso: " << Codigo << " - " << Nombre << ", al mando de: "
             << profesor.getNombre() << " en " << Bloques << " bloques." << endl;
}
