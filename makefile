#Variables

CXX = g++
CXXFLAGS = -std=c++14

FUENTE = main.cpp
NOMBRE = tarea.out
XLSX = ArchivosXLSX/Cursos.xlsx ArchivosXLSX/Docentes.xlsx ArchivosXLSX/Salas.xlsx

LIB = -Ixlnt/include -lxlnt

CLASES = Clases_Funciones/docente.cpp

#Reglas


tarea: $(FUENTE) $(CLASES)
	$(CXX) $(FUENTE) -o $(NOMBRE) $(CLASES) $(CXXFLAGS) $(LIB)
	clear
	./$(NOMBRE) $(XLSX)

ejecutar:
	./$(NOMBRE) $(XLSX)

clear:
	rm $(NOMBRE)
