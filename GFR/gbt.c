
/* gBT.C */

/* Algoritmo gBT para calcular los testores tipicos de Goldman */
/*               de una matriz real                            */

/* Jesus Ariel Carrasco Ochoa */
/* julio 21, 1998             */
/* diciembre 3, 2015   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FALSE 0
#define TRUE  1

/* para tomar los tiempos */
time_t ini, fin;


FILE *fs, *ff;

long int  nv, nt;

int   nf, nr;    // número de filas y rasgos respectivamente

int ncz;         // número de columnas de ceros

int nunos;

double tamEspacio;

#define PUNTITO 100000

#define MAXFILAS 30000   // Máximo tamaño de MB 30,000 filas
#define MAXRASGOS 1000   //                      1,000 variables

int MB[MAXFILAS][MAXRASGOS];

int ni[MAXRASGOS] ;     // posición inicial del primer valor diferente d e cero

int nfc[MAXRASGOS] ;     // número de filas cubiertas, para evaluar la redundancia
int ind[MAXRASGOS] ;     // marcas de rasgos indispensable, para evaluar la tipicidad

int MO[MAXFILAS][MAXRASGOS];

char cz[MAXRASGOS];      // marcas para columnas de ceros
char t[MAXRASGOS];
int  v[MAXRASGOS];
int  p[MAXRASGOS];
int  m[MAXRASGOS];

char nom[100];         // nombre de archivo original
char nom1[105];        // temporal nombres de archivo

FILE *f;

void qs(int lista[],int limite_izq,int limite_der)
{
    int izq,der,temporal,pivote;

    izq=limite_izq;
    der = limite_der;
    pivote = lista[(izq+der)/2];
    do{
        while(lista[izq]<pivote && izq<limite_der)izq++;
        while(pivote<lista[der] && der > limite_izq)der--;
        if(izq <=der)
          {
            temporal= lista[izq];
            lista[izq]=lista[der];
            lista[der]=temporal;
            izq++;
            der--;
          }
      }while(izq<=der);
    if(limite_izq<der){qs(lista,limite_izq,der);}
    if(limite_der>izq){qs(lista,izq,limite_der);}
}


int esta( int v, int L[] )
{
	int j;

	for( j=0 ; j<nf ; j++ ) if( v == L[j] ) return TRUE;
	return FALSE;
}

void ordenaMB()
{
  int i, j, L[MAXFILAS];

  for( i=0 ; i<nr ; i++ )
    {
	  for( j=0; j<nf ; j++ ) L[j] = 0;
	  for( j=0; j<nf ; j++ ) if( !esta(MB[j][i], L) ) L[j] = MB[j][i];
	  qs( L, 0, nf-1 );
	  for( j=0; j<nf ; j++ ) MO[j][i] = L[j];
    }
  for( i=0 ; i<nr ; i++ )
    {
	  cz[i] = '0';
	  for( j=0 ; j<nf ; j++ ) if( MO[j][i] != 0 ) break;
	  if( j==nf ) { ncz++; cz[i] = '1'; };
	  ni[i] = j;
	  t[i] = '0';
	  p[i] = 0;
	  v[i] = 0;
    }
  t[nr] = 0;       // para poder escribir t como cadena
/* ahora inicia en 00....00 por si la última columna es de ceros
  //  para iniciar en 0....01
  t[nr-1] = '1';
  p[nr-1] = ni[nr-1];
  v[nr-1] = MO[ni[nr-1]][nr-1];
  nunos = 1;
*/
  tamEspacio = 1;
  for( i=0 ; i<nr ; i++ )
	  tamEspacio *= nf-ni[i]+1;
  printf(" Tamaño del espacio de búsqueda: %e\n\n", tamEspacio);
  printf(" Número de columnas de ceros: %d: ", ncz);
  for( i=0 ; i<nr ; i++ ) if( cz[i] == '1' ) printf( "%d ", i+1 );
  printf("\n\n");
  fflush(stdout);

//  for( i=0 ; i<nr ; i++ )
//     printf("%c",t[i]);
//  printf("\n");
//  fflush(stdout);

}

