#Variables

CXX = g++
CXXFLAGS = -std=c++14

FUENTE = main.cpp
NOMBRE = tarea.out
XLSX = ArchivosXLSX/Cursos.xlsx ArchivosXLSX/Docentes.xlsx ArchivosXLSX/Salas.xlsx

LIB = -Ixlnt/include -lxlnt

CLASES = Clases_Funciones/docente.cpp Clases_Funciones/curso.cpp
FUNCIONES = Clases_Funciones/funciones.cpp

#Reglas


tarea: $(FUENTE) $(CLASES) $(FUNCIONES)
	$(CXX) $(FUENTE) -o $(NOMBRE) $(CLASES) $(FUNCIONES) $(CXXFLAGS) $(LIB)
	clear
	./$(NOMBRE) $(XLSX)

ejecutar:
	./$(NOMBRE) $(XLSX)

clear:
	rm $(NOMBRE)