El script csv_converter.py convierte imagenes de una carpeta en formato csv (filas con los pixeles separados por comas) y además ajusta el tamaño para que se vuelva cuadrada.

- Para convertir todas las imagenes con extensión "png" de una carpeta "imagenes/" en csv y poner las imagenes convertidas en el directorio "imagenes_convertidas/" correr:
    python csv_converter.py imagenes/ imagenes_convertidas/ .png

- Lo mismo que antes pero para dcm o pgm (funciona para 16 bits)
    python csv_converter.py imagenes16/ imagenes_convertidas/ .pgm
    python csv_converter.py imagenes16/ imagenes_convertidas/ .dcm

- También para pasar de .dcm a pgm de 16 bits (u otro formato que soporte 16 bits como .png o .tif):
    python csv_converter.py imagenes16/ imagenes_convertidas/ .dcm .pgm

- Para utilizar pgm en C++ consultar el siguiente repositorio:
    https://github.com/patxiska/ppmloader

- Para visualizar una imagen "imagenes/ejemplo.csv" en CSV correr:
    python csv_visualizer.py imagenes/ejemplo.csv

Dependencias: Numpy, Pillow, SciPy.
    - pip install scipy --user
    - pip install numpy --user
    - pip install pillow --user
    - pip install pydicom --user

