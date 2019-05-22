# ProyectoCP2019

Descripción: *Pendiente a subir*

## Instalación (Ubuntu):
1. Instalar CMake.
```
$ sudo apt-get install cmake
```
2. Instalar Libreria.

```
$ git clone https://github.com/tfussell/xlnt.git
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
$ g++ main.cpp -o tarea -std=c++14 -xlnt/include -lxlnt
$ ./tarea Cursos.xlsx Docentes.xlsx Salas.xlsx
```
- Errores con archivo .so:

	Agregar "/usr/local/lib" al final de /etc/ld.so.conf y luego:
```
$ sudo ldconfig
$ ldconfig -p | grep local
```

## Objetivo del proyecto

Pendiente a subir