void inicia(int argc, char *argv[])
{
  int   i, j;
  float tt;
  int   tti;

  if(argc == 1)
        {
	      printf( "Dar el nombre del archivo de la matriz: " );
	      fflush(stdout);
	      scanf( "%s", nom );
        }
    else
        {
    	  strncpy(nom, argv[1], 99);
    	  nom[99]=0;
        }
  f = fopen( nom, "r" );
  if( f == (FILE*)NULL )
        {
          printf( "\n\n El archivo %s no existe \n\n", nom );
          exit(0);
        }
    else
        {
    	  strcpy(nom1,nom);
    	  strcat( nom1, ".tmp" );
    	  fs = fopen( nom1, "w" );
    	  if( fs == (FILE*)NULL )
    	        {
    	          printf( "\n\n No se pudo crear el archivo temporal %s \n\n", nom1 );
    	          exit(0);
    	        }
    	  strcpy(nom1,nom);
    	  strcat( nom1, ".ttg" );
    	  ff = fopen( nom1, "w" );
    	  if( ff == (FILE*)NULL )
    	        {
    	          printf( "\n\n No se pudo crear el archivo de salida %s \n\n", nom1 );
    	          exit(0);
    	        }
         fscanf( f, "%d", &nf );
         fscanf( f, "%d", &nr );
         for( i=0 ; i<nf ; i++ )
           for( j=0 ; j<nr ; j++ )
              {
              fscanf( f, "%f", &tt );
              MB[i][j] = (int) (tt*1000);
//                fscanf( f, "%d", &tti );
//                MB[i][j] = tti;
              }
  ordenaMB();

/* lee la matriz ordenada, se sustituyó por ordenaMB
         for( i=0 ; i<nf ; i++ )
           for( j=0 ; j<nr ; j++ )
              {
                fscanf( f, "%d", &tt );
                MO[i][j] = tt;
              }
         for( i=0 ; i<nr ; i++ )
           {
             fscanf( f, "%d", &tt );
             ni[i] = tt;
             t[i] = '0';
             p[i] = 0;
             v[i] = 0;
           }
         t[nr-1] = '1';
         p[nr-1] = ni[nr-1];
         v[nr-1] = MO[ni[nr-1]][nr-1];
*/
         fclose(f);
        }
}

void salida()
{
  int i;

//  fprintf( fs, " %3d  %s  ", nv, t );


  // con foramto Raudel
  for( i=0; i<nr ; i++ )
    {
      if( t[i]=='1' )
        {
    	  if ( v[i] >= 1000 )
    		  fprintf( fs, "1.000 " );
    		else
    		    {
    			  fprintf( fs, "0." );
    			  if( v[i] < 100 ) fprintf( fs, "0" );
    			  if( v[i] < 10 ) fprintf( fs, "0" );
    			  fprintf( fs,"%d ", v[i] );
    		    }
        }
      else
          fprintf( fs, "0 " );
    }
  fprintf( fs, "\n" );

/*
// con formato para imprimir
  fprintf( fs, "{ " );
  for( i=0; i<nr ; i++ )
      {
        if( t[i]=='1' )
          {
            fprintf( fs, "x%d/0.", i+1 );
//            if( v[i] < 100 ) fprintf( fs, "0" );
            if( v[i] < 10 ) fprintf( fs, "0" );
            fprintf( fs,"%d ", v[i] );
          }
      }
    fprintf( fs, "}\n" );
*/
  fflush(fs);

}

void escribe()
{

  int i;

  printf( " %ld  %s %d-1s ", nv, t, nunos );
  for( i=0; i<nr ; i++ )
    {
      if( t[i]=='1' )
        {
          printf( "x%d/0.", i+1 );
          if( v[i] < 10 ) printf( "0" );
          printf( "%d ", v[i] );
        }
    }
  printf ("\n               ");
  for( i=0; i<nr ; i++ )
      if( t[i]=='1' )
          printf( "  %d     ", nfc[i] );

 printf( "\n" );
 fflush(stdout);
}

