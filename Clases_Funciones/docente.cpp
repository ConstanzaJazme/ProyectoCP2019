#include <iostream>
#include <vector>
#include "docente.h"
#include "funciones.h"

using namespace std;

//================================== CONSTRUCTORES =====================================

Docente::Docente(){
        this->ID = "0";
        this->Nombres = "SN";
        this->Apellidos = "SA";
        this->PesoDisponibilidad = 0;   //Indica quien tiene mayor prioridad a la hora de elegir el horario, bajo el criterio de que quien tenga menos disponibilidad es el que mayor peso tendrá (CUENTA NO DISPONIBLES)
        this->Holgura = 0;    //Indica la diferencia entre bloques totales disponibles y bloques que necesita para hacer clases
}

Docente::Docente(string id, string nombres, string apellidos, vector<vector<int> > disponibilidad, int pesoDisponibilidad, int holgura){
        this->ID = id;
        this->Nombres = nombres;
        this->Apellidos = apellidos;
        this->Disponibilidad = disponibilidad;
        this->PesoDisponibilidad = pesoDisponibilidad;
        this->Holgura = holgura;
}

//================================== METODOS SETS =====================================

void Docente::setID(string id){
        this->ID = id;
}

void Docente::setNombre(string nombre){
        this->Nombres = nombre;
}

void Docente::setApellido(string apellido){
        this->Apellidos = apellido;
}

void Docente::setPesoDisponibilidad(int pesoDisponibilidad){
        this->PesoDisponibilidad = pesoDisponibilidad;
}

void Docente::setHolgura(int holgura){
        this->Holgura = holgura;
}

//================================== METODOS GETS =====================================

string Docente::getID(){
        return this->ID;
}

string Docente::getNombre(){
        return this->Nombres;
}

string Docente::getApellido(){
        return this->Apellidos;
}

int Docente::getPesoDisponibilidad(){
        return this->PesoDisponibilidad;
}

int Docente::getHolgura(){
        return this->Holgura;
}


//================================== METODOS GENERALES =====================================

void Docente::imprimirDocente(){
        vector<string> Dias = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

        cout << "Profesor: " << this->ID << " - " << this->Nombres << " " << this->Apellidos << endl;

        for(int dia = 0; dia < this->Disponibilidad.size(); dia++) {
                cout << Dias[dia] << ": ";
                for(int disp = 0; disp < this->Disponibilidad.at(dia).size(); disp++) {
                        cout << this->Disponibilidad.at(dia).at(disp) << " ";
                }
                cout << endl;
        }

}

bool Docente::estaDisponible(int dia, int periodo){
        if(this->Disponibilidad.at(dia).at(periodo) == 1) {
                return true;
        }
        return false;
}
