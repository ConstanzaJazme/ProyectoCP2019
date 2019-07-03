#Variables

CXX = g++ -fopenmp
CXXFLAGS = -std=c++14

CXXMPI = mpic++ -fopenmp
CXXRMPI = mpirun
CXXFLAGSMPI = --oversubscribe

FUENTE = main.cpp
NOMBRE = tarea.out
XLSX = -c ArchivosXLSX/Cursos.xlsx -d ArchivosXLSX/Docentes.xlsx -s ArchivosXLSX/Salas.xlsx

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
