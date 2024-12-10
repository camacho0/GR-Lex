# Ruta al archivo que contiene la lista de archivos .txt
lista_archivos_txt = "./../names.txt"

# Línea que deseas agregar al principio de cada archivo
linea_a_agregar = "200 7"

# Leer la lista de archivos .txt desde el archivo
with open(lista_archivos_txt, 'r') as archivo_lista:
    archivos_a_modificar = [linea.strip() for linea in archivo_lista]

# Iterar sobre cada archivo .txt de la lista y agregar la línea al principio
for archivo in archivos_a_modificar:
    with open(archivo, 'r') as archivo_original:
        contenido_original = archivo_original.read()

    # Agregar la línea al principio
    contenido_modificado = f"{linea_a_agregar}\n{contenido_original}"

    with open(archivo, 'w') as archivo_modificado:
        archivo_modificado.write(contenido_modificado)

print("Línea agregada al principio de los archivos.")

