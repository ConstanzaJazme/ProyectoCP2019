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

  bool correcto= argumentos(argc,argv);
          if (correcto==true) {

                  xlnt::workbook cursos; //instancia de objeto que aloja el xlsx
                  xlnt::workbook docentes; //instancia de objeto que aloja el xlsx
                  xlnt::workbook salas; //instancia de objeto que aloja el xlsx

                  cursos.load(argv[2]); //carga del xlsx
                  docentes.load(argv[4]); //carga del xlsx
                  salas.load(argv[6]); //carga del xlsx
                  //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                  vector<Docente> vectorDocente = obtenerVectorInfoDocentes(docentes, cursos);
                  //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                  vector<vector<Sala> > vectorSala = obtenerVectorInfoSalas(salas);

                  ordenarPorHolguraVectorDocente(vectorDocente);

                  vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);


                  //Se usa OpenMP para paralelizar la escritura en el superCubo

                  int thread;
                  int mi_hilo;

                  int nthreads = omp_get_max_threads();
                  omp_set_num_threads(nthreads);
                  int divProfesores = vectorDocente.size() / nthreads;
                  int diferencia=0;

                  #pragma omp parallel shared(superCubo,vectorDocente,vectorSala,divProfesores,nthreads) private(mi_hilo,diferencia)
                  {
                    mi_hilo = omp_get_thread_num();
                    diferencia=0;
                    if(mi_hilo == nthreads-1) {
                      diferencia = (vectorDocente.size() % nthreads);
                    }

                    asignarPorProcesador(superCubo, vectorDocente, vectorSala, mi_hilo, divProfesores, diferencia);




                  }

                  escribirResultadosEnXlsxFinal(vectorSala, superCubo);


    }









  return 0;
}
