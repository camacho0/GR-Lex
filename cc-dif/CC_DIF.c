/****************************************************************************
Archivo      : cc_dif.c
Contenido    : rutinas para el calculo de los testores difusos tipicos
	       utilizando el algoritmo CC (en ANSI C).
Autor        : Guillermo Sanchez Diaz
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

/* tamanos de las cadenas */
#define TAM_NOMBRE  40
#define TAM_CAD_MIN  5

/* constantes generales */
#define TAM_BYTE 8
#define BELL 7
#define NULO '\0'
#define TT 0
#define LM 1
#define LE  2
#define MARCA 1
#define MAYOR 0
#define MENOR 1
#define IGUAL 2
#define ABRE   "{"
#define CIERRA " }"
#define VARIABLE 'X'
#define SEPARADOR '|'

/* estructuras que maneja la lista de TT */

struct nodo_t {
       int valor;
       int rasgo;
       struct nodo_t *liga;
};

typedef struct nodo_t *NODO_TESTOR;

struct nodo_l {
       struct nodo_t *testor;
       struct nodo_l *siguiente;
};

typedef struct nodo_l *NODO_LISTA;

/* variables globales */
int filas, rasgos;  /* numero de filas y columnas de la MB */
int longitud_testor; /* tamano del TT empaquetado */
char *Mb; /* arreglo para almacenar la MB */
unsigned int mascara; /* variable para efectuar el empaquetamiento */
NODO_LISTA cabeza;   /* cabeza de la lista */
char nombre_resultados[TAM_NOMBRE]="archivosalida.txt"; /* variables para el archivo que tendra */
FILE *resultados;		    /* los testores tipicos */

/* solo del algoritmo */
char *f_marcadas;   /* arreglos para efectuar los bloqueos */
int *lista_maximal_valor, *lista_maximal_fila, *lista_maximal_rasgo;
int *l_aux_valor, *l_aux_fila, *l_aux_rasgo;
int e[3];		       /* arreglo para la lista maximal */
int ultimo_elemento; /* indica cual es el ultimo elemento de la LM */
long numero_testores; /* indica cual es el numero de testores encontrado */
int fil, col; /* posicion del elemento corriente */
int fil_ult, col_ult; /* fila y columna del ultimo elemento */

/* para tomar los tiempos */
time_t ta_ini, ta_fin;

/****************************************************************************

	 >>>>>>>>>>>>>>>   Programa Principal	<<<<<<<<<<<<<<<<

****************************************************************************/

main()
 {
   if (Carga_mb()) /* verifica si se puede cargar la MB a memoria */
     {
       Crea_listas();
       time(&ta_ini);
       Algoritmo_ccdif();
       time(&ta_fin);
       printf("%s%.0lf seg.\n","Tiempo consumido por el algoritmo : ", difftime(ta_fin, ta_ini));
       printf("%s%ld\n", "El numero de testores difusos tipicos encontrado es : ", numero_testores);
       Manda_resultados();
       Elimina_listas(); /* desalojamos la memoria ocupada */
     }
 }

/* verifica si se puede cargar la Mb a memoria */
Carga_mb()
 {
  FILE *archivo;
  char nombre_matriz[TAM_NOMBRE], grado_cad[TAM_CAD_MIN];
  int i, j, k, band=0;

   //printf("\nNombre del archivo que contiene la MB : ");
   scanf("%s", nombre_matriz);
    if ((archivo=fopen(nombre_matriz, "r")) != NULL)
      {
	//printf("\n\nLeyendo los datos de la matriz, un momento por favor... ");
    /* leemos el numero de rasgos y columnas del archivo */
	fscanf(archivo, "%d", &filas);
	fscanf(archivo, "%d", &rasgos);
    /* verificamos si soporta los datos */
	 if ((Mb=(char *)calloc(filas*rasgos, sizeof(char))) != NULL)
	   {
    /* leemos los grados de pertenencia */
	     for (i=0; i < filas; i++)
	       for (j=0; j < rasgos; j++)
		 {
		   for (k=0; k < TAM_CAD_MIN; k++) /* limpiamos la cadena */
		     grado_cad[k]=NULO;
		   fscanf(archivo, "%s", grado_cad);
		   Mb[i*rasgos + j]=(char)atoi(grado_cad);
		 }
	     /* creamos el archivo de resultados */
	     //printf("\n\nNombre del archivo para guardar los testores tipicos : ");
	     //scanf("%s", nombre_resultados);
	      if ((resultados=fopen(nombre_resultados, "w")) != NULL)
		{
		  fclose(resultados);
		  band=1; /* continua */
		}
	      else
		printf("\n%cError, no se pudo crear el archivo %s", BELL, nombre_resultados);
	   }
	 else
	   printf("\n%cNo hay memoria suficiente para cargar los datos.", BELL);
	fclose(archivo);
      }
    else
      printf("\n%cError, el archivo no existe", BELL);

  return(band);
 }

