#ifndef DOCENTE_H
#define DOCENTE_H

#include "curso.h"


class Docente {
public:
Docente();
Docente(std::string, std::string, std::string, std::vector<std::vector<int> >, int, int, std::vector<Curso>);

void setID(std::string);
void setNombre(std::string);
void setApellido(std::string);
void setPesoDisponibilidad(int);
void setHolgura(int);
void setAsignaturas(std::vector<Curso>);


std::string getID();
std::string getNombre();
std::string getApellido();
int getPesoDisponibilidad();
int getHolgura();
std::vector<Curso> getAsignaturas();

void imprimirDocente();
bool estaDisponible(int, int);
void reservarHorario(int, int);


private:
std::string ID;
std::string Nombres;
std::string Apellidos;
std::vector<std::vector<int> > Disponibilidad;
int PesoDisponibilidad;
int Holgura;
std::vector<Curso> Asignaturas;
};

#endif
