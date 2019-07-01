#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <typeinfo>

using namespace std;
using namespace xlnt;

/* Cuenta la cantidad de filas que hay los archivos xlxs */
int cantidadFilasPorArchivo(workbook archivo){
	auto sheetArchivo = archivo.active_sheet(); //trabajando con la 1° pestaña del archivo

	int contadorFilas = 0;
	for (auto row : sheetArchivo.rows(false)) //seudoForEach que recorrelas filas.
	{
		contadorFilas++;
	}

	cout << "Cantidad de filas:" << contadorFilas << endl << endl;
}


/* Funcion que permite verificar la cantidad correcta de argumentos */
bool validarCantidad(int argc, char *argv[]){

	if (argc-1 != 6) {
		return false;
	}

	else{
		return true;
	}

}

int main(int argc, char *argv[])
{
	if (validarCantidad(argc, argv) == true) {

		cout << "Cantidad de Argumentos Valida." << endl;

		workbook cursos; //instancia de objeto que aloja el xlsx
		workbook docentes; //instancia de objeto que aloja el xlsx
		workbook salas; //instancia de objeto que aloja el xlsx

		/* Se verifica que el prefijo cumpla con el archivo correspondido */
		for (int i = 1; i < argc; i=i+2) {
			char *prefijo = argv[i];

			if(prefijo[1] == 'c') {
				cursos.load(argv[i+1]); //carga del xlsx
			}
			if(prefijo[1] == 'd') {
				docentes.load(argv[i+1]); //carga del xlsx
			}
			if(prefijo[1] == 's') {
				salas.load(argv[i+1]); //carga del xlsx
			}
		}

		cout << " " << endl;
		cantidadFilasPorArchivo(cursos);
		cantidadFilasPorArchivo(docentes);
		cantidadFilasPorArchivo(salas);
	}
	else{
		cout << "Cantidad de Argumentos Invalida." << endl;
	}

	return 0;
}
