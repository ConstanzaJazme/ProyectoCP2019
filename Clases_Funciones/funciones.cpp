#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "funciones.h"

using namespace std;

//================================== FUNCIONES GENERALES =====================================

//Cuenta la cantidad de filas que hay en los archivos mandados por argumento.
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

//Ordena ascendentemente el vector de docentes segun su holgura
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

xlnt::border estilo_borde(xlnt::border border){    //Función para los estilos en el Excel
        xlnt::border::border_property border_property;
        border_property.style(xlnt::border_style::thin);
        border.side(xlnt::border_side::start, border_property); // left
        border.side(xlnt::border_side::end, border_property); // right
        border.side(xlnt::border_side::top, border_property); // top
        border.side(xlnt::border_side::bottom, border_property); // bottom
        return border;
}

void escribirDias(xlnt::worksheet hoja, xlnt::border border){
        vector<string> DiasSemana = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
        for (int i = 0; i < DiasSemana.size(); i++) {
                hoja.cell(xlnt::cell_reference(i + 3, 1)).value(DiasSemana.at(i));
                hoja.cell(xlnt::cell_reference(i + 3, 1)).border(border);
                hoja.cell(xlnt::cell_reference(i + 3, 1)).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
        }
}

void escribirPeriodos(xlnt::worksheet hoja, xlnt::border border){
        vector<string> Horas = {"8:00 – 9:30", "9:40 – 11:10", "11:20 – 12:50", "13:00 – 14:30", "14:40 – 16:10", "16:20 – 17:50", "18:00 – 19:30"};
        for (int i = 0; i < Horas.size(); i++) {
                hoja.cell(xlnt::cell_reference(1, i+2)).value(Horas.at(i));
                hoja.cell(xlnt::cell_reference(1, i+2)).border(border);
                hoja.cell(xlnt::cell_reference(1, i+2)).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));

                hoja.cell(xlnt::cell_reference(2, i+2)).value(i + 1);
                hoja.cell(xlnt::cell_reference(2, i+2)).border(border);
                hoja.cell(xlnt::cell_reference(2, i+2)).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
        }
}

void borde_alineamiento_tam(xlnt::worksheet hoja, xlnt::border border, int dia, int periodo){   //Configura celdas de tal forma que se vean bien
        // Bordes
        hoja.cell(xlnt::cell_reference(dia + 3, periodo + 2)).border(border);

        // Alineamiento
        hoja.cell(xlnt::cell_reference(dia + 3, periodo + 2)).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));

        // Tamaño de celda
        hoja.column_properties(1).width = 12.0;
        hoja.column_properties(2).width = 3.0;
        for(int i = 0; i < 6; i++) { //ancho
                hoja.column_properties(i+3).width = 16.0;
        }
        for(int i = 1; i < 9; i++) { //alto
                hoja.row_properties(i).height = 16.0;
        }
}

//Escribe en el archivo final el resultado de hacer el horario
void escribirResultadosEnXlsxFinal(vector<Sala> vectorSala, vector<vector<vector<string> > > superCubo){
        crearArchivoSalidaConNombreSheet(vectorSala); //Se crea archivo de salida
        xlnt::border border;
        xlnt::workbook salida;
        border=estilo_borde(border);
        salida.load("salida.xlsx"); //Se carga el archivo de salida de resultados
        for(int sala = 0; sala < superCubo.size(); sala++) {
                for(int dia = 0; dia < superCubo.at(sala).size(); dia++) {
                        for(int periodo = 0; periodo < superCubo.at(sala).at(dia).size(); periodo++) {
                                //Se selecciona la hoja correspondiente
                                xlnt::worksheet hojaActiva = salida.sheet_by_title(vectorSala.at(sala).getNombre());
                                //Se escribe el horario dependiendo de lo que haya el vector de resultados
                                hojaActiva.cell(xlnt::cell_reference(dia + 3, periodo + 2)).value(superCubo.at(sala).at(dia).at(periodo));

                                borde_alineamiento_tam(hojaActiva,border,dia,periodo);
                        }
                }
        }
        salida.save("salida.xlsx"); //Se guardan resultados
}

//Funcion que inicializa un SuperCubo, el cual se recorre por sala,dia,periodo y representa el Excel de salida
vector<vector<vector<string> > > crearSuperCubo(vector<Sala> vectorSala){
        vector<vector<vector<string> > > superCubo;
        for(int salas = 0; salas < vectorSala.size(); salas++) {
                vector<vector<string> > horarioDia;
                for(int dias = 0; dias < 6; dias++) {
                        vector<string> horarioPeriodo;
                        int maxPeriodos = 7;
                        if(dias == 5) maxPeriodos = 4;
                        for(int periodos = 0; periodos < maxPeriodos; periodos++) {
                                horarioPeriodo.push_back("*" + vectorSala.at(salas).getNombre());
                        }
                        horarioDia.push_back(horarioPeriodo);
                }
                superCubo.push_back(horarioDia);
        }
        return superCubo;
}

