#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "docente.h"
#include "curso.h"
#include "sala.h"
#include <xlnt/xlnt.hpp>


using namespace std;

//================================== FUNCIONES GENERALES =====================================

//Cuenta la cantidad de filas que hay los archivos mandados por argumento.
void cantidadFilasPorArchivo(int argc, char *argv[]);

//Muestra por pantalla el contenido de las primeras N filas
//de un vector bidimensional (Filas/Columnas)
void imprimirVectorNPrimeros(vector<vector<string>> vector, int nPrimeros);

//Crea vector que contiene la info de cierta pestaña del xlsx
vector<vector<string>> crearVectorVectoresIndex(xlnt::workbook wb, int index);

//Ordena ascendentemente el vector de docentes segun su holgura
void quickSort(std::vector<Docente> &, int, int);

xlnt::border estilo_borde(xlnt::border);

void escribirDias(xlnt::worksheet, xlnt::border);

void escribirPeriodos(xlnt::worksheet, xlnt::border);

void borde_alineamiento_tam(xlnt::worksheet, xlnt::border, int, int);

//Escribe en el archivo final el resultado de hacer el horario
void escribirResultadosEnXlsxFinal(vector<vector<Sala>>, vector<vector<vector<string>>>);

//Funcion que genera un SuperCubo, el cual se recorre por sala,dia,periodo y representa el Excel de salida
vector<vector<vector<string> > > crearSuperCubo(vector<vector<Sala>> );

//Compueba si un ramo es de informatica
bool esRamoInformatica(string);

//Compueba si una sala es LAB
bool esLab(string);


//Función que retorna el mayor entre 2 numeros y la ultima posicion que tiene en un arreglo (en el formato primer digito = tamaño conjunto segundo digito posicion)
int obtenerNumMayor(int, int, int);

void asignarAsignatura(vector<vector<vector<string> > > &, int,int , Docente &, int, int);
//================================== FUNCIONES DOCENTES =====================================

//Muestra por pantalla una lista de los profesores desde un vector
void imprimeProfesores(vector<vector<string>> profes);

//Cuenta la cantidad de asignarutas de cada profesor y las muestra por pantalla
void cantidadAsignaturasPorProfesor(int argc, char *argv[]);

//Obtiene la disponibilidad total que se encuentra en el XLSX DOCENTE, convirtiendola en [PESTAÑA][FILA][COLUMNA]=[DÍA][PROFESOR][PERIODO]
vector<vector<vector<string>>> obtenerVectorInfoDisponibilidad(xlnt::workbook, int );

//Obtiene el vector de disponibilidad de un profesor en especifico y retorna la cantidad de veces que NO esta disponible
int ObtenerPesoDisponibilidad(vector<vector<int>> &,vector<vector<vector<string>>>, int, int);

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]);

//Imprime vector de Docentes
void imprimirVectorDocentes(char *argv[]);

//Funcion que recibe los vectores docente y curso y ordena el de docentes segun holgura y lo imprime
void ordenarPorHolguraVectorDocente(std::vector<Docente> &);

//Retorna la busqueda de un Docente por su ID desde un vector<Docente>
Docente buscarDocenteByID(std::string, std::vector<Docente>);

//================================== FUNCIONES CURSOS =====================================

vector <Curso> VectorVectoresAsignatura(vector< vector<string>>, string);

int bloquesReales(int);

//Retorna vector de Curso con la info del xlsx
vector<Curso> obtenerVectorInfoCursos(char *argv[]);

//Imprime vector de Docentes
void imprimirVectorCursos(char *argv[]);

//Retorna el numero de bloques totales asignados a un profesor desde vector Curso
int obtenerBloquesPorDocenteByCurso(std::vector<Curso>);

//================================== FUNCIONES SALAS =====================================

//Crea el archivo .xlsx de salida y coloca el nombre de cada pestaña segun las salas disponibles en Salas.xlsx
void crearArchivoSalidaConNombreSheet(std::vector<vector<Sala>>);

//Retorna vector de Sala con la info del xlsx
vector<vector<Sala>> obtenerVectorInfoSalas(char *argv[]);

int decisionBloquesJuntos(int);   //Se toma la decision de cuantos bloques dejar juntos



#endif // FUNCIONES_H_INCLUDED
