import os

def agregar_cadena_al_inicio(archivo_entrada, archivo_salida, cadena):
    with open(archivo_entrada, 'r') as entrada:
        contenido_original = entrada.read()
    
    with open(archivo_salida, 'w') as salida:
        salida.write(cadena + contenido_original)

def main():
    directorio = "./20/"  # Ajusta la ruta a tu directorio
    cadena_a_agregar = "20 10 \n"

    for archivo in os.listdir(directorio):
        if archivo.endswith(".txt"):
            ruta_entrada = os.path.join(directorio, archivo)
            ruta_salida = os.path.join(directorio, "temporal.txt")

            agregar_cadena_al_inicio(ruta_entrada, ruta_salida, cadena_a_agregar)

            # Reemplazar el archivo original con el archivo de salida temporal
            os.remove(ruta_entrada)
            os.rename(ruta_salida, ruta_entrada)

            print(f"Agregada cadena al inicio de {archivo}")

if __name__ == "__main__":
    main()

