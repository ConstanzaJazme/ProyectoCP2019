#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;



int main(int argc, char *argv[])
{
        imprimirVectorCursos(argv);
        return 0;
}
