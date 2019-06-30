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
// <<<<<<< HEAD
//         //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
//         vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
//         //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
//         vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
//         // Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
//         // vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);
//         ordenarPorHolguraVectorDocente(vectorDocente);
//         vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);
//         int ramos = 0;
//         for(int docente = 0; docente < vectorDocente.size(); docente++) { //Se recorren todos los profesores
//                 Docente profesor = vectorDocente.at(docente);
//                 for(int curso = 0; curso < profesor.getAsignaturas().size(); curso++) { //Se recorren todos los cursos que tiene cada profesor
//                         int bloques =profesor.getAsignaturas().at(curso).getBloques();
//                         string idRamo = profesor.getAsignaturas().at(curso).getCodigo();
//                         int ramoColocado = 0;
//                         bool ramoInformatica = esRamoInformatica(idRamo); //Se verifica si el ramo obtenido es de informatica
//
//                         while(bloques > 0) { //Mientras el ramo aun tenga bloques sin asignar
//                                 bool asignar=false;
//                                 int salaAleatoria = rand()%vectorSala.size();
//                                 bool esLaboratorio = esLab(vectorSala.at(salaAleatoria).getNombre()); //Se verifica si la sala es de LAB
//
//                                 if(!ramoInformatica && !esLaboratorio) { //Si el ramo no de informatica ni la sala es de laboratorio
//                                         asignar=asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo,bloques);
//                                         if (asignar) bloques--;
//                                 }
//                                 if(ramoInformatica && esLaboratorio) {
//                                         asignar=asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo, bloques);
//                                         if (asignar) bloques--;
//                                 }
//                         }
// =======
        if(argc-1 == 3) {

                //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
                //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
                // //Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
                //vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

                ordenarPorHolguraVectorDocente(vectorDocente);

                vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);
                int ramos = 0;
                for(int docente = 0; docente < vectorDocente.size(); docente++) { //Se recorren todos los profesores
                        Docente profesor = vectorDocente.at(docente);
                        for(int curso = 0; curso < profesor.getAsignaturas().size(); curso++) { //Se recorren todos los cursos que tiene cada profesor

                                int bucleTerminado=0;    //bucleTerminado confirma si ya se ha iterado al menos una vez por cada dia y existenciaGrupos confirma si existen disponibilidades juntas
                                bool ramoInformatica = esRamoInformatica(profesor.getAsignaturas().at(curso).getCodigo()); //Se verifica si el ramo obtenido es de informatica

                                while(profesor.getAsignaturas().at(curso).getBloques()>0) { //Mientras el ramo aun tenga bloques sin asignar
                                  std::cout << "ESTOY COMENZANDO EL WHILE " <<bucleTerminado<< '\n';

                                        int salaAleatoria = rand()%vectorSala.size();   //Se toma una sala al azar

                                        bool esLaboratorio = esLab(vectorSala.at(salaAleatoria).getNombre()); //Se verifica si la sala es de LAB
                                        std::cout << "Estoy a punto de ver en que sala" << '\n';
                                        if(!ramoInformatica && !esLaboratorio) { //Si el ramo no de informatica ni la sala es un lab
                                            std::cout << "Entre a una sala normal" << '\n';
                                                asignarAsignatura(superCubo,salaAleatoria,profesor,curso,bucleTerminado);
                                                bucleTerminado++;

                                        }
                                        else if(ramoInformatica && esLaboratorio) { //Si el ramo es de informatica y sala es un lab
                                          std::cout << "Entre a un lab" << '\n';
                                                asignarAsignatura(superCubo,salaAleatoria,profesor,curso,bucleTerminado);
                                                bucleTerminado++;


                                        }
                                }
                                std::cout << "/* TERMINE UNA ASIGNATURA el siguiente curso es  */"<< profesor.getAsignaturas().at(curso).getBloques() << '\n';
                        }
                        //profesor.imprimirDocente();
                }
                escribirResultadosEnXlsxFinal(vectorSala, superCubo);
        }


        else{
                cout << "Cantidad de Argumentos Invalida." << endl;
        }

        return 0;
}