//Compueba si un ramo es de informatica
bool esRamoInformatica(string ramo){
        if(ramo[0] == 'I' && ramo[1] == 'N' && ramo[2] == 'F') return true;
        return false;
}

//Compueba si una sala es LAB
bool esLab(string sala){
        string nombreSala = sala.substr(0,3);
        if(nombreSala == "LAB") {
                return true;
        }
        return false;
}

bool asignarAsignatura(vector<vector<vector<string> > > &superCubo, int salas, Docente profesor, string idRamo){
        for(int dias = 0; dias < superCubo.at(salas).size(); dias++) {
                for(int periodos = 0; periodos < superCubo.at(salas).at(dias).size(); periodos++) {
                        if(superCubo.at(salas).at(dias).at(periodos)[0] == '*' && profesor.estaDisponible(dias, periodos)) {
                                superCubo.at(salas).at(dias).at(periodos) = idRamo + " - " + profesor.getID();
                                return true;
                        }
                }
        }
        return false;
}
//================================== FUNCIONES DOCENTES =====================================

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

//Retorna un vector de la clase CURSO, el cual contiene todos los cursos de un profesor
vector <Curso> VectorVectoresAsignatura(vector< vector<string> > vectorCursos, string id_docente){
        vector <Curso> CursosxDocente;
        //se itera las asignaturas que hay en el vector de vectores de asignaturas
        for (int asignaturas = 1; asignaturas < vectorCursos.size(); asignaturas++) {
                //verificacion si el id del profesor que esta relacionado en
                //las asignaturas concuerda con el id del profesor
                if(vectorCursos.at(asignaturas).at(2) == id_docente) {
                        string codigo = vectorCursos.at(asignaturas).at(0);
                        string nombre = vectorCursos.at(asignaturas).at(1);
                        string idDocente = vectorCursos.at(asignaturas).at(2);
                        int bloques_pedagogicos = stoi(vectorCursos.at(asignaturas).at(5));
                        int bloques= bloquesReales(bloques_pedagogicos);
                        Curso nuevoCurso(codigo, nombre, idDocente, bloques);
                        CursosxDocente.push_back(nuevoCurso);
                }
        }
        return CursosxDocente;
}

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]){
        vector<Docente> vectorInfoDocentes; //Vector a devolver
        vector<vector<vector<string> > > vectorInfoDias; //Vector que contiene vector de vectores por día

        xlnt::workbook xlsDocentes;
        xlsDocentes.load(argv[2]); //carga del xlsx

        xlnt::workbook xlsCursos; //instancia de objeto que aloja el xlsx
        xlsCursos.load(argv[1]); //carga del xlsx

        vector< vector<string> > CursosDocente = crearVectorVectoresIndex(xlsCursos, 0); //Vector de vectores de los cursos

        int cantidad_hojas= xlsDocentes.sheet_count();

        //iteracion por pestañas en el xlsx
        for (int sheet = 0; sheet < cantidad_hojas; sheet++) {
                //obtencion de informacion de cada pestaña
                vector< vector<string> > vectorSheet = crearVectorVectoresIndex(xlsDocentes, sheet);
                vectorInfoDias.push_back(vectorSheet);
        }

        //Iteración por profesor
        for (int profesores = 1; profesores < vectorInfoDias.at(0).size(); profesores++) {
                vector<vector<int> > disponibleDia;
                vector <Curso> asignaturas;

                string id = vectorInfoDias.at(0).at(profesores).at(0); //OJO, como la información de los profesores se repite en todas las hojas, se sca solo de la inicial.
                string nombres =  vectorInfoDias.at(0).at(profesores).at(1);
                string apellidos = vectorInfoDias.at(0).at(profesores).at(2);
                int pesoDisponibilidad = 0;

                //Se Itera por días
                for (int dias = 0; dias < cantidad_hojas; dias++) {

                        vector<int> dia_x; //Vector que almacena la disponibilidad por día de un profesor

                        //Se itera por columnnas
                        for(int col = 3; col < vectorInfoDias.at(dias).at(profesores).size(); col++) {
                                if(vectorInfoDias.at(dias).at(profesores).at(col) == "DISPONIBLE") {
                                        dia_x.push_back(1);
                                } else {
                                        dia_x.push_back(0);
                                        pesoDisponibilidad++;
                                }
                        }
                        disponibleDia.push_back(dia_x);
                        dia_x.clear(); //se limpia vector auxiliar que guarda la disponibilidad del dia
                }

                asignaturas=VectorVectoresAsignatura(CursosDocente, id);

                //despues de que se recopila todos los datos se crea un objecto de clase Docente
                Docente nuevoProfesor(id, nombres, apellidos, disponibleDia, pesoDisponibilidad, 0,asignaturas);
                //se guarda el objeto en vector que los contenga a todos
                vectorInfoDocentes.push_back(nuevoProfesor);
                //nuevoProfesor.imprimirDocente();

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

//Funcion que recibe los vectores docente y curso y ordena el de docentes segun holgura y lo imprime
void ordenarPorHolguraVectorDocente(vector<Docente> &vectorDocente, vector<Curso> vectorCurso){
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

        // for(Docente profe : vectorDocente) { //Muestra por pantalla
        //         cout << profe.getNombre() << " " << profe.getApellido() << " /Holgura: " << profe.getHolgura() <<" Disponibilidad: "<<39- profe.getPesoDisponibilidad()<<endl;
        // }
}

//Retorna la busqueda de un Docente por su ID desde un vector<Docente>
Docente buscarDocenteByID(string id, vector<Docente> vector){
        for(Docente profesor : vector) { //itera por los docentes en el vector
                if(profesor.getID() == id) { //comprueba los ID
                        return profesor; //si lo encuentra, lo retorna
                }
        }
        Docente nuevo; //Objeto vacio para retornar
        return nuevo;
}

//================================== FUNCIONES CURSOS =====================================

//Conversion de horas pedagogicas a Bloques
int bloquesReales(int bloques){
        if (bloques%2==0) {
                return bloques/2;
        }
        return (bloques/2)+1;
}

//Retorna vector de Curso con la info del xlsx
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
                int bloques = stoi(vectorCurso.at(curso).at(5));
                Curso nuevoCurso(codigo, nombre, idDocente, bloques);
                vectorInfoCurso.push_back(nuevoCurso);

        }
        return vectorInfoCurso;
}

