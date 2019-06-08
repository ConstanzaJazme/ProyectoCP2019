#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <xlnt/xlnt.hpp>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/sala.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;




int main(int argc, char *argv[])
{
        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
        vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);


        // ordenarPorHolguraVectorDocente(vectorDocente, vectorCurso);

        // crearArchivoSalidaConNombreSheet(vectorSala);

        // cantidadFilasPorArchivo(argc, argv);

        // cantidadAsignaturasPorProfesor(argc, argv);







        return 0;
}


//================== Datos de prueba rapida vectorDocente ======================

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


//============== Datos prueba imprimir resultado final en xlsx =================

// vector<vector<vector<string> > > superCubo;
//
// for(int salas = 0; salas < 41; salas++) {
//         vector<vector<string> > horarioDia;
//
//         for(int dias = 0; dias < 6; dias++) {
//                 vector<string> horarioPeriodo;
//                 int maxPeriodos = 7;
//                 if(dias == 5) maxPeriodos = 4;
//                 for(int periodos = 0; periodos < maxPeriodos; periodos++) {
//                         Curso curso = vectorCurso.at(rand()%vectorCurso.size());
//                         string cursoProfesor = curso.getCodigo() + " - " + curso.getID_Docente();
//                         horarioPeriodo.push_back(cursoProfesor);
//                 }
//                 horarioDia.push_back(horarioPeriodo);
//         }
//         superCubo.push_back(horarioDia);
// }
//
// escribirResultadosEnXlsxFinal(vectorSala, superCubo);