/* crea los arreglos a utilizar */
Crea_listas()
 {

  /* creamos la cabeza de la lista y el arreglo de bloqueos por fila */
  cabeza=(NODO_LISTA)malloc(sizeof(struct nodo_l));
  f_marcadas=(char *)calloc(filas, sizeof(char));
  lista_maximal_valor=(int *)calloc(rasgos, sizeof(int));
  lista_maximal_fila=(int *)calloc(rasgos, sizeof(int));
  lista_maximal_rasgo=(int *)calloc(rasgos, sizeof(int));
  l_aux_valor=(int *)calloc(rasgos, sizeof(int));
  l_aux_fila=(int *)calloc(rasgos, sizeof(int));
  l_aux_rasgo=(int *)calloc(rasgos, sizeof(int));
 }

/* libera la memoria ocupada por las estructuras utilizadas */
Elimina_listas()
 {

   free(Mb);
   free(f_marcadas);
   free(lista_maximal_valor);
   free(lista_maximal_fila);
   free(lista_maximal_rasgo);
   free(l_aux_valor);
   free(l_aux_fila);
   free(l_aux_rasgo);
   free(cabeza);  /* liberamos la lista de testores tipicos */
 }

/* ordena la lista maximal ascendentemente */
Ordena_lista()
 {
  int i, j, aux1, aux2;

  /* copiamos la lista_maximal para ordenarla y trabajar con la nueva */
   for (i=0; i <= ultimo_elemento; i++)
     {
       l_aux_valor[i]=lista_maximal_valor[i];
       l_aux_fila[i]=lista_maximal_fila[i];
       l_aux_rasgo[i]=lista_maximal_rasgo[i];
     }

   for (i=0; i <= ultimo_elemento-1; i++)
    for (j=ultimo_elemento; j > i; j--)
     if (l_aux_rasgo[j] < l_aux_rasgo[j-1])
       {
	 aux1=l_aux_valor[j]; aux2=l_aux_rasgo[j];
	 l_aux_valor[j]=l_aux_valor[j-1];
	 l_aux_rasgo[j]=l_aux_rasgo[j-1];
	 l_aux_valor[j-1]=aux1; l_aux_rasgo[j-1]=aux2;
       }
 }

/* crea una nueva lista testor para agregarse a TT y la deja en testor2 */
NODO_LISTA Crea_testor()
 {
  NODO_LISTA t;
  NODO_TESTOR tt1, tt2;
  int i;

  /* creamos el nuevo testor y su primer elemento */
  t=(NODO_LISTA)malloc(sizeof(struct nodo_l));
  tt1=(NODO_TESTOR)malloc(sizeof(struct nodo_t));
  t -> testor=tt1;
  t -> siguiente=NULL;
  tt1 -> valor=l_aux_valor[0];
  tt1 -> rasgo=l_aux_rasgo[0];
   for (i=1; i <= ultimo_elemento ; i++)
     {
	tt2=(NODO_TESTOR)malloc(sizeof(struct nodo_t));
	tt1 -> liga=tt2;
	tt2 -> valor=l_aux_valor[i];
	tt2 -> rasgo=l_aux_rasgo[i];
	tt1=tt2;
     }
  tt1 -> liga=NULL; /* para que ya no apunte a otro */

  return(t);
 }

/* retorna MAYOR, si lista_maximal es mayor que el siguiente de test;
   IGUAL si lista_maximal es igual a el siguiente de test;
   MENOR si el siguiente de test es menor que lista_maximal o si
	 test -> siguiente es igual a NULL */
