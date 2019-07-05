#Variables

CXX = g++
CXXFLAGS = -std=c++14 -fopenmp

CXXMPI = mpic++
CXXRMPI = mpirun
CXXFLAGSMPI = --oversubscribe

FUENTE = main.cpp
NOMBRE = tarea.out
XLSX = -s ArchivosXLSX/Salas.xlsx -c ArchivosXLSX/Cursos.xlsx -d ArchivosXLSX/Docentes.xlsx

LIB = -Ixlnt/include -lxlnt

CLASES = Clases_Funciones/docente.cpp Clases_Funciones/curso.cpp Clases_Funciones/sala.cpp
FUNCIONES = Clases_Funciones/funciones.cpp

#Reglas


tarea: $(FUENTE) $(CLASES) $(FUNCIONES)
	$(CXX) $(FUENTE) -o $(NOMBRE) $(CLASES) $(FUNCIONES) $(CXXFLAGS) $(LIB)
	clear
	./$(NOMBRE) $(XLSX)

tareaMPI: $(FUENTE) $(CLASES) $(FUNCIONES)
		$(CXXMPI) $(FUENTE) -o $(NOMBRE) $(CLASES) $(FUNCIONES) $(CXXFLAGS) $(LIB)
		clear
		$(CXXRMPI)  $(CXXFLAGSMPI) -np $(shell bash -c 'read  -p "Cantidad -np: " pwd; echo $$pwd') $(NOMBRE) $(XLSX)

ejecutar:
	./$(NOMBRE) $(XLSX)

clear:
	rm $(NOMBRE)

.DEFAULT_GOAL := tarea
