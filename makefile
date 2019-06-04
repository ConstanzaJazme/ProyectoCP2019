#Variables

CXX = g++
CXXFLAGS = -std=c++14

FUENTE = main.cpp
NOMBRE = tarea.out
XLSX = ArchivosXLSX/Cursos.xlsx ArchivosXLSX/Docentes.xlsx ArchivosXLSX/Salas.xlsx

LIB = -Ixlnt/include -lxlnt

CLASES = Clases_Funciones/docente.cpp Clases_Funciones/curso.cpp Clases_Funciones/sala.cpp
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

main2: main2.cpp
	g++ main2.cpp -o prueba -std=c++14 -Ixlnt/include -lxlnt
