#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/sala.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;



int main(int argc, char *argv[])
{
        vector<Sala> salas = obtenerVectorInfoSalas(argv);
        for(int i = 0; i < salas.size(); i++) {
                cout << salas.at(i).getNombre() << endl;
        }
        imprimirVectorDocentes(argv);

        return 0;
}
