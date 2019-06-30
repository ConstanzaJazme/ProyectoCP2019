#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <xlnt/xlnt.hpp>
// #include <mpi.h>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/sala.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;

int main(int argc, char *argv[])
{
        if(argc-1 == 3) {
                int mi_rango; /* rango del proceso    */
                int p; /* numero de procesos   */
                int tag = 0; /* etiqueta del mensaje */

                // MPI_Init(NULL, NULL);
                // MPI_Comm_size(MPI_COMM_WORLD, &p);
                // MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);




                //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
                //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
                // //Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
                //vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

                ordenarPorHolguraVectorDocente(vectorDocente);
                vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);
                //
                // int divProfesores = vectorDocente.size() / (p - 1);
                // int diferencia = 0;
                // vector<int> indexProfesores;
                // int numPrueba = 0;

                // if (mi_rango != 0) { /* -- Esclavos -- fuentes encargadas de realizar los calculos */
                //         MPI_Recv(&numPrueba, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /* Se recibe un sub vector para luego calcular el sub promedio*/
                //
                //         if(mi_rango == p - 1) {
                //                 diferencia = vectorDocente.size() - (divProfesores * (p - 1));
                //         }

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
                                 profesor.imprimirDocente();
                        }
                        escribirResultadosEnXlsxFinal(vectorSala, superCubo);


                // } else { /* -- MASTER -- fuente encargada de distribuir los sub vectores*/
                //
                //         for(int profes = 0; profes < vectorDocente.size(); profes++) {
                //                 indexProfesores.push_back(stoi(vectorDocente.at(profes).getID()));
                //         }
                //
                //         for (int fuente = 1; fuente < p; fuente++) {
                //                 MPI_Send(&numPrueba, 2, MPI_INT, fuente, tag, MPI_COMM_WORLD); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                //         }
                // }
                //
                // MPI_Finalize();



        }


        else{
                cout << "Cantidad de Argumentos Invalida." << endl;
        }

        return 0;
}
