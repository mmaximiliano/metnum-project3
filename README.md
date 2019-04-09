# Métodos Numéricos - Trabajo Práctico 3 - Tomografía Computada

## Cómo compilar el código
Para compilar, dirigirse al directorio `codigo` y luego

```
mkdir -p build
cd build
cmake ..
make
```

Para ejecutar, desde el directorio build, correr:
```
./tp3 -i <image-path> -r <ray-type> <n> -s <size-n> -n <noise> -e <eigenvalue-min> -o <output-dir> -t <time-dir>
```
Donde
- image-path es la imagen a reconstruir
- ray-type es el tipo de rayo (0 es random, 1 rotated, 2 lateralBorders, 3 allBorders)
- size-n es el tamaño de discretizacion
- noise es el nivel de ruido, como se explica en el informe
- eigenvalue-min es la cantidad de valores singulares que busca al armar SVD
- output-dir es el directorio donde se pondra la reconstruccion, en csv
- time-dir es el directorio donde se pondra los tiempos de ejecucion de cada parte del programa, en json

## Cómo compilar el informe
El informe puede ser compilado con `Makefile`. Requiere tener el comando `pdflatex` y algunas bibliotecas de latex.

Comandos disponibles de `Makefile`:
- `make`: compila el pdf. Corre 2 veces pdflatex para generar correctamente el índice.
- `make read`: abre el lector de pdf default del sistema con xdg-open.
- `make clean`: elimina los archivos generados al compilar.