/*
int nunos()
{
  int nu, i;

  nu=0;
  for( i=0 ; i<nr ; i++ ) if( t[i]=='1' ) nu++;
  return nu;
}
*/

void sig()
{
  int i;

  for( i=nr-1 ; i>=0 ; i-- )
     {
       if( (t[i] == '0') && (cz[i] == '0') )
             {
               t[i] = '1';
               break;
             }
        else t[i]='0';
     }
  for( i=0 ; i<nr ; i++ )
     {
       if( t[i] == '1' )
          {
             p[i]=ni[i];
             v[i]=MO[p[i]][i];
          }
     }

  nunos=0;
  for( i=0 ; i<nr ; i++ ) if( t[i]=='1' ) nunos++;

/*
  for( i=0 ; i<nr ; i++ )
     printf("%c",t[i]);
  printf("\n");
  fflush(stdout);
*/


  return;
}

int es_testor()
{
  int i, j, k;

  for( i=0 ; i<nr ; i++ )
    {
	  nfc[i] = 0;    // al inicio ningún rasgo cubre ninguna fila; para la redundancia
      ind[i] = 0;    // al inicio ningún rasgo es indispensable; para verificar tipicidad
    }
  /* checa si en cada fila existe un valor del testor <= que el de la fila */
  for( i=0 ; i<nf ; i++ )
    {
      for( j=0 ; j<nr ; j++ )
      {
        if( (t[j]=='1') && (v[j] < MB[i][j]) ){ nfc[j]++; break; } // Incrementa el número de filas cubiertas para el primer rasgo que cubre
                                                                   // a la fila; para la redundancia, y si de manera estricta pasa a la sig fila

        if( (t[j]=='1') && (v[j] ==MB[i][j]) ){ nfc[j]++;          // Incrementa el número de filas cubiertas para el primer rasgo que cubre
                                                                   // a la fila; para la redundancia, y si es igual checa los demás para ver si
                                                                   // es el único que cubre a la fila
                                                for( k=j+1 ; k<nr ; k++ )
                                                {
                                                	if( (t[k]=='1') && (v[k]<=MB[i][k]) ) break; // si algún otro cubre a la fila i entonces no tiene
                                                		                                         // que verificar más, j no es indispensable para esta fila
                                                }
                                                if( k == nr ) ind[j]=1;  // si ninguno otro cubre a la fila entonces el j original es indispensable
                                                break;
                                              }
      }
      if( j==nr ) return FALSE; // si ninguno cubrió a la fila i entonces t no es testor de Goldman
    } 
  return TRUE; // si todas las filas fueron cubiertas por algún rasgo entonces sí es testor
}

// igual a es_testor(), pero no cuenta las fials cubiertas, y por lo tanto al checar tipicidad no altera el conteo que se hizo al checar al condiución de testor
// con la nueva manera de verificar la tipicidad ya no se necesita esta función
int es_testor2()
{
  int i, j;

  /* checa si en cada fila existe un valor del testor <= que el de la fila */
  for( i=0 ; i<nf ; i++ )
    {
      for( j=0 ; j<nr ; j++ )
        if( (t[j]=='1') && (v[j]<=MB[i][j]) ) break;
      if( j==nr ) return FALSE;
    }
  return TRUE;
}

