#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "funciones.h"

using namespace std;

//Cuenta la cantidad de filas que hay los archivos mandados por argumento.
void cantidadFilasPorArchivo(int argc, char *argv[]){
        if(argc > 1) { //Verifica la cantidad de argumentos a momento de ejecutar
                cout << "Cantidad de archivos ingresados: " << argc-1 << endl << endl;
                //iteracion desde el el 2° objeto (1° es nombre del .cpp)
                for(int archivos = 1; archivos < argc; archivos++) {
                        cout << "Nombre archivo: " << argv[archivos] << endl;

                        xlnt::workbook xlsCursos; //instancia de objeto que aloja el xlsx
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
vector<vector<string> > crearVectorVectoresIndex(xlnt::workbook wb, int index){
        xlnt::worksheet hojaActiva = wb.sheet_by_index(index);

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
        xlnt::workbook xlsCursos; //instancia de objeto que aloja el xlsx
        xlsCursos.load(argv[1]); //carga del xlsx
        auto sheetCursos = xlsCursos.active_sheet(); //seleccionar 1° pestaña

        xlnt::workbook xlsDocentes; //instancia de objeto que aloja el xlsx
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

        }
        cout << endl << "Cantidad total de Cursos: " << contador << endl;

}

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]){
        vector<Docente> vectorInfoDocentes; //Vector a devolver

        xlnt::workbook xlsDocentes;
        xlsDocentes.load(argv[2]); //carga del xlsx

        //obtencion de lista de los docentes
        vector< vector<string> > vectorDocentes = crearVectorVectoresIndex(xlsDocentes, 0);

        //iteracion por docentes
        for (int profesores = 1; profesores < vectorDocentes.size(); profesores++)
        {
                vector<vector<int> > disponibleDia;
                string id = vectorDocentes.at(profesores).at(0);
                string nombres = vectorDocentes.at(profesores).at(1);
                string apellidos = vectorDocentes.at(profesores).at(2);
                int pesoDisponibilidad = 0;

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
                                                        pesoDisponibilidad++;
                                                }
                                        }
                                }
                        }
                        disponibleDia.push_back(dia);
                }
                //despues de que se recopila todos los datos se crea un objecto de clase Docente
                Docente nuevoProfesor(id, nombres, apellidos, disponibleDia, pesoDisponibilidad, 0);
                //se guarda el objeto en vector que los contenga a todos
                vectorInfoDocentes.push_back(nuevoProfesor);
        }

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

vector<Curso> obtenerVectorInfoCursos(char *argv[]){
        vector<Curso> vectorInfoCurso; //Vector a devolver

        xlnt::workbook xlsCurso;
        xlsCurso.load(argv[1]); //carga del xlsx

        //obtencion de lista de los docentes
        vector< vector<string> > vectorCurso = crearVectorVectoresIndex(xlsCurso, 0);

        //iteracion por curso
        for (int curso = 1; curso < vectorCurso.size(); curso++)
        {
                string codigo = vectorCurso.at(curso).at(0);
                string nombre = vectorCurso.at(curso).at(1);
                string idDocente = vectorCurso.at(curso).at(2);
                string bloques = vectorCurso.at(curso).at(5);

                Curso nuevoCurso(codigo, nombre, idDocente, bloques);
                vectorInfoCurso.push_back(nuevoCurso);

        }
        return vectorInfoCurso;

}

Docente buscarDocenteByID(string id, vector<Docente> vector){
        for(Docente profesor : vector) { //itera por los docentes en el vector
                if(profesor.getID() == id) { //comprueba los ID
                        return profesor; //si lo encuentra, lo retorna
                }
        }
        Docente nuevo; //Objeto vacio para retornar
        return nuevo;
}

int obtenerBloquesPorDocenteByCurso(string id, vector<Curso> vector){
        int holgura = 0;
        for(Curso c : vector) { //itera el vector
                if(c.getID_Docente() == id) { //verifica si tienen el mismo ID
                        holgura += stoi(c.getBloques()); //si son iguales, suma su holgura
                }
        }
        return holgura;
}

//Imprime vector de Docentes
void imprimirVectorCursos(char *argv[]){
        vector<Curso> allCursos = obtenerVectorInfoCursos(argv);
        vector<Docente> allDocentes = obtenerVectorInfoDocentes(argv);
        int contador = 0;
        for(Curso info : allCursos) {
                info.imprimirCurso(buscarDocenteByID(info.getID_Docente(), allDocentes));
                contador++;
        }
        cout << endl << endl << "Cantidad de Cursos: " << contador << endl;
}

