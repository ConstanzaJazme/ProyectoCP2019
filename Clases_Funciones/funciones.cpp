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
        xlnt::worksheet hojaActiva = wb.sheet_by_index(index);    //Se accede a la hoja de posición index en el XLSX
        vector<vector<string> > vectorHojaCompleta;
        for(auto fila : hojaActiva.rows(false)) {   //Se recorre fila a fila
                vector<string> vectorFilasIndividuales;
                for (auto celda : fila)   //Se accede a cada celda de la fila (fila-columna)
                        vectorFilasIndividuales.push_back(celda.to_string());
                vectorHojaCompleta.push_back(vectorFilasIndividuales);    //Se guarda por [Fila][Columna]
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
        int contINF=0;
        int contNORMAL=0;
        int cuentaTotal=0;
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


int decisionBloquesJuntos(int bloques){
        if (bloques/2==0) return 1; //Si la cantidad de bloques da 0, significa que solo hay un bloque de es ramo.
        else{
                if (bloques%2!=0) { //Si el numero es impar, significa que es posible asignar 3 bloques y el resto en pares
                        int aleatorio=rand()%2;
                        if (aleatorio==0) return 2; //Se decidira aleatoriamente si se deben enviar los 3 juntos, o solo de 2
                        else return 3;
                }
                else{
                        return 2; //Si no hay 3 bloques, se enviaran dos bloques juntos
                }
        }
}

bool repeticionRamoSalaDistinta(int salaAleatoria, string ramo, int dia, int periodo, string profesor, vector<vector<vector<string> > > superCubo){
        string ramoProfesor = ramo + " - " + profesor;
        for(int sala = 0; sala < superCubo.size(); sala++) {
                string ramoCubo = superCubo.at(sala).at(dia).at(periodo);
                if(sala != salaAleatoria && ramoCubo == ramoProfesor && ramoCubo.substr(ramoCubo.length()-4, ramoCubo.length()) == profesor) {
                        return false;
                }
        }
        return true;
}


int obtenerNumMayor(int mayor, int numero, int posicion){   //Función que retorna el mayor entre 2 numeros
        if (mayor>=10) mayor=mayor/10; //Como el numero que se recibira puede ya haber pasado por esta funcion, se verifica que el numero que llegue sea menor a 10, si es mayor significa que el segundo digito es la posicion
        if (numero>mayor) mayor=numero; //Compara las variables mayor y numero, y si numero es mayor, este se vuelve la nueva variable mayor
        return (mayor*10)+posicion;
}

bool asignarAsignatura(vector<vector<vector<string> > > &superCubo, int salas, Docente &profesor, string idRamo){
        for(int dia = 0; dia < superCubo.at(salas).size(); dia++) {
                for(int periodo = 0; periodo < superCubo.at(salas).at(dia).size(); periodo++) {
                        if(superCubo.at(salas).at(dia).at(periodo)[0] == '*' && profesor.estaDisponible(dia, periodo)) {
                                profesor.reservarHorario(dia, periodo);
                                superCubo.at(salas).at(dia).at(periodo) = idRamo + " - " + profesor.getID();
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

//Obtiene la disponibilidad total que se encuentra en el XLSX DOCENTE, convirtiendola en [PESTAÑA][FILA][COLUMNA]=[DÍA][PROFESOR][PERIODO]
vector<vector<vector<string> > > obtenerVectorInfoDisponibilidad(xlnt::workbook xlsDocentes, int cantidad_hojas){
        vector<vector<vector<string> > > vectorInfoDias; //Vector que contiene vector de vectores por día
        for (int sheet = 0; sheet < cantidad_hojas; sheet++) { //iteracion por pestañas en el xlsx
                vector< vector<string> > vectorSheet = crearVectorVectoresIndex(xlsDocentes, sheet); //obtencion de informacion de cada pestaña
                vectorInfoDias.push_back(vectorSheet);
        }
        return vectorInfoDias;
}


//Obtiene el vector de disponibilidad de un profesor en especifico y retorna la cantidad de veces que NO esta disponible, ademas se llena el vector de la disponibilidad diaria de cada docente
int ObtenerPesoDisponibilidad(vector<vector<int> > &disponiblexDia, vector<vector<vector<string> > > vectorInfoDias, int profesores, int cantidad_hojas ){
        int pesoDisponibilidad = 0; //PesoDisponibilidad para la cuenta de "NO DISPONIBLE"
        for (int dias = 0; dias < cantidad_hojas; dias++) {
                int conjunto_mayor=0, conjunto_momentaneo=0, posicion_final=0, dispDiaria =0; // conjunto_mayor para almacenar el grupo mayor de "DISPONIBLE" juntos, conjunto_momentaneo cuenta de "DISPONIBLE" juntos
                vector<int> dia_x; //Vector que almacena la disponibilidad por día de un profesor
                for(int col = 3; col < vectorInfoDias.at(dias).at(profesores).size(); col++) { //Se itera por columnnas
                        if(vectorInfoDias.at(dias).at(profesores).at(col)[0] == 'D') {
                                conjunto_momentaneo++; //Suma los bloques disponibles
                                dia_x.push_back(1);
                                conjunto_mayor= obtenerNumMayor(conjunto_mayor,conjunto_momentaneo, col-3);
                                dispDiaria++;
                        } else {
                                conjunto_momentaneo=0; //Cuando se encuentra un "NO DISPONIBLE" la sumatoria se reinicia.
                                dia_x.push_back(0);
                                pesoDisponibilidad++;
                        }
                }
                dia_x.push_back(dispDiaria);
                dia_x.push_back(conjunto_mayor);
                disponiblexDia.push_back(dia_x);
        }
        return pesoDisponibilidad;
}

//Retorna vector de Docentes con la info de todas las pestañas del xlsx
vector<Docente> obtenerVectorInfoDocentes(char *argv[]){
        xlnt::workbook xlsDocentes, xlsCursos;
        xlsDocentes.load(argv[2]); //carga del xlsx
        xlsCursos.load(argv[1]); //carga del xlsx
        int cantidad_hojas= xlsDocentes.sheet_count();
        vector<Docente> vectorInfoDocentes; //Vector a devolver
        vector< vector<string> > CursosDocente = crearVectorVectoresIndex(xlsCursos, 0); //Vector de vectores de los cursos
        vector<vector<vector<string> > > vectorInfoDias= obtenerVectorInfoDisponibilidad(xlsDocentes,cantidad_hojas); //Vector que contiene vector de vectores por día cada pestaña día del XLSX
        for (int profesores = 1; profesores < vectorInfoDias.at(0).size(); profesores++) {    //Iteración por profesor
                vector<vector<int> > disponiblexDia;   //Vector que será rellenado con las disponibilidades diarias de cada profesor
                string id = vectorInfoDias.at(0).at(profesores).at(0); //OJO, como la información de los profesores se repite en todas las hojas, se sca solo de la inicial.
                string nombres =  vectorInfoDias.at(0).at(profesores).at(1);
                string apellidos = vectorInfoDias.at(0).at(profesores).at(2);
                std::cout << "APELLIDOS: "<<apellidos << '\n';
                int pesoDisponibilidad=ObtenerPesoDisponibilidad(disponiblexDia,vectorInfoDias,profesores,cantidad_hojas);  //variable que contabiliza los NO DISPONIBLES
                vector <Curso> asignaturas=VectorVectoresAsignatura(CursosDocente, id);
                Docente nuevoProfesor(id, nombres, apellidos, disponiblexDia, pesoDisponibilidad, 0,asignaturas);   //despues de que se recopila todos los datos se crea un objecto de clase Docente
                nuevoProfesor.imprimirDocente();
                disponiblexDia.clear();
                vectorInfoDocentes.push_back(nuevoProfesor);    //se guarda el objeto en vector que los contenga a todos
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
void ordenarPorHolguraVectorDocente(vector<Docente> &vectorDocente){
        for(int i = 0; i < vectorDocente.size(); i++) { //itera vector docente
                //calcula disponibilidad restando 39 (7 bloques * 5 diasSemana + 4 bloques dia sabado)
                //menos lo obtenido en el objeto docente ya calculado
                int disponibilidadReal = 39-vectorDocente.at(i).getPesoDisponibilidad(); //39: disponibilidad todos los bloques en una semana
                //Se busca lo que realmente se necesita en bloques para cada profesor
                int disponibilidadEsperada = obtenerBloquesPorDocenteByCurso(vectorDocente.at(i).getAsignaturas());
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

//Retorna el numero de bloques totales asignados a un profesor desde vector Curso contenido en Docente
int obtenerBloquesPorDocenteByCurso(vector<Curso> vector){
        int bloquesNecesarios = 0;
        for(Curso c : vector) { //itera el vector de Cursos
                bloquesNecesarios += c.getBloques(); //suma la cantidad de bloques que debe cumplir el docente
        }
        return bloquesNecesarios;
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