Compara_testores(t1)
NODO_LISTA t1;
 {
  NODO_LISTA t2;
  NODO_TESTOR tt1;
  int comparacion, i;

  comparacion=IGUAL;
   if (t1 -> siguiente != NULL)
     {
       t2=t1 -> siguiente;
       tt1=t2 -> testor;
       i=0;
	while((comparacion == IGUAL) && (i <= ultimo_elemento) &&
	      (tt1 != NULL))
	  if (l_aux_rasgo[i] > tt1 -> rasgo)
	    comparacion=MAYOR;
	  else if (l_aux_rasgo[i] < tt1 -> rasgo)
	    comparacion=MENOR;
	  else if (l_aux_valor[i] > tt1 -> valor)
	    comparacion=MAYOR;
	  else if (l_aux_valor[i] < tt1 -> valor)
	    comparacion=MENOR;
	  else
	    {
	      i++;
	      tt1=tt1 -> liga;
	    }
     }
   else
     comparacion=MENOR; /* ya no mas elementos que comparar */

   if (comparacion == IGUAL) /* verificamos su longitud */
     if ((i > ultimo_elemento) && (tt1 != NULL))
       comparacion=MENOR;
     else if ((i <= ultimo_elemento) && (tt1 == NULL))
       comparacion=MAYOR;

  return(comparacion);
 }

/* verifica si el testor mandado no esta repetido, para escribirlo en TT */
Escribe_testor()
 {
  NODO_LISTA t1, t2;
  int opcion, i;

  Ordena_lista();
  t1=cabeza;
   do
    {
      opcion=Compara_testores(t1);
       if (opcion == MAYOR) /* sigue comparando */
	 t1=t1 -> siguiente;
       else if (opcion == MENOR) /* lo adicionamos a la lista de TT */
	 {
	   t2=Crea_testor();
	   t2 -> siguiente=t1 -> siguiente;
	   t1 -> siguiente=t2;
	   numero_testores++;
	 }
    } while(opcion == MAYOR);
 }

/****************************************************************************

   ---------->>>>>>> Rutinas que efectuan el algoritmo CC <<<<<<<----------

****************************************************************************\

/* ejecuta el algoritmo CC dif*/
Algoritmo_ccdif()
 {
  int i,j;

   //printf("\nIniciando el algoritmo...");
   /* inicializamos variables generales */
   cabeza -> testor=NULL;  cabeza -> siguiente=NULL;
   numero_testores=0;
   ultimo_elemento=-1;
    for (i=0; i < filas; i++)
      for (j=0; j < rasgos; j++)
	if (Mb[i*rasgos + j]) /* elemento no nulo */
	  {
	   // printf("\nProcesando elemento : a%d,%d", i+1,j+1);
	    Limpia_bloqueos();
	    e[0]=Mb[i*rasgos + j];  e[1]=i;  e[2]=j;
	    Adiciona_elemento(LM);
	     while(Lista_no_vacia(LM))
	       {
		 Siguiente_compatible();
		  if (Lista_no_vacia(LE))
		    Adiciona_elemento(LM);
		  else
		    {
		       if (Es_testor())
			 Adiciona_elemento(TT);
		      Elimina_ultimo();
		    }
	       }
	  }
 }

/* limpia las listas de bloqueo */
Limpia_bloqueos()
 {
  int i;

   for (i=0; i < filas; i++)
     f_marcadas[i]=0;
 }

/* adiciona un nuevo elemento en la lista maximal o en la de testores */
Adiciona_elemento(int elemento)
 {

   if (elemento == LM)
     {
       lista_maximal_valor[++ultimo_elemento]=e[0];	      /* valor */
       lista_maximal_fila[ultimo_elemento]=fil=fil_ult=e[1];  /* fila */
       lista_maximal_rasgo[ultimo_elemento]=col=col_ult=e[2]; /* columna */
       Bloqueos(); /* efectuamos los bloqueos por filas y columnas */
     }
   else
     Escribe_testor();
 }

/* realiza el bloqueo por filas del elemento corriente */
Bloqueos()
 {
  int i;

   for (i=0; i < filas; i++)  /* por filas */
     if (Mb[i*rasgos + col] >= Mb[fil*rasgos + col]) /* hay que bloquear */
       f_marcadas[i]=MARCA;
 }

/* verifica si la lista especificada no contiene elementos */
Lista_no_vacia(int lista)
 {
   if (lista == LM)
     return(lista_maximal_valor[0]);
   else
     return(e[0]);
 }

