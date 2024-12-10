
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

/*para tomar tiempo*/
time_t ini, fin;

FILE *fs;

int  nv, nt;

int   nf, nr;    // número de filas y rasgos respectivamente

int MB[100][30];

int ni[30] ;

int MO[100][30];

char t[30];
int  v[30];
int  p[30];
int  m[30];


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
  int i, j, L[30];

  for( i=0 ; i<nr ; i++ )
    {
	  for( j=0; j<nf ; j++ ) L[j] = 0;
	  for( j=0; j<nf ; j++ ) if( !esta(MB[j][i], L) ) L[j] = MB[j][i];
	  qs( L, 0, nf-1 );
	  for( j=0; j<nf ; j++ ) MO[j][i] = L[j];
    }
  for( i=0 ; i<nr ; i++ )
    {
	  for( j=0 ; j<nf ; j++ ) if( MO[j][i] != 0 ) break;
	  ni[i] = j;
	  t[i] = '0';
	  p[i] = 0;
	  v[i] = 0;
    }
  t[nr-1] = '1';
  p[nr-1] = ni[nr-1];
  v[nr-1] = MO[ni[nr-1]][nr-1];
}

void inicia(int argc, char *argv[])
{
  FILE *f;
  int   i, j, tt;
  char nom[100];
  char nom1[105];

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
    	  strcat( nom1, ".ttg" );
    	  fs = fopen( nom1, "w" );
    	  if( fs == (FILE*)NULL )
    	        {
    	          printf( "\n\n No se pudo crear el archivo de salida %s \n\n", nom1 );
    	          exit(0);
    	        }
         fscanf( f, "%d", &nr );
         fscanf( f, "%d", &nf );
         for( i=0 ; i<nf ; i++ )
           for( j=0 ; j<nr ; j++ )
              {
                fscanf( f, "%d", &tt );
                MB[i][j] = tt;
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
  for( i=0; i<nr ; i++ )
    {
      if( t[i]=='1' )
        {
          fprintf( fs, "x%d/0.", i+1 );
          if( v[i] < 100 ) fprintf( fs, "0" );
          if( v[i] < 10 ) fprintf( fs, "0" );
          fprintf( fs,"%d ", v[i] );
        }
    }
  fprintf( fs, "\n" );

  fflush(fs);
}

void escribe()
{
/*
  int i;

  printf( " %3d  %s  ", nv, t );
  for( i=0; i<nr ; i++ )
    {
      if( t[i]=='1' )
        {
          printf( "x%d/0.", i+1 );
          if( v[i] < 10 ) printf( "0" );
          printf( "%d ", v[i] );
        }
    }

*/
// printf( "\n" );
 fflush(stdout);
}

int nunos()
{
  int nu, i;

  nu=0;
  for( i=0 ; i<nr ; i++ ) if( t[i]=='1' ) nu++;
  return nu;
}

void sig()
{
  int i;

  for( i=nr-1 ; i>=0 ; i-- )
     {
       if( t[i] == '0' )
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
  return;
}

int es_testor()
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

  /* checa eliminado rasgo a rasgo */
  for( i=0 ; i<nr ; i++ )
     if( t[i]=='1' )
         {
           t[i]='0';
           r = es_testor();
           t[i]='1';
           if( r ) return FALSE;
         }

  /* checa por superconjuntos con el mismo soporte */
  for( i=0 ; i<nr ; i++ )
     if( t[i]=='1' )
         {
           if( p[i] == nf-1 ) continue;
           v[i]=MO[p[i]+1][i];
           r = es_testor();
           v[i]=MO[p[i]][i];
           if( r ) return FALSE;
         }	
  return TRUE;
}

void salto_no_testor()
{
  int i, nu;

  nu = nunos();
  if( nu == 1 )
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
  int i, nu;

  nu = nunos();
  if( nu == 1 )
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

/* busca el ultimo rasgo que no tenga la minima pertenencia */
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
  int i;

/*
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

/* pasa al siguiente en el orden  */
/* dentro de la misma combinacion */
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

/* si ya termino pasa a la siguiente combinacion */
  sig();
}

int no_termina()
{
  int i;

  
  for( i=0; i<nr ; i++ )
    if( t[i] == '1' ) break;
  if( i == nr ) return FALSE;
return TRUE;
/*
  for( i=0; i<nr ; i++ )
    if( t[i] == '1' ) { if( p[i] != nf-1 ) return TRUE; }
      else return TRUE;
  return FALSE;
*/
}

void gBT()
{
  nv = 0;
  nt = 0;
  while( no_termina() )
    {
       if( (nv % 10000) == 0 )
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
/*                printf( "T  " );
                escribe();              */
                salto_testor();
              }
       else
         {
/*           printf( "NT " );
           escribe();                  */
           salto_no_testor();
         }
      nv++;
    }
}

int main(int argc, char *argv[])

{
  int i, j;

  inicia(argc,argv);
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

  printf( "\n\n %d combinaciones verificadas ", nv );
  printf( "\n\n %d testores difusos tipicos \n\n", nt );
	printf( "\n\n tiempo para calcular los TTG: %lf seg \n\n", difftime(fin,ini));
  fclose (fs);
  return TRUE;
}
