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

        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);
        vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);

        ordenarPorHolguraVectorDocente(vectorDocente, vectorCurso);

        crearArchivoSalidaConNombreSheet(vectorSala);


        return 0;
}


//Datos de prueba rapida vectorDocente:

// vector<Docente> vectorDocente;
// vector<vector<int> > vectorVacio;
// Docente nuevo1("2998", "Rosa", "Cisterna", vectorVacio, 19, 0);
// Docente nuevo2("2995", "Leonardo", "Bravo", vectorVacio, 18, 0);
// Docente nuevo3("2994", "Oscar", "Magna", vectorVacio, 17, 0);
// Docente nuevo4("2993", "Ricardo", "Corbinaud", vectorVacio, 27, 0);
// vectorDocente.push_back(nuevo1);
// vectorDocente.push_back(nuevo2);
// vectorDocente.push_back(nuevo3);
// vectorDocente.push_back(nuevo4);