vector<Sala> obtenerVectorInfoSalas(char *argv[]){
        vector<Sala> vectorInfoSala; //Vector a devolver

        xlnt::workbook xlsxSala;
        xlsxSala.load(argv[3]); //carga del xlsx

        //obtencion de lista de las salas
        vector< vector<string> > vectorSala = crearVectorVectoresIndex(xlsxSala, 0);

        //iteracion por sala
        for (int sala = 1; sala < vectorSala.size(); sala++)
        {
                string Edificio = vectorSala.at(sala).at(0);
                string numeroSala = vectorSala.at(sala).at(1);
                string nombreSala = Edificio + "-" + numeroSala;

                Sala nuevoSala(nombreSala);
                vectorInfoSala.push_back(nuevoSala);

        }
        return vectorInfoSala;
}
void quickSort(vector<Docente> &numeros, int limite_izq, int limite_der){
        int pivote = numeros.at((limite_izq + limite_der)/2).getHolgura();
        int i = limite_izq;
        int j = limite_der;
        Docente aux;


        while(i<=j) {
                while(numeros.at(i).getHolgura() < pivote)
                        i++;
                while(numeros.at(j).getHolgura() > pivote)
                        j--;

                if(i <= j) {

                        aux = numeros.at(i);
                        numeros.at(i) = numeros.at(j);
                        numeros.at(j) = aux;
                        i++;
                        j--;
                }
        }

        if(limite_izq < j) {
                quickSort(numeros, limite_izq, j);
        }

        if(i < limite_der) {
                quickSort(numeros, i, limite_der);
        }
}

void ordenarPorHolguraVectorDocente(vector<Docente> vectorDocente, vector<Curso> vectorCurso){
        for(int i = 0; i < vectorDocente.size(); i++) { //itera vector docente
                //calcula disponibilidad restando 39 (7 bloques * 5 diasSemana + 4 bloques dia sabado)
                //menos lo obtenido en el objeto docente ya calculado
                int disponibilidadReal = 39-vectorDocente.at(i).getPesoDisponibilidad(); //39: disponibilidad todos los bloques en una semana

                //Se busca lo que realmente se necesita en bloques para cada profesor
                int disponibilidadEsperada = obtenerBloquesPorDocenteByCurso(vectorDocente.at(i).getID(), vectorCurso);


                int holgura = disponibilidadReal - disponibilidadEsperada;
                vectorDocente.at(i).setHolgura(holgura);//Se cambia atributo Holgura en cada objeto por lo obtenido
        }
        quickSort(vectorDocente, 0, vectorDocente.size()-1); //se ordena ascendentemente por holgura

        for(Docente profe : vectorDocente) { //Muestra por pantalla
                cout << profe.getNombre() << " " << profe.getApellido() << " /Holgura: " << profe.getHolgura() << endl;
        }
}

void crearArchivoSalidaConNombreSheet(vector<Sala> vectorSala){
        //creacion de archivo Start
        xlnt::workbook wbOut;
        string dest_filename = "salida.xlsx";

        for(int i = 0; i < 17; i++) { //17 primeras sheets
                wbOut.create_sheet();
        }
        wbOut.save(dest_filename);

        //se abre nuevamente ya que da un error y se crean las siguiente 13 sheets
        xlnt::workbook resultado;
        resultado.load(dest_filename);
        for(int i = 0; i < 13; i++) {
                resultado.create_sheet();
        }
        resultado.save(dest_filename);

        //se crean las ultimas 10 sheets antes que lanze el error de core.
        xlnt::workbook resultado2;
        resultado2.load(dest_filename);
        for(int i = 0; i < 10; i++) {
                resultado2.create_sheet();
        }
        resultado2.save(dest_filename);

        //Terminar creacion de archivo END

        //Colocar nombres pestañas
        xlnt::workbook salida;
        salida.load(dest_filename);

        for(int sala = 0; sala < vectorSala.size(); sala++) {
                xlnt::worksheet hojaActiva = salida.sheet_by_index(sala);
                string nombreSala = vectorSala.at(sala).getNombre();
                hojaActiva.title(nombreSala);
        }


        salida.save(dest_filename);

}
