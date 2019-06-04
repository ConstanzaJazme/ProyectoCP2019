#ifndef DOCENTE_H
#define DOCENTE_H

class Docente {
public:
Docente();
Docente(std::string, std::string, std::string, std::vector<std::vector<int> >, int);
void setNombre(std::string);
void setApellido(std::string);
std::string getNombre();
std::string getID();
std::string getApellido();
void imprimirDocente();


private:
std::string ID;
std::string Nombres;
std::string Apellidos;
std::vector<std::vector<int> > Disponibilidad;
int PesoDisponibilidad;
};

#endif