// //Imprime vector de Docentes
// void imprimirVectorCursos(char *argv[]){
//         vector<Curso> allCursos = obtenerVectorInfoCursos(argv);
//         vector<Docente> allDocentes = obtenerVectorInfoDocentes(argv);
//         int contador = 0;
//         for(Curso info : allCursos) {
//                 info.imprimirCurso(buscarDocenteByID(info.getID_Docente(), allDocentes));
//                 contador++;
//         }
//         cout << endl << endl << "Cantidad de Cursos: " << contador << endl;
// }

//Retorna el numero de bloques totales asignados a un profesor desde vector Curso
int obtenerBloquesPorDocenteByCurso(string id, vector<Curso> vector){
        int holgura = 0;
        for(Curso c : vector) { //itera el vector
                if(c.getID_Docente() == id) { //verifica si tienen el mismo ID
                        holgura += c.getBloques(); //si son iguales, suma su holgura
                }
        }
        return holgura;
}

//================================== FUNCIONES SALAS =====================================

//Crea el archivo .xlsx de salida y coloca el nombre de cada pestaña segun las salas disponibles en Salas.xlsx
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


//Retorna vector de Sala con la info del xlsx
void crearArchivoSalidaConNombreSheet(vector<Sala> vectorSala){
        xlnt::workbook wbOut; //Instancia de workbook
        string dest_filename = "salida.xlsx";
        xlnt::border border;
        border=estilo_borde(border);
        for(int i = 0; i < vectorSala.size(); i++) {  //Se crea una hoja por sala
                wbOut.create_sheet();   //Crea hoja
                xlnt::worksheet hojaActiva = wbOut.sheet_by_index(i); //Se busca la hoja recien creada
                string nombreSala = vectorSala.at(i).getNombre(); //Se obtiene el nombre de la sala
                hojaActiva.title(nombreSala); //Se agrega el nombre de la sala a la hoja
                hojaActiva.merge_cells("A1:B1"); //Decoracion
                hojaActiva.merge_cells("H6:H8"); //Decoracion
                escribirDias(hojaActiva,border);
                escribirPeriodos(hojaActiva,border);
        }
        wbOut.remove_sheet(wbOut.sheet_by_index(vectorSala.size()));  //Se remueve la hoja que viene por defecto en el workbook
        wbOut.save(dest_filename);    //Se guarda en el archivo de destino

}
