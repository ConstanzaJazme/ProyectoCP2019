#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "Clases_Funciones/docente.h"

using namespace std;
using namespace xlnt;

//Cuenta la cantidad de filas que hay los archivos mandados por argumento.
void cantidadFilasPorArchivo(int argc, char *argv[]){
        if(argc > 1) { //Verifica la cantidad de argumentos a momento de ejecutar
                cout << "Cantidad de archivos ingresados: " << argc-1 << endl << endl;
                //iteracion desde el el 2° objeto (1° es nombre del .cpp)
                for(int archivos = 1; archivos < argc; archivos++) {
                        cout << "Nombre archivo: " << argv[archivos] << endl;

                        workbook xlsCursos; //instancia de objeto que aloja el xlsx
                        xlsCursos.load(argv[archivos]); //carga del xlsx
                        auto sheetCursos = xlsCursos.active_sheet(); //trabajando con la 1° pestaña del archivo

                        int contadorFilas = 0;
                        for (auto row : sheetCursos.rows(false)) //seudoForEach que recorrelas filas.
                        {
                                contadorFilas++;
                        }

                        cout << "Cantidad de filas: " << contadorFilas << endl << endl;
                }
        } else {
                cout << "No se ingresaron archivos .xlsx" << endl;
        }
}

//Muestra por pantalla el contenido de las primeras N filas
//de un vector bidimensional (Filas/Columnas)
void imprimirVectorNPrimeros(vector<vector<string> > vector, int nPrimeros){
        for (int fila = 1; fila <= nPrimeros; fila++) //Itera por fila hasta N
        {
                cout << "| ";
                for (int columna = 0; columna < vector.at(fila).size(); columna++) //itera por columna
                {
                        //Imprime lo que esta en la fila y columna indicada
                        cout << vector.at(fila).at(columna) << " | ";
                }
                cout << endl;
        }
}

//Muestra por pantalla una lista de los profesores desde un vector
void imprimeProfesores(vector<vector<string> > profes){
        for (int fila = 1; fila < profes.size(); fila++) //Itera por fila
        {
                cout << fila << ".- ";
                for (int columna = 0; columna < 3; columna++) //itera por columna
                {
                        //Imprime lo que esta en la fila y columna indicada
                        cout << profes.at(fila).at(columna) << " ";
                }
                cout << endl;
        }
}

//Crea vector que contiene la info de cierta pestaña del xlsx
vector<vector<string> > crearVectorVectoresIndex(workbook wb, int index){
        worksheet hojaActiva = wb.sheet_by_index(index);

        vector<vector<string> > vectorHojaCompleta;

        for(auto fila : hojaActiva.rows(false)) {
                vector<string> vectorFilasIndividuales;
                for (auto celda : fila)
                        vectorFilasIndividuales.push_back(celda.to_string());

                vectorHojaCompleta.push_back(vectorFilasIndividuales);
        }

        return vectorHojaCompleta;
}

//Cuenta la cantidad de asignarutas de cada profesor y las muestra por pantalla
void cantidadAsignaturasPorProfesor(int argc, char *argv[]){
        workbook xlsCursos; //instancia de objeto que aloja el xlsx
        xlsCursos.load(argv[1]); //carga del xlsx
        auto sheetCursos = xlsCursos.active_sheet(); //seleccionar 1° pestaña

        workbook xlsDocentes; //instancia de objeto que aloja el xlsx
        xlsDocentes.load(argv[2]); //carga xlsx
        auto sheetDocentes = xlsDocentes.active_sheet(); //seleccionar 1° pestaña

        vector< vector<string> > vectorCursos = crearVectorVectoresIndex(xlsCursos, 0); //Vector de vectores de los cursos
        vector< vector<string> > vectorDocentes = crearVectorVectoresIndex(xlsDocentes, 0); //Vector de vectores de los docentes


        int contador = 0;
        //Se itera los profesores que hay en el vector de vectores de profesores
        for (int profesores = 1; profesores < vectorDocentes.size(); profesores++)
        {
                int contadorAsignaturasPorProfesor = 0;
                //se itera las asignaturas que hay en el vector de vectores de asignaturas
                for (int asignaturas = 1; asignaturas < vectorCursos.size(); asignaturas++) {
                        //verificacion si el id del profesor que esta relacionado en
                        //las asignaturas concuerda con el id del profesor
                        if(vectorCursos.at(asignaturas).at(2) == vectorDocentes.at(profesores).at(0)) {
                                contadorAsignaturasPorProfesor++; //si coincide se aumenta el contador
                                contador++;
                        }
                }
                //Mostrar por pantalla el nombre del profesor y su cantidad de asignarutas
                cout << profesores << ".- " << vectorDocentes.at(profesores).at(1) << " "
                     << vectorDocentes.at(profesores).at(2) << " tiene: " <<
                        contadorAsignaturasPorProfesor << " asignaturas." << endl;

                cout << endl << contador << endl;
        }

}

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]){
        vector<Docente> vectorInfoDocentes; //Vector a devolver

        workbook xlsDocentes;
        xlsDocentes.load(argv[2]); //carga del xlsx

        //obtencion de lista de los docentes
        vector< vector<string> > vectorDocentes = crearVectorVectoresIndex(xlsDocentes, 0);

        //iteracion por docentes
        for (int profesores = 1; profesores < vectorDocentes.size(); profesores++)
        {
                cout << "..";
                vector<vector<int> > disponibleDia;
                string id = vectorDocentes.at(profesores).at(0);
                string nombres = vectorDocentes.at(profesores).at(1);
                string apellidos = vectorDocentes.at(profesores).at(2);

                //iteracion por pestañas en el xlsx
                for (int sheet = 0; sheet < xlsDocentes.sheet_count(); sheet++) {
                        //obtencion de informacion de cada pestaña
                        vector< vector<string> > vectorSheet = crearVectorVectoresIndex(xlsDocentes, sheet);
                        vector<int> dia;
                        //iteracion por info de cada pestaña
                        for (int row = 1; row < vectorSheet.size(); row++) {
                                //verificacion la info de cierto profesor corresponde al profesor del primer for
                                if(vectorSheet.at(row).at(0) == id) {
                                        dia.clear(); //se limpia vector auxiliar que guarda la disponibilidad del dia
                                        //iteracion de las ultimas filas con la info de disponibilidad
                                        for(int col = 3; col < vectorSheet.at(row).size(); col++) {
                                                if(vectorSheet.at(row).at(col) == "DISPONIBLE") {
                                                        dia.push_back(1);
                                                } else {
                                                        dia.push_back(0);
                                                }
                                        }
                                }
                        }
                        disponibleDia.push_back(dia);
                }
                //despues de que se recopila todos los datos se crea un objecto de clase Docente
                Docente nuevoProfesor(id, nombres, apellidos, disponibleDia);
                //se guarda el objeto en vector que los contenga a todos
                vectorInfoDocentes.push_back(nuevoProfesor);
        }
        system("clear");
        return vectorInfoDocentes;

}

//Imprime vector de Docentes
void imprimirVectorDocentes(char *argv[]){
        vector<Docente> allDocentes = obtenerVectorInfoDocentes(argv);
        int contador = 0;
        for(Docente info : allDocentes) {
                info.imprimirDocente();
                contador++;
        }
        cout << endl << endl << "Cantidad de profesores: " << contador << endl;
}

int main(int argc, char *argv[])
{
        cantidadFilasPorArchivo(argc, argv);
        // imprimirVectorDocentes(argv);
        return 0;
}
