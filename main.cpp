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

vector<vector<string> > obtenerCursosPorDocente(vector<Curso> vectorCurso, string docente){
        vector<vector<string> > cursosPorDocente;
        for(int curso = 0; curso < vectorCurso.size(); curso++) {
                if(vectorCurso.at(curso).getID_Docente() == docente) {
                        vector<string> infoCurso;
                        infoCurso.push_back(vectorCurso.at(curso).getCodigo());
                        infoCurso.push_back(vectorCurso.at(curso).getBloques());
                        cursosPorDocente.push_back(infoCurso);
                }
        }
        return cursosPorDocente;
}

vector<vector<vector<string> > > crearSuperCubo(int cantidadSalas){
        vector<vector<vector<string> > > superCubo;

        for(int salas = 0; salas < cantidadSalas; salas++) {
                vector<vector<string> > horarioDia;

                for(int dias = 0; dias < 6; dias++) {
                        vector<string> horarioPeriodo;
                        int maxPeriodos = 7;
                        if(dias == 5) maxPeriodos = 4;
                        for(int periodos = 0; periodos < maxPeriodos; periodos++) {
                                horarioPeriodo.push_back("0");
                        }
                        horarioDia.push_back(horarioPeriodo);
                }
                superCubo.push_back(horarioDia);
        }

        return superCubo;
}


int main(int argc, char *argv[])
{
        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
        vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);
        crearArchivoSalidaConNombreSheet2(vectorSala);

//         ordenarPorHolguraVectorDocente(vectorDocente, vectorCurso);
//
//         vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala.size());
//
//         int ramos = 0;
//
//         for(int docente = 0; docente < vectorDocente.size(); docente++) {
//                 vector<vector<string> > cursosDocente = obtenerCursosPorDocente(vectorCurso, vectorDocente.at(docente).getID());
//                 for(int curso = 0; curso < cursosDocente.size(); curso++) {
//
//                         int bloques = stoi(cursosDocente.at(curso).at(1));
//                         string idRamo = cursosDocente.at(curso).at(0);
//                         int ramoColocado = 0;
//                         Docente profesor = vectorDocente.at(docente);
//
//                         while(bloques > 0) {
//                                 for(int salas = 0; salas < superCubo.size(); salas++) {
//                                         for(int dias = 0; dias < superCubo.at(salas).size(); dias++) {
//                                                 for(int periodos = 0; periodos < superCubo.at(salas).at(dias).size(); periodos++) {
//                                                         if(superCubo.at(salas).at(dias).at(periodos) == "0" && profesor.estaDisponible(dias, periodos)) {
//                                                                 superCubo.at(salas).at(dias).at(periodos) = idRamo + " - " + vectorDocente.at(docente).getID();
//                                                                 ramoColocado++;
//                                                                 goto Encontrado;
//                                                         }
//                                                 }
//                                         }
//                                 }
// Encontrado:
//                                 bloques -= 1;
//                                 // cout << bloques<< endl;
//
//                         }
//                         ramos++;
//
//                 }
//                 // cout << docente << endl;
//         }
//         // cout << "Ramos Totales: " << ramos << endl;
//         escribirResultadosEnXlsxFinal(vectorSala, superCubo);







        return 0;
}

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
