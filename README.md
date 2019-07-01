# ProyectoCP2019

Descripción: *Pendiente a subir*

## Instalación (Ubuntu):
1. Instalar CMake.
```
$ sudo apt-get install cmake
```
2. Instalar Libreria.

```
$ git clone https://github.com/FabianAlvaradoDonoso/xlnt
$ cd xlnt
$ cmake .
$ make -j 2
$ sudo make install
$ sudo ldconfig
```

3. Compilar y Ejecutar con:
```
$ make
```

#### En el caso de errores:

- Si 'Make' no funciona, compilar y ejecutar con:
```
$ g++ main.cpp -o tarea.out Clases_Funciones/docente.cpp Clases_Funciones/curso.cpp Clases_Funciones/sala.cpp Clases_Funciones/funciones.cpp -std=c++14 -Ixlnt/include -lxlnt
$ ./tarea.out -c ArchivosXLSX/Cursos.xlsx -d ArchivosXLSX/Docentes.xlsx -s ArchivosXLSX/Salas.xlsx
```
- Errores con archivo .so:

	Agregar "/usr/local/lib" al final de /etc/ld.so.conf y luego:
```
$ sudo ldconfig
$ ldconfig -p | grep local
```

## Objetivo del proyecto

Pendiente a subir
