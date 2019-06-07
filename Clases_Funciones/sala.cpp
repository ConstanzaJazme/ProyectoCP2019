#include <iostream>
#include <vector>
#include "sala.h"

using namespace std;

//================================== CONSTRUCTORES =====================================

Sala::Sala(){
        this->Nombre = "";
}

Sala::Sala(string nombre){
        this->Nombre = nombre;
}

//================================== METODOS SETS =====================================

void Sala::setNombre(string nombre){
        this->Nombre = nombre;
}

//================================== METODOS GETS =====================================

string Sala::getNombre(){
        return this->Nombre;
}
