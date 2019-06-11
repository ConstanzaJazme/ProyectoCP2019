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

  /* Esto es solo una de idea de como obtener las posibles soluciones del horario
  ** Se intentara simular distintos horarios sobre la disponibilidad del docente
  */
  // And for vectors
    // std::vector<int> another;  //Suponiendo que el docente tiene 22 bloques disponibles
    // another.push_back(1111);  //el ramo 1 tiene 6 bloques, por lo que se divide para cumplir con la restricción de 4 bloques maximos
    // another.push_back(2222);
    // another.push_back(11);
    // another.push_back(22);
    // another.push_back(3);
    // another.push_back(4);
    // another.push_back(00);
    // another.push_back(00);
    // another.push_back(00);
    // another.push_back(00);
    //
    //
    //
    // std::sort(another.begin(), another.end());
    // do {    //Mientras más restricciones, más certero y pequeño es el grupo
    //   if (another.at(0) < 10 && another.at(1) <10 && another.at(2) <10  && another.at(3) <100 && another.at(4) <10  && another.at(5) <100 && another.at(6) <10  && another.at(7) <10  ){
    //
    //       for(int i = 0; i < another.size(); i++) { //itera vector docente
    //           std::cout << another.at(i) <<" ";
    //       }
    //       std::cout  << '\n';
    //     }
    //
    //
    // } while (std::next_permutation(another.begin(), another.end()));  //Se hace la permutación del vector
         vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
         vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
         vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

        ordenarPorHolguraVectorDocente(vectorDocente, vectorCurso);

        // crearArchivoSalidaConNombreSheet(vectorSala);

        //cantidadFilasPorArchivo(argc, argv);

        //cantidadAsignaturasPorProfesor(argc, argv);







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
