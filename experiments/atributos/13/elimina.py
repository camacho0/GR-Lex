import os
import numpy as np

def eliminar_primera_linea(archivo_entrada, archivo_salida):
    with open(archivo_entrada, 'r') as entrada:
        lineas = entrada.readlines()
    
    with open(archivo_salida, 'w') as salida:
        salida.writelines(lineas[1:])

def main():
    directorio = "./90/"  # Ajusta la ruta a tu directorio

    for archivo in os.listdir(directorio):
        if archivo.endswith(".txt"):
            ruta_entrada = os.path.join(directorio, archivo)
            ruta_salida = os.path.join(directorio, "temporal.txt")

            eliminar_primera_linea(ruta_entrada, ruta_salida)

            # Reemplazar el archivo original con el archivo de salida temporal
            os.remove(ruta_entrada)
            os.rename(ruta_salida, ruta_entrada)

            print(f"Eliminada la primera línea de {archivo}")
            data=np.loadtxt(ruta_entrada)
            data=data*100
            np.savetxt(ruta_entrada,data,delimiter=" ",fmt="%i")

if __name__ == "__main__":
    main()

