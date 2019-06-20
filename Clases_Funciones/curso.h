#ifndef CURSO_H
#define CURSO_H

//#include "docente.h"

class Curso {
public:
Curso();
Curso(std::string, std::string, std::string, std::string);

void setCodigo(std::string);
void setNombre(std::string);
void setID_Docente(std::string);
void setBloques(std::string);

std::string getCodigo();
std::string getNombre();
std::string getID_Docente();
std::string getBloques();

//void imprimirCurso(Docente);


private:
std::string Codigo;
std::string Nombre;
std::string ID_Docente;
std::string Bloques;
};

#endif
