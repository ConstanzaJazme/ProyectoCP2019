#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <xlnt/xlnt.hpp>
#include <mpi.h>
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

                MPI_Init(NULL, NULL);
                MPI_Comm_size(MPI_COMM_WORLD, &p);
                MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);




                //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
                //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
                // //Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
                vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

                ordenarPorHolguraVectorDocente(vectorDocente);
                vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);

                int divProfesores = vectorDocente.size() / (p - 1);
                int diferencia = 0;
                vector<int> indexProfesores;
                int numPrueba = 0;

                if (mi_rango != 0) { /* -- Esclavos -- fuentes encargadas de realizar los calculos */
                        MPI_Recv(&numPrueba, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /* Se recibe un sub vector para luego calcular el sub promedio*/

                        if(mi_rango == p - 1) {
                                diferencia = vectorDocente.size() - (divProfesores * (p - 1));
                        }

                        for(int docente = (mi_rango-1) * divProfesores; docente < divProfesores * mi_rango + diferencia; docente++) { //Se recorren todos los profesores
                                Docente profesor = vectorDocente.at(docente);
                                for(int curso = 0; curso < profesor.getAsignaturas().size(); curso++) {         //Se recorren todos los cursos que tiene cada profesor
                                        int bloques = profesor.getAsignaturas().at(curso).getBloques();
                                        string idRamo = profesor.getAsignaturas().at(curso).getCodigo();
                                        bool ramoInformatica = esRamoInformatica(idRamo);         //Se verifica si el ramo obtenido es de informatica

                                        while(bloques > 0) {         //Mientras el ramo aun tenga bloques sin asignar
                                                int salaAleatoria = rand()%vectorSala.size();

                                                bool esLaboratorio = esLab(vectorSala.at(salaAleatoria).getNombre());         //Se verifica si la sala es de LAB

                                                if(!ramoInformatica && !esLaboratorio) {         //Si el ramo no de informatica ni la sala es un lab
                                                        if (asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo)) bloques--;
                                                }
                                                if(ramoInformatica && esLaboratorio) {         //Si el ramo es de informatica y sala es un lab
                                                        if (asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo)) bloques--;
                                                }
                                        }
                                }
                        }

                } else { /* -- MASTER -- fuente encargada de distribuir los sub vectores*/

                        for(int profes = 0; profes < vectorDocente.size(); profes++) {
                                indexProfesores.push_back(stoi(vectorDocente.at(profes).getID()));
                        }

                        for (int fuente = 1; fuente < p; fuente++) {
                                MPI_Send(&numPrueba, 2, MPI_INT, fuente, tag, MPI_COMM_WORLD); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                        }
                }

                MPI_Finalize();


                escribirResultadosEnXlsxFinal(vectorSala, superCubo);

        }


        else{
                cout << "Cantidad de Argumentos Invalida." << endl;
        }

        return 0;
}