int es_tipico()
{
  int i, r;

/* checa la tipicidad usando las marcas de indispensable */
  for( i=0 ; i<nr ; i++ )
	 if ( (t[i]=='1') && (ind[i] == 0) ) return FALSE; // si algún rasgo no es indipensable entonces t no es típico
  return TRUE;                      // si todos fueron indispensables entonces sí es típico


/* para verificar la tipifcidad sin las marcas de indispensable
  // checa eliminado rasgo a rasgo
  for( i=0 ; i<nr ; i++ )
     if( t[i]=='1' )
         {
    	   if( nfc[i] == 0 ) return FALSE;
           t[i]='0';
           r = es_testor2();
           t[i]='1';
           if( r ) return FALSE;
         }

  // checa por superconjuntos con el mismo soporte
  for( i=0 ; i<nr ; i++ )
     if( t[i]=='1' )
         {
           if( p[i] == nf-1 ) continue;
           v[i]=MO[p[i]+1][i];
           r = es_testor2();
           v[i]=MO[p[i]][i];
           if( r ) return FALSE;
         }	
  return TRUE;
*/
}

void salto_no_testor()
{
  int i;
//, nu;

//  nu = nunos();
  if( nunos == 1 )
    {
      /* si solo es un rasgo pasa a la siguiente combinacion */
      sig();
      return;
    }

/* busca el ultimo rasgo que no tenga la minima pertenencia */
/* y le pone la minima pertenencia */
  for( i=nr-1 ; i>=0 ; i-- )
     {
       if( t[i] == '1' )
         {
           if( p[i] != ni[i] )
             {
               p[i]=ni[i];
               v[i]=MO[p[i]][i];
               break;
             }
         }
     }

/* busca el ultimo rasgo antes del que no tenia la minima pertenencia 
   que no tenga la maxima pertenencia */
/* si lo encuentra pasa a la siguiente pertenencia */
/* a los que tenian maxima les pone la minima */
  for( i=i-1 ; i>=0 ; i-- )
     {
       if( t[i] == '1' )
         {
           if( p[i] == nf-1 )
             {
               p[i]=ni[i];
               v[i]=MO[p[i]][i];
             }
           else
             {
               p[i]++;
               v[i]=MO[p[i]][i];
               break;
             }
         }
     }
  if( i >= 0 ) return;
/* si todos los rasgos estaban en la maxima pasa a la siguiente combinacion */
  sig();
}

void salto_tipico()
{
  int i;
//, nu;

//  nu = nunos();
  if( nunos == 1 )
    {
      /* si solo es un rasgo se elimina el valor minimo del mismo */
      for( i=0 ; i<nr ; i++ )
         if( t[i]=='1' )
           {
             if( ni[i] < (nf-1) ) ni[i]++;
             break;
           }
      /* y se pasa a la siguiente combinacion de rasgos */
      sig();
      return;
    }

/* busca el último rasgo que no tenga la minima pertenencia */
  for( i=nr-1 ; i>=0 ; i-- )
     if( t[i] == '1' )
       if( p[i] != ni[i] )
         {
           p[i]=ni[i];
           v[i]=MO[p[i]][i];
           break;
         }

/* busca el rasgo mas a la derecha con pertenencia menor a la maxima */
/* si lo encuentra le pone el siguiente valor de pertenencia */
/* a los rasgos de la derecha que tengan pertenenecia igual a la maxima
   les va poniendo la minima */
  for( i=i-1 ; i>=0 ; i-- )
     {
       if( t[i] == '1' )
         {
           if( p[i] == nf-1 )
             {
               p[i]=ni[i];
               v[i]=MO[p[i]][i];
             }
           else
             {
               p[i]++;
               v[i]=MO[p[i]][i];
               break;
             }
         }
     }
  if( i >= 0 ) return;
/* si todos los rasgos estaban en la maxima pasa a la siguiente combinacion */
  sig();
}

