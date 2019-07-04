# ProyectoCP2019

Descripción: Desarrollo de Proyecto de Computación Paralela, creación de horarios coherentes dependiendo de los archivos desde donde obtiene la información

## Instalación (Ubuntu):
1. Instalar Compilador C++.

```
$ sudo apt-get install g++
or
$ sudo dnf install gcc-c++
```

2. Instalar CMake.

```
$ sudo apt-get install cmake
or
$ sudo yum install make automake kernel-devel
```
3. Instalar Libreria XLNT.

```
$ git clone https://github.com/FabianAlvaradoDonoso/xlnt
$ cd xlnt
$ cmake .
$ make -j 2
$ sudo make install
$ sudo ldconfig
```
4. Instalar OpenMP

```
$ sudo apt-get install libomp-dev
or
$ sudo dnf --refresh install MUMPS-openmp

```

5. Instalar Proyecto

```
$ git https://github.com/ConstanzaJazme/ProyectoCP2019.git
$ cd ProyectoCP2019
```

5. Uso:

- Compilación y Ejecución automático:

```
$ make
```

- Compilación y Ejecución manual:
```
$ g++ main.cpp -o tarea.out Clases_Funciones/docente.cpp Clases_Funciones/curso.cpp Clases_Funciones/sala.cpp Clases_Funciones/funciones.cpp -std=c++14 -fopenmp -Ixlnt/include -lxlnt

$./tarea.out -c “Archivo_Curso”.xlsx -d “Archivo_Docentes”.xlsx -s “Archivo_Salas”.xlsx
```

- Manual de Usuario
https://drive.google.com/file/d/1tkBnD2nuE343VCFYNwfAYxfj4OcaTvJk/view?usp=sharing
