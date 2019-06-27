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
<<<<<<< HEAD
        //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
        vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
        // Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
        // vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);
        ordenarPorHolguraVectorDocente(vectorDocente);
        vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);
        int ramos = 0;
        for(int docente = 0; docente < vectorDocente.size(); docente++) { //Se recorren todos los profesores
                Docente profesor = vectorDocente.at(docente);
                for(int curso = 0; curso < profesor.getAsignaturas().size(); curso++) { //Se recorren todos los cursos que tiene cada profesor
                        int bloques =profesor.getAsignaturas().at(curso).getBloques();
                        string idRamo = profesor.getAsignaturas().at(curso).getCodigo();
                        int ramoColocado = 0;
                        bool ramoInformatica = esRamoInformatica(idRamo); //Se verifica si el ramo obtenido es de informatica

                        while(bloques > 0) { //Mientras el ramo aun tenga bloques sin asignar
                                bool asignar=false;
                                int salaAleatoria = rand()%vectorSala.size();
                                bool esLaboratorio = esLab(vectorSala.at(salaAleatoria).getNombre()); //Se verifica si la sala es de LAB

                                if(!ramoInformatica && !esLaboratorio) { //Si el ramo no de informatica ni la sala es de laboratorio
                                        asignar=asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo,bloques);
                                        if (asignar) bloques--;
                                }
                                if(ramoInformatica && esLaboratorio) {
                                        asignar=asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo, bloques);
                                        if (asignar) bloques--;
                                }
                        }
=======
        if(argc-1 == 3) {

                //Obtiene la información de los docente, almacenando id, nombres, apellidos, pesodisponibilidad, holgura y sus cursos en la clase DOCENTE
                vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
                //Obtiene la información de las salas, almacenando el nombre de las salas en la clase SALA
                vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
                // //Obtiene la información de los cursos, almacenando codigo, nombre y bloques en la clase CURSO
                vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

                ordenarPorHolguraVectorDocente(vectorDocente);

                vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);
                int ramos = 0;
                for(int docente = 0; docente < vectorDocente.size(); docente++) { //Se recorren todos los profesores
                        Docente profesor = vectorDocente.at(docente);
                        for(int curso = 0; curso < profesor.getAsignaturas().size(); curso++) { //Se recorren todos los cursos que tiene cada profesor
                                int bloques = profesor.getAsignaturas().at(curso).getBloques();
                                string idRamo = profesor.getAsignaturas().at(curso).getCodigo();
                                bool ramoInformatica = esRamoInformatica(idRamo); //Se verifica si el ramo obtenido es de informatica

                                while(bloques > 0) { //Mientras el ramo aun tenga bloques sin asignar
                                        int salaAleatoria = rand()%vectorSala.size();

                                        bool esLaboratorio = esLab(vectorSala.at(salaAleatoria).getNombre()); //Se verifica si la sala es de LAB

                                        if(!ramoInformatica && !esLaboratorio) { //Si el ramo no de informatica ni la sala es un lab
                                                if (asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo)) bloques--;
                                        }
                                        if(ramoInformatica && esLaboratorio) { //Si el ramo es de informatica y sala es un lab
                                                if (asignarAsignatura(superCubo,salaAleatoria,profesor,idRamo)) bloques--;
                                        }
                                }
                        }
                        profesor.imprimirDocente();
>>>>>>> a19a0b5298a0972a7bc1703b28707a577a5ab3f2
                }
                escribirResultadosEnXlsxFinal(vectorSala, superCubo);
        }
<<<<<<< HEAD
        // cout << "Ramos Totales: " << ramos << endl;
        escribirResultadosEnXlsxFinal(vectorSala, superCubo);
=======

        else{
                cout << "Cantidad de Argumentos Invalida." << endl;
        }

>>>>>>> a19a0b5298a0972a7bc1703b28707a577a5ab3f2
        return 0;
}