void salto_testor()
{
  int i, j, k;
  int fc;  // filas cubiertas
  int nrp; // número de rasgos procesados

/* esto no tengo idea de para qué era
  int nu;
  int vv[nr], pp[nr];

  for( i=0 ; i<nr ; i++ )
    {
      vv[i]=v[i];
      pp[i]=p[i];
    }
  for( i=nr-1 ; i>=0 ; i-- )
    if( t[i] == '1' )
      {
        p[i]=nf-1;
        v[i]=MO[nf-1][i];
        if( es_testor() )
          {
            if( es_tipico() ) return;
          }
        else
          {
            v[i] = vv[i];
            p[i] = pp[i];
          }
      }
*/

// busca el primer rasgo generador de redundancia de izquierda a derecha ; para la redundancia
  fc = 0;
  nrp = 0;
  for( k=0 ; k<nr ; k++ )
   if( t[k] == '1' )
     {
      nrp++;
	  // (caso 1) si no cubre ninguna fila el mismo es redundante y se debe disminuir su pertenencia (para que pueda cubrir algo)
	  if( nfc[k] == 0 )
	      {
  		    for( i=k-1 ; i>=0 ; i-- )
		      {
		        if( t[i] == '1' )
		         {
		           if( p[i] == nf-1 )     // busca el primero desde el generador de redundancia a la izquierda con pertenencia diferente de la máxima
		             {
		               p[i]=ni[i];        // les va poniendo la mínima a los que tenían la máxima
		               v[i]=MO[p[i]][i];
		             }
		           else
		             {
		               p[i]++;            // al primero distinto de la máxima le encrementa la pertenencia
		               v[i]=MO[p[i]][i];
		               for( j=k ; j<nr ; j++ ) // de k en adelante les pone la mínima (a los anteriores de k que tenían la máxima ya les había puesto la mínima
			             {
			               p[j]=ni[j];
			               v[j]=MO[p[j]][j];
			             }
		               return;
		             }
		         }
		      }
		    sig(); // si no pudo encontrar ninguno con pertenencia diferencte de la máxima antes de k, pasa a la siguiente combinación
		    return;
 	      }
	  // si cubre alguna fila, pero las filas que quedan por cubrir despues de este rasgo son menos que los rasgos restante
	  else
	      {
	        fc += nfc[k];
 	  	    // (caso 2) alguno de estos no cubrirá nada y se le debe aumentar la pertenencia para que pueda cubrir menos y deje más para los restantes
	        if( ((nf-fc) < (nunos-nrp-1)) || (nrp == nunos) )
	        {
	  		    for( i=k ; i>=0 ; i-- )  // el proceso es similar al anterior pero iniciando en k, si puede le aumneta la pertenencia y pone en mínima los posteriores, si no, busca hacia atras
			      {
			        if( t[i] == '1' )
			         {
			           if( p[i] == nf-1 )     // busca el primero desde el generador de redundancia a la izquierda con pertenencia diferente de la máxima
			             {
			               p[i]=ni[i];        // les va poniendo la mínima a los que tenían la máxima
			               v[i]=MO[p[i]][i];
			             }
			           else
			             {
			               p[i]++;            // al primero distinto de la máxima le encrementa la pertenencia
			               v[i]=MO[p[i]][i];
			               for( j=k+1 ; j<nr ; j++ ) // de k+1 en adelante les pone la mínima (a k y los anteriores de k que tenían la máxima ya les había puesto la mínima
				             {
				               p[j]=ni[j];
				               v[j]=MO[p[j]][j];
				             }
			               return;
			             }
			         }
			      }
			    sig(); // si k tiene la máxima y no pudo encontrar ninguno con pertenencia diferencte de la máxima antes de k, pasa a la siguiente combinación
			    return;
	        }
	      }
    }

// siemrpe se debe cumplir alguno de los casos anteriores (1 o 2) puesto que es testor no típico

  printf("\n No se cumplio ni 1 ni 2 \n");
  fflush(stdout);
  exit(0);


/* pasa al siguiente en el orden  */
/* dentro de la misma combinacion */
/*
  for( i=nr-1 ; i>=0 ; i-- )
     {
       if( t[i] == '1' )
         {
           if( p[i] == nf-1 )
             {
               p[i]=ni[i];
               v[i]=MO[p[i]][i];
             }
           else
             {
               p[i]++;
               v[i]=MO[p[i]][i];
               break;
             }
         }
     }
  if( i >= 0 ) return;

// si ya termino pasa a la siguiente combinacion
  sig();
*/
}

