#include <iostream>
#include <vector>
#include <xlnt/xlnt.hpp>
#include "curso.h"
#include "funciones.h"

using namespace std;
using namespace xlnt;

//================================== CONSTRUCTORES =====================================

Curso::Curso(){
        this->Codigo = "0";
        this->Nombre = "S.N";
        this->ID_Docente = "0";
        this->Bloques = 0;
}

Curso::Curso(string codigo, string nombre, string idDocente, int bloques){
        this->Codigo = codigo;
        this->Nombre = nombre;
        this->ID_Docente = idDocente;
        this->Bloques = bloques;
}

//================================== METODOS SETS =====================================

void Curso::setCodigo(string codigo){
        this->Codigo = codigo;
}

void Curso::setNombre(string nombre){
        this->Nombre = nombre;
}

void Curso::setID_Docente(string idDocente){
        this->ID_Docente = idDocente;
}

void Curso::setBloques(int bloques){
        this->Bloques = bloques;
}

//================================== METODOS GETS =====================================

string Curso::getCodigo(){
        return this->Codigo;
}

string Curso::getNombre(){
        return this->Nombre;
}

string Curso::getID_Docente(){
        return this->ID_Docente;
}

int Curso::getBloques(){
        return this->Bloques;
}

//================================== METODOS GENERALES =====================================

// void Curso::imprimirCurso(Docente profesor){
//         cout << "Curso: " << this->Codigo << " - " << this->Nombre << ", al mando de: "
//              << profesor.getNombre() << " en " << this->Bloques << " bloques." << endl;
// }
