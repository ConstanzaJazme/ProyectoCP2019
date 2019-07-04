#ifndef SALA_H
#define SALA_H


class Sala {
    public:

        Sala();
        Sala(std::string);

        void setNombre(std::string);

        std::string getNombre();


    private:

        std::string Nombre;
        std::vector<std::vector<int> > Disponibilidad;
};

#endif
