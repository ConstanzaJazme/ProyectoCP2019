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
int getPesoDisponibilidad();
void imprimirDocente();
void setHolgura(int);
int getHolgura();


private:
std::string ID;
std::string Nombres;
std::string Apellidos;
std::vector<std::vector<int> > Disponibilidad;
int PesoDisponibilidad;
int Holgura;
};

#endif
