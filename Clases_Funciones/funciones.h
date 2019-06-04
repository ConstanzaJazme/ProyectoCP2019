#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "docente.h"
#include "curso.h"
#include "sala.h"

using namespace std;
using namespace xlnt;

//Cuenta la cantidad de filas que hay los archivos mandados por argumento.
void cantidadFilasPorArchivo(int argc, char *argv[]);

//Muestra por pantalla el contenido de las primeras N filas
//de un vector bidimensional (Filas/Columnas)
void imprimirVectorNPrimeros(vector<vector<string>> vector, int nPrimeros);

//Muestra por pantalla una lista de los profesores desde un vector
void imprimeProfesores(vector<vector<string>> profes);

//Crea vector que contiene la info de cierta pestaña del xlsx
vector<vector<string>> crearVectorVectoresIndex(workbook wb, int index);

//Cuenta la cantidad de asignarutas de cada profesor y las muestra por pantalla
void cantidadAsignaturasPorProfesor(int argc, char *argv[]);

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]);

//Imprime vector de Docentes
void imprimirVectorDocentes(char *argv[]);

//Retorna vector de Curso con la info del xlsx
vector<Curso> obtenerVectorInfoCursos(char *argv[]);

//Imprime vector de Docentes
void imprimirVectorCursos(char *argv[]);

Docente buscarDocenteByID(std::string, std::vector<Docente>);

//Retorna vector de Sala con la info del xlsx
vector<Sala> obtenerVectorInfoSalas(char *argv[]);

#endif // FUNCIONES_H_INCLUDED
