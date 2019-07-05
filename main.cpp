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
    vector<string> nombresArchivos = argumentos(argc,argv);
    bool correcto = comprobacionNombres(nombresArchivos);
    if (correcto){
            try{
                    xlnt::workbook cursos; //instancia de objeto que aloja el xlsx
                    xlnt::workbook docentes; //instancia de objeto que aloja el xlsx
                    xlnt::workbook salas; //instancia de objeto que aloja el xlsx

                    cursos.load(nombresArchivos.at(0)); //carga del xlsx
                    docentes.load(nombresArchivos.at(1)); //carga del xlsx
                    salas.load(nombresArchivos.at(2)); //carga del xlsx

                    //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                    vector<Docente> vectorDocente = obtenerVectorInfoDocentes(docentes, cursos);
                    //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                    vector<vector<Sala> > vectorSala = obtenerVectorInfoSalas(salas);

                    ordenarPorHolguraVectorDocente(vectorDocente); //Orden de los profesores

                    vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala); //vector de salida, contendra toda la informacion


                    //Se usa OpenMP para paralelizar la escritura en el superCubo
                    // int thread;

                    int mi_hilo; //inicializacion variable para diferenciar hilo mientra se paraleliza

                    int nthreads = omp_get_max_threads(); //Se obtiene la cantidad maxima de hilos disponibles
                    omp_set_num_threads(nthreads); //Setea la cantidad de hilos a usar
                    int divProfesores = vectorDocente.size() / nthreads; //Tamaño grupos a repartir
                    int diferencia=0;

                    #pragma omp parallel shared(superCubo,vectorDocente,vectorSala,divProfesores,nthreads) private(mi_hilo,diferencia) //Ejecucion de cada hilo
                    {
                            mi_hilo = omp_get_thread_num(); //Numero del hilo
                            diferencia=0;
                            if(mi_hilo == nthreads-1) {
                                    diferencia = (vectorDocente.size() % nthreads); //Si es el ultimo hilo, se le agrega la diferencia al ultimo profesor en el vector
                            }
                            asignarPorProcesador(superCubo, vectorDocente, vectorSala, mi_hilo, divProfesores, diferencia); //Asignar ramo por hilo
                    }

                    escribirResultadosEnXlsxFinal(vectorSala, superCubo); //Escribir resultados en archivo final
            }catch(std::exception& e){
                    cout << "ERROR! Revise que los nombres de los archivos esten acompañados a su izquierda por su etiqueta correspondiente." << endl;
            }
    }else{
        cout << "ERROR! Revise los nombres de los archivos ingresados." << endl;
    }
    return 0;
}
