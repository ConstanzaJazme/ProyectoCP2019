#ifndef CURSO_H
#define CURSO_H

//#include "docente.h"

class Curso {
    public:
        Curso();
        Curso(std::string, std::string, std::string,int);

        void setCodigo(std::string);
        void setNombre(std::string);
        void setID_Docente(std::string);
        void setBloques(int);

        std::string getCodigo();
        std::string getNombre();
        std::string getID_Docente();
        int getBloques();



    private:    
        std::string Codigo;
        std::string Nombre;
        std::string ID_Docente;
        int Bloques;
};

#endif