/* busca el siguiente elemento compatible de la lista y lo deja en e */
Siguiente_compatible()
 {
  int i, j, band;

  i=fil_ult;   /* empezamos en la fila y siguiente columna del ultimo */
  j=col_ult+1; /* elemento */
  e[0]=e[1]=e[2]=0; /* suponemos no hay siguiente compatible */
  band=1; /* no se ha hallado el compatible */
   while ((i < filas) && (band))
     if (f_marcadas[i]) /* hay bloqueo */
       {
	 i++;
	 j=0;
       }
     else
       {
	 while ((band) && (j < rasgos))
	   if (Es_compatible(i, j))
	     {
	       band=0; /* se encontro */
	       e[0]=Mb[i*rasgos + j];
	       e[1]=i;
	       e[2]=j;
	     }
	   else
	     j++;
	 if (band) /* no se hallo */
	   {
	     i++; /* buscamos en la siguiente fila, primera columna */
	     j=0;
	   }
       }
 }

/* retorna 1 si los elementos ai,j y afil,col son compatibles */
Es_compatible(int i, int j)
 {
  int k, band;

   band=1; k=0;
    while ((k <= ultimo_elemento) && (band))
      if ((Mb[lista_maximal_fila[k]*rasgos + lista_maximal_rasgo[k]] >
	   Mb[i*rasgos + lista_maximal_rasgo[k]]) &&
	  (Mb[i*rasgos + j] > Mb[lista_maximal_fila[k]*rasgos + j]))
	k++;
      else
	band=0;

  return(band);
 }

/* verifica si la lista maximal es testor */
Es_testor()
 {
  int i, band;

  /* verifica si el bloqueo por filas no contiene ceros */
  i=0;  band=1;
    while ((band) && (i < filas))
      if (f_marcadas[i])
	i++;
      else
	band=0;

  return(band);
 }

/* elimina el ultimo elemento de la lista maximal */
Elimina_ultimo()
 {
  int i;

   /* dejamos las coordenadas del ultimo elemento en la lista, para que las
      utilice posteriormente la funcion Siguiente_Compatible */
   fil_ult=lista_maximal_fila[ultimo_elemento]; /* para que no haya */
   col_ult=lista_maximal_rasgo[ultimo_elemento]; /* repeticiones en la lista */
   lista_maximal_valor[ultimo_elemento--]=0;
   /* Ajustamos el bloqueo con los elementos restantes */
   Limpia_bloqueos();
     for (i=0; i <= ultimo_elemento; i++)
       {
	 fil=lista_maximal_fila[i];
	 col=lista_maximal_rasgo[i];
	 Bloqueos();
       }
 }

/* manda los resultados a disco */
Manda_resultados()
 {
  NODO_LISTA t1, t2;
  NODO_TESTOR tt1, tt2;
  float val;
	/*
   printf("\n\n%cAlgoritmo finalizado.", BELL);
   printf("\nEl numero de testores difusos tipicos hallado es : %ld\n",numero_testores);
   printf("\nEscribiendo los testores tipicos encontrados en disco...\n");
	 */
   resultados=fopen(nombre_resultados, "w");
   //fprintf(resultados, "%s%ld\n", "El numero de testores difusos tipicos encontrado es : ", numero_testores);
   //fprintf(resultados, "%s%.0lf seg.\n","Tiempo consumido por el algoritmo : ", difftime(ta_fin, ta_ini));
   t1=cabeza -> siguiente;
    while (t1 != NULL)
      {
	t2=t1 -> siguiente;
	fprintf(resultados, "%s", ABRE);
	tt1=t1 -> testor;
	 while (tt1 != NULL)
	   {
	     tt2=tt1 -> liga;
	     val=(float)tt1 -> valor / 100.0;
	     fprintf(resultados, " %c%d%c%1.2f", VARIABLE, tt1 -> rasgo + 1,
		     SEPARADOR, val);
	      if (tt2 != NULL) /* hay mas elementos */
		fprintf(resultados, ",");
	     free(tt1); /* se va liberando la lista de TT */
	     tt1=tt2;
	   }
	fprintf(resultados, "%s\n", CIERRA);
	free(t1); /* se va liberando la lista de TT */
	t1=t2;
      }
   fclose(resultados);
 }
