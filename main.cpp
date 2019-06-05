#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>
#include "Clases_Funciones/docente.h"
#include "Clases_Funciones/curso.h"
#include "Clases_Funciones/sala.h"
#include "Clases_Funciones/funciones.h"

using namespace std;
using namespace xlnt;

void quickSort(vector<Docente> &numeros, int limite_izq, int limite_der){
        int pivote = numeros.at((limite_izq + limite_der)/2).getHolgura();
        int i = limite_izq;
        int j = limite_der;
        int aux;


        while(i<=j) {
                while(numeros.at(i).getHolgura() < pivote)
                        i++;
                while(numeros.at(j).getHolgura() > pivote)
                        j--;
                //En este punto los límites están en la ubicación para ser intercambiados

                if(i <= j) {
                        aux = numeros.at(i).getHolgura();
                        numeros.at(i).setHolgura(numeros.at(j).getHolgura());
                        numeros.at(j).setHolgura(aux);
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


int main(int argc, char *argv[])
{

        vector<Docente> vectorDocente = obtenerVectorInfoDocentes(argv);
        vector<Curso> vectorCurso = obtenerVectorInfoCursos(argv);
        vector<vector<string> > vectorHolgura;

        cout << vectorDocente.at(0).getHolgura() << endl;
        // vectorDocente.at(0).setHolgura(10);
        // cout << vectorDocente.at(0).getHolgura() << endl;


        for(int i = 0; i < vectorDocente.size(); i++) {
                int disponibilidad = 39-vectorDocente.at(i).getPesoDisponibilidad(); //39: disponibilidad todos los bloques en una semana

                int holgura = obtenerBloquesPorDocente(vectorDocente.at(i).getID(), vectorCurso);
                // cout << vectorDocente.at(i).getNombre() << " " << vectorDocente.at(i).getApellido() << " /Holgura: " << disponibilidad - holgura << endl;
                int calculoHolgura = disponibilidad - holgura;
                vectorDocente.at(i).setHolgura(calculoHolgura);
                cout << vectorDocente.at(i).getHolgura() << endl;
        }
        // quickSort(vectorDocente, 0, vectorDocente.size()-1);

        // for(Docente profe : vectorDocente) {
        //         // cout << profe.getNombre() << " " << profe.getApellido() << " /Holgura: " << profe.getHolgura() << endl;
        //         cout << profe.getHolgura() << end;
        // }
        cout << vectorDocente.at(3).getHolgura() << endl;

        return 0;
}
