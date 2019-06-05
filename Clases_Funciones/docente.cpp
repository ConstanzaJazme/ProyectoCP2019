#include <iostream>
#include <vector>
#include "docente.h"
#include "funciones.h"

using namespace std;

Docente::Docente()//constructor
{
        ID = "0";
        Nombres = "SN";
        Apellidos = "SA";
        PesoDisponibilidad = 0;
        Holgura = 0;
}
Docente::Docente(string id, string nombres, string apellidos, vector<vector<int> > disponibilidad, int pesoDisponibilidad)
{
        ID = id;
        Nombres = nombres;
        Apellidos = apellidos;
        Disponibilidad = disponibilidad;
        PesoDisponibilidad = pesoDisponibilidad;
        Holgura = 0;
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
        cout << "Holgura" << 39-PesoDisponibilidad << endl;

}
int Docente::getPesoDisponibilidad()
{
        return PesoDisponibilidad;
}
void Docente::setHolgura(int holgura)
{
        Holgura = holgura;
}
int Docente::getHolgura()
{
        return Holgura;
}
