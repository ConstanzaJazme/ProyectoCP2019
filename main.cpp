#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <xlnt/xlnt.hpp>
// #include <mpi.h>
#include <omp.h>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/sala.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;


int main(int argc, char *argv[])
{
        if(argc-1 == 6) {

                cout << "Cantidad de Argumentos Valida." << endl;

                xlnt::workbook cursos; //instancia de objeto que aloja el xlsx
                xlnt::workbook docentes; //instancia de objeto que aloja el xlsx
                xlnt::workbook salas; //instancia de objeto que aloja el xlsx

                /* Se verifica que el prefijo cumpla con el archivo correspondido */
                for (int i = 1; i < argc; i=i+2) {
                        char *prefijo = argv[i];

                        if(prefijo[1] == 'c') {
                                cursos.load(argv[i+1]); //carga del xlsx
                        }
                        if(prefijo[1] == 'd') {
                                docentes.load(argv[i+1]); //carga del xlsx
                        }
                        if(prefijo[1] == 's') {
                                salas.load(argv[i+1]); //carga del xlsx
                        }
                }

                cout << "XLSX Alojados." << endl;

                cout << "Cursos: " << cantidadFilasPorArchivo(cursos) << endl;
                cout << "Docentes: " << cantidadFilasPorArchivo(docentes) << endl;
                cout << "Salas: " << cantidadFilasPorArchivo(salas) << endl;

                int mi_rango; /* rango del proceso    */
                int p; /* numero de procesos   */
                int tag = 0; /* etiqueta del mensaje */

                //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                vector<Docente> vectorDocente = obtenerVectorInfoDocentes(docentes, cursos);
                //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                vector<vector<Sala> > vectorSala = obtenerVectorInfoSalas(salas);

                ordenarPorHolguraVectorDocente(vectorDocente);

                vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);

                // MPI_Init(NULL, NULL);
                // MPI_Comm_size(MPI_COMM_WORLD, &p);
                // MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
                //
                //
                //
                // int divProfesores = vectorDocente.size() / p;
                // int suma=0;
                // int diferencia = 0;
                // int numPrueba = 0;
                //
                // if (mi_rango != 0) { /* -- Esclavos -- fuentes encargadas de realizar los calculos */
                //         MPI_Recv(&diferencia, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                //
                //         if(mi_rango == p - 1) {
                //                 diferencia = vectorDocente.size() % p;
                //         }
                //
                //         asignarPorProcesador(superCubo, vectorDocente, vectorSala, mi_rango, divProfesores, diferencia);
                //
                //         numPrueba = 1;
                //         MPI_Send(&numPrueba, 2, MPI_INT, 0, tag, MPI_COMM_WORLD); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                //
                //
                //
                // } else { /* -- MASTER -- fuente encargada de distribuir los sub vectores*/
                //
                //         for (int fuente = 1; fuente < p; fuente++) {
                //                 MPI_Send(superCubo, 2, MPI_INT, fuente, tag, MPI_COMM_WORLD); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                //
                //
                //                 MPI_Recv(&numPrueba, 2, MPI_INT, fuente, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /* Envía sub vectores a todas las fuentes (exceptuando MASTER)*/
                //                 suma+=numPrueba;
                //         }
                //
                //         asignarPorProcesador(superCubo, vectorDocente, vectorSala, mi_rango, divProfesores, diferencia);
                //
                //
                //         if(suma == p-1) {
                //                 escribirResultadosEnXlsxFinal(vectorSala, superCubo);
                //         }
                // }
                //
                // MPI_Finalize();
                //

                int thread;
                  int nthreads = omp_get_max_threads();
                   omp_set_num_threads(nthreads);
                   int divProfesores = vectorDocente.size() / nthreads;
                   int diferencia=0;

                   #pragma omp parallel shared(superCubo,vectorDocente,vectorSala,divProfesores,nthreads) private(mi_rango,diferencia)
                   {
                       mi_rango = omp_get_thread_num();
                       diferencia=0;
                       if(mi_rango == nthreads-1) {
                            diferencia = (vectorDocente.size() % nthreads);
                      }

                      asignarPorProcesador(superCubo, vectorDocente, vectorSala, mi_rango, divProfesores, diferencia);


                       std::cout<<"Soy el proceso "<<mi_rango<<std::endl;


                   }
              
                                escribirResultadosEnXlsxFinal(vectorSala, superCubo);


        }


        else{
                cout << "Cantidad de Argumentos Invalida." << endl;
        }

        return 0;
}
