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

vector<vector<string> > obtenerCursosPorDocente(vector<Curso> vectorCurso, string docente){
        vector<vector<string> > cursosPorDocente;
        for(int curso = 0; curso < vectorCurso.size(); curso++) {
                if(vectorCurso.at(curso).getID_Docente() == docente) {
                        vector<string> infoCurso;
                        infoCurso.push_back(vectorCurso.at(curso).getCodigo());
                        infoCurso.push_back(vectorCurso.at(curso).getBloques());
                        cursosPorDocente.push_back(infoCurso);
                }
        }
        return cursosPorDocente;
}

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

bool esRamoInformatica(string ramo){
        if(ramo[0] == 'I' && ramo[1] == 'N' && ramo[2] == 'F') return true;
        return false;
}

bool esLab(vector<vector<string> > vectorDiaPeriodo){
        string nombreSala = vectorDiaPeriodo.at(0).at(0).substr(0,3);
        if(nombreSala == "INF" || nombreSala == "*LA") {
                return true;
        }
        return false;
}


int main(int argc, char *argv[])
{
        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        vector<Sala> vectorSala = obtenerVectorInfoSalas(argv);
        vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);

        ordenarPorHolguraVectorDocente(vectorDocente, vectorCurso);

        vector<vector<vector<string> > > superCubo = crearSuperCubo(vectorSala);


        int ramos = 0;

        for(int docente = 0; docente < vectorDocente.size(); docente++) {
                vector<vector<string> > cursosDocente = obtenerCursosPorDocente(vectorCurso, vectorDocente.at(docente).getID());
                for(int curso = 0; curso < cursosDocente.size(); curso++) {

                        int bloques = stoi(cursosDocente.at(curso).at(1));
                        string idRamo = cursosDocente.at(curso).at(0);
                        int ramoColocado = 0;
                        Docente profesor = vectorDocente.at(docente);
                        bool ramoInformatica = esRamoInformatica(idRamo);

                        while(bloques > 0) {
                                for(int salas = 0; salas < superCubo.size(); salas++) {
                                        bool esLaboratorio = esLab(superCubo.at(salas));

                                        if(!ramoInformatica && !esLaboratorio) {
                                                for(int dias = 0; dias < superCubo.at(salas).size(); dias++) {
                                                        for(int periodos = 0; periodos < superCubo.at(salas).at(dias).size(); periodos++) {
                                                                if(superCubo.at(salas).at(dias).at(periodos)[0] == '*' && profesor.estaDisponible(dias, periodos)) {
                                                                        superCubo.at(salas).at(dias).at(periodos) = idRamo + " - " + vectorDocente.at(docente).getID();
                                                                        ramoColocado++;
                                                                        goto Encontrado;
                                                                }
                                                        }
                                                }
                                        }
                                        if(ramoInformatica && esLaboratorio) {
                                                for(int dias = 0; dias < superCubo.at(salas).size(); dias++) {
                                                        for(int periodos = 0; periodos < superCubo.at(salas).at(dias).size(); periodos++) {
                                                                if(superCubo.at(salas).at(dias).at(periodos)[0] == '*' && profesor.estaDisponible(dias, periodos)) {
                                                                        superCubo.at(salas).at(dias).at(periodos) = idRamo + " - " + vectorDocente.at(docente).getID();
                                                                        ramoColocado++;
                                                                        goto Encontrado;
                                                                }
                                                        }
                                                }
                                        }


                                }
Encontrado:
                                bloques -= 2;
                                // cout << bloques<< endl;

                        }
                        ramos++;

                }
                // cout << docente << endl;
        }
        // cout << "Ramos Totales: " << ramos << endl;
        escribirResultadosEnXlsxFinal(vectorSala, superCubo);






        return 0;
}
