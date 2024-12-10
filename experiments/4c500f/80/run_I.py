import os

# Ruta al programa en C++
programa_en_cpp = "./../matI"

# Directorio donde se encuentran los archivos .txt de entrada
directorio_entrada = "./../names/"

# Ruta al archivo .txt de salida
archivo_salida = "./../izq_re/80.txt"

# Obtener la lista de archivos .txt en el directorio de entrada
archivos_entrada = [f for f in os.listdir(directorio_entrada) if f.endswith(".txt")]

# Iterar sobre cada archivo .txt, ejecutar el programa en C++ y guardar los resultados en el archivo de salida
with open(archivo_salida, 'w') as salida_global:
    for archivo_entrada in archivos_entrada:
        # Construir la ruta completa para el archivo de entrada
        ruta_entrada = os.path.join(directorio_entrada, archivo_entrada)

        # Comando para ejecutar el programa en C++ con el archivo .txt de entrada y concatenar el resultado al archivo de salida
        comando = f"{programa_en_cpp} < {ruta_entrada}"
        print(comando)
        resultado = os.popen(comando).read()
        salida_global.write(f"Archivo: {archivo_entrada}\n{resultado}\n{'='*30}\n")
        salida_global.flush()

print("Proceso completado. Resultados guardados en el archivo de salida.")

