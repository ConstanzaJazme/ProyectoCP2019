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

Docente::Docente(string id, string nombres, string apellidos, vector<vector<int> > disponibilidad, int pesoDisponibilidad, int holgura, vector<Curso> asignaturas){
        this->ID = id;
        this->Nombres = nombres;
        this->Apellidos = apellidos;
        this->Disponibilidad = disponibilidad;
        this->PesoDisponibilidad = pesoDisponibilidad;
        this->Holgura = holgura;
        this->Asignaturas= asignaturas;
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

void Docente::setAsignaturas(std::vector<Curso> asignaturas){
        this->Asignaturas= asignaturas;
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

vector<Curso> Docente::getAsignaturas(){
        return this->Asignaturas;
}

vector<vector<int> > Docente::getDisponibilidad(){
        return this->Disponibilidad;
}



//================================== METODOS GENERALES =====================================

void Docente::imprimirDocente(){
        vector<string> Dias = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
        cout << "Profesor: " << this->ID << " - " << this->Nombres << " " << this->Apellidos << endl;
        int pos=0;
        for(int dia = 0; dia < this->Disponibilidad.size(); dia++) {
                pos= this->Disponibilidad.at(dia).size();
                cout << Dias[dia] << ": ";
                for(int disp = 0; disp < this->Disponibilidad.at(dia).size()-2; disp++) {
                        cout << this->Disponibilidad.at(dia).at(disp) << " ";
                }
                std::cout << "Conjunto mas largo "<<  this->Disponibilidad.at(dia).at(pos-1)/10 << " de un total de "<<  this->Disponibilidad.at(dia).at(pos-2)<<  '\n';
        }

}

bool Docente::estaDisponible(int dia, int bloques){
        int posicion= this->Disponibilidad.at(dia).size()-1;  //Obtiene posicion de la info del conjunto de mayor disponibilidad en el vector dia
        if(bloques<= this->Disponibilidad.at(dia).at(posicion)/10) {
                return true;
        }
        return false;
}

int Docente::asignarBloqueAislado(int dia, int posicion_final, int largo,int curso){    //Retorna la posicion de un bloque aislado
        int fin= this->Disponibilidad.at(dia).size()-2; //Obtiene el tamaño del vector dia, variará dependiendo del dia
        int bloques=this->Asignaturas.at(curso).getBloques(); //Obtiene los bloques restantes de la asignatura
        for (int iterador=0; iterador < fin; iterador++) { //itera el día
                if(iterador == (posicion_final-largo) + 1) { //Si el iterador llega al conjunto más largo
                        // if (largo == 1) {   //Pero si es 1, ya se puede llenar ese espacio
                        //   std::cout << "iterador: "<<iterador << '\n';
                        //
                        //   return iterador;  //Se devuelve la posicion donde se asigno
                        // }
                        iterador=posicion_final; //Se saltará todas esas iteraciones

                }
                else{ //Sino se encuentra con el conjunto
                        if (this->Disponibilidad.at(dia).at(iterador)==1) { //Busca una disponibilidad
                                return iterador; //Se devuelve la posicion donde se asigno
                        }
                }
        }
}

void Docente::reservarHorario(int dia, int periodo, int curso){
        int posicion= this->Disponibilidad.at(dia).size()-1; //Obtiene posicion de la info del conjunto de mayor disponibilidad en el vector dia
        int conjunto= this->Disponibilidad.at(dia).at(posicion); //Se accede al valor del conjunto [tamaño*10 + posicion]
        int disponibilidad_total= this->Disponibilidad.at(dia).at(posicion-1); //Se accede al valor de la disponibilidad total

        int bloques=this->Asignaturas.at(curso).getBloques();
        this->Disponibilidad.at(dia).at(periodo) = 0; //Asigna el bloque
        this->Asignaturas.at(curso).setBloques(bloques-1); //Se le quita un bloque al ramo del profesor

        if (periodo > (conjunto%10-conjunto/10) && periodo<=conjunto%10) {
                this->Disponibilidad.at(dia).at(posicion)=((conjunto/10)-1)*10+(conjunto%10);
                this->Disponibilidad.at(dia).at(posicion-1)=disponibilidad_total-1;
        }
        else{
                this->Disponibilidad.at(dia).at(posicion-1)=disponibilidad_total-1;

        }
}
