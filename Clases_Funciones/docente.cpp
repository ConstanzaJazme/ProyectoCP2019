#include <iostream>
#include <vector>
#include "docente.h"

//Definir dias para poder imprimir despues cada Docente

//jajaja no me sirve

using namespace std;

Docente::Docente()//constructor
{
        ID = "0";
        Nombres = "SN";
        Apellidos = "SA";
}
Docente::Docente(string id, string nombres, string apellidos, vector<vector<int> > disponibilidad, int pesoDisponibilidad)
{
        ID = id;
        Nombres = nombres;
        Apellidos = apellidos;
        Disponibilidad = disponibilidad;
        PesoDisponibilidad = pesoDisponibilidad;
}
void Docente::setNombre(string nombre)
{
        Nombres = nombre;
}
void Docente::setApellido(string apellido)
{
        Apellidos = apellido;
}
string Docente::getNombre()
{
        return Nombres;
}
string Docente::getApellido()
{
        return Apellidos;
}
string Docente::getID()
{
        return ID;
}
void Docente::imprimirDocente()
{
        vector<string> Dias = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
        cout << "Profesor: " << ID << " - " << Nombres << " " << Apellidos << endl;
        for(int dia = 0; dia < Disponibilidad.size(); dia++) {
                cout << Dias[dia] << ": ";
                for(int disp = 0; disp < Disponibilidad.at(dia).size(); disp++) {
                        cout << Disponibilidad.at(dia).at(disp) << " ";
                }
                cout << endl;
        }
        cout << "Peso Disp: " << PesoDisponibilidad << endl;
}