/*
int no_termina()
{
  int i;
  
  for( i=0; i<nr ; i++ )
    if( t[i] == '1' ) break;
  if( i == nr ) return FALSE;
return TRUE;

//  for( i=0; i<nr ; i++ )
//    if( t[i] == '1' ) { if( p[i] != nf-1 ) return TRUE; }
//      else return TRUE;
//  return FALSE;

}
*/

void gBT()
{
  nv = 0;
  nt = 0;
//  while( no_termina() )

  sig();    // para pasar a 00....01 dado que al inicio está en 00...00
  while( nunos )
    {
//       escribe();
       nv++;
       if( (nv % PUNTITO) == 0 )
       	   {
    	   	   printf(".");
    	   	   fflush(stdout);
       	   }

      if( es_testor() )
         if( es_tipico() )
              {
                nt++; 
//                printf( "TT " );
//                escribe();
                salida();
                salto_tipico(); 
              }
           else
              {
//                printf( "T  " );
//                escribe();
                salto_testor();
              }
       else
         {
//           printf( "NT " );
//           escribe();
           salto_no_testor();
         }
    }
}

int main(int argc, char *argv[])

{
  int i, j;
  char c;

  printf( "\n\n Cada puntito son %d combinaciones verificadas \n\n", PUNTITO );
  inicia(argc,argv);
/*
  // escribe la matriz de entrada
  printf( "\n Matriz basica MB de %d rasgos y %d filas\n\n", nr, nf );
  for( i=0 ; i<nf ; i++ )
    {
      for( j=0 ; j<nr ; j++ )
       {
         printf( " 0." );
         if( MB[i][j] < 100 ) printf( "0" );
         if( MB[i][j] < 10 ) printf( "0" );
         printf( "%d ", MB[i][j] );
       }
      printf( "\n" );
    }
  printf( "\n" );
*/
/*
  // escribe la matriz ordenada
  printf( "\n Matriz basica ordenada MO de %d rasgos y %d filas\n\n", nr, nf );
  for( i=0 ; i<nf ; i++ )
    {
      for( j=0 ; j<nr ; j++ )
       {
         printf( " 0." );
         if( MO[i][j] < 100 ) printf( "0" );
         if( MO[i][j] < 10 ) printf( "0" );
         printf( "%d ", MO[i][j] );
       }
      printf( "\n" );
    }
  printf( "\n" );
  for( j=0 ; j<nr ; j++ )
   {
     printf( "%6d ", ni[j] );
   }
  printf( "\n" );
  fflush(stdout);
*/

  time(&ini);
  gBT();
  time(&fin);

  printf( "\n\n %ld combinaciones verificadas ", nv );
  printf( "\n\n %ld testores difusos tipicos ", nt );
  printf( "\n\n tiempo para calcular los TTG: %lf seg \n\n", difftime(fin, ini) );
  fprintf(fs,"%c",EOF);
  fflush(fs);
  fclose (fs);

  // salida formato Raudel
  strcpy(nom1,nom);
  strcat( nom1, ".tmp" );
  f = fopen( nom1, "r" );
  if( f == (FILE*)NULL )
        {
          printf( "\n\n Error al leer el archivo temporal %s\n\n", nom );
          exit(0);
        }
//  para Raudel
   fprintf( ff, "%d %ld\n", nr, nt );

// para que sea igual al de Memo
//  fprintf( ff, "El numero de testores difusos tipicos encontrado es : %ld\n", nt );
//  fprintf( ff, "Tiempo consumido por el algoritmo :  %lf seg\n", difftime(fin, ini) );

  fscanf(f,"%c",&c);
  while(c!=EOF)
  {
    fprintf(ff,"%c",c);
    fscanf(f,"%c",&c);
  }
//  fprintf(ff, "\n\n Tamaño del espacio de búsqueda: %.0lf", tamEspacio);
//  fprintf(ff,  "\n\n Combinaciones verificadas: %ld  ", nv );
  fflush(ff);
  fclose(ff);
  fclose(f);
  return TRUE;
}
