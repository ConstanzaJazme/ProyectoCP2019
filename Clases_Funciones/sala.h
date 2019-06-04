#ifndef SALA_H
#define SALA_H


class Sala {
public:

Sala();
Sala(std::string);
std::string getNombre();
void setNombre(std::string);


private:

std::string Nombre;
std::vector<std::vector<int> > Disponibilidad;
};

#endif
