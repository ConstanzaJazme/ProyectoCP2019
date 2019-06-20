#ifndef DOCENTE_H
#define DOCENTE_H

class Docente {
public:
Docente();
Docente(std::string, std::string, std::string, std::vector<std::vector<int> >, int, int);

void setID(std::string);
void setNombre(std::string);
void setApellido(std::string);
void setPesoDisponibilidad(int);
void setHolgura(int);

std::string getID();
std::string getNombre();
std::string getApellido();
int getPesoDisponibilidad();
int getHolgura();

void imprimirDocente();
bool estaDisponible(int, int);


private:
std::string ID;
std::string Nombres;
std::string Apellidos;
std::vector<std::vector<int> > Disponibilidad;
int PesoDisponibilidad;
int Holgura;
};

#endif
