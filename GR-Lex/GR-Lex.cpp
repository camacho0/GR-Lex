//en esta version cambiaremos el uso de vectores
//por arreglos fijos
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
//variables globales
int nf;//numero de filas de la matriz
int nc;//numero de caracteristicas 
double **BM; //matriz basica
double **ord; //matriz ordenada
double ***Matrices;//matrices ordenadas
int Numreductos=0; //numero de reductos
double Verificadas=0; //numero de combinaciones verificadas
bool Contribuye; //indica si una combinacion contribuye
bool Reducto; //indica si es reducto
int *Indices; //indices de la combinacion
double *Grados; //grados de pertenencia
int UltimoI; //ultimo indice agregado
double UltimoG; //ultimo grado agregado
int *FilasG; //guardamos filas revisadas 
int **Filas;//filas para cada caracteristica
int TamF; //tamano de FilasG diferentes de 0
int *Aux; //guardamos las filas revisadas
bool Condicion3;
bool Condicion1;
int num_ind; //tamano de la combinacion
time_t ini,fin; //para tomar tiempo
ofstream fich;
int restantes=0;


//funcion de lectura
void Lectura(string& nombre){
	ifstream archivo(nombre);

	if (!archivo.is_open()) {
  	cout<< "Error al abrir el archivo: " << nombre <<endl;
    return ;
  }
	//leemos la dimension de la matriz
	archivo >> nf >> nc;
	//asignamos memoria
	//matriz basica
	BM= new double*[nf];
	Filas=new int*[nf];
	for(int i=0;i<nf;i++){
		BM[i]=new double[nc];
		Filas[i]=new int[nc];
	}
	for(int i=0; i<nf;i++){
		for(int j=0;j<nc;j++){
			Filas[i][j]=-1;
		}
	}


	//asignamos memoria para las matrices ordenadas
	Matrices=new double**[nc];
	for(int k=0;k<nc;k++){
		Matrices[k]=new double*[nf];
		for(int i=0;i<nf;i++){
			Matrices[k][i]=new double[nc];
		}
	}
	//arreglos auxiliares 
	//de indices y grados
	Indices=new int[nc];
	Grados=new double[nc];
	for(int i=0;i<nc;i++){
		Indices[i]=nf;
		Grados[i]=nf;
	}
	FilasG=new int[nf];
	Aux=new int[nf];
	for(int i=0;i<nf;i++){
		FilasG[i]=0;
		Aux[i]=1;
	}

	//leemos los datos de la matriz
	for(int i=0;i<nf;i++){
		for(int j=0;j<nc;j++){
			archivo >> BM[i][j];
		}
	}
}

//funcion que ordena
void Ordena(){
	double temp; //valor temporar
	double** artemp;
	int k;
	//reservamos memoria 
	ord= new double*[nf];
	artemp=new double*[nf];
	for(int i=0;i<nf;i++){
		ord[i]=new double[nc];
		artemp[i]=new double[nc];
	}
	//rellenamos ord de 0
	for(int i=0;i<nf;i++){
		for(int j=0;j<nc;j++){
			ord[i][j]=0;
			artemp[i][j]=BM[i][j];
		}
	}
	//ordenamos columna por columna
	//almacenamos en artemp
	for(int j=0;j<nc;j++){
		for(int i=0;i<nf;i++){
			for(int k=i+1;k<nf;k++){
				if(artemp[i][j]<artemp[k][j]){
					temp=artemp[i][j];
					artemp[i][j]=artemp[k][j];
					artemp[k][j]=temp;
				}
			}
		}
	}

	//copiamos temp a ord
	for(int j=0;j<nc;j++){
		ord[0][j]=artemp[0][j];
		k=1;
		for(int i=1;i<nf;i++){
			if(artemp[i][j]<artemp[i-1][j]){
				ord[k][j]=artemp[i][j];
				 k++;
				}
			}
		}
	
}


//funcion que checa si hay minimos 
//si no hay 0 en una caracteristica 
//el minimo grado de ella es reducto
void Minimos(){
	bool zero;
	for(int j=0;j<nc;j++){
		zero=true;
		for(int i=0;i<nf;i++){
			if(BM[i][j]==0){
				zero=false;
			}
		}
		if(zero){
			for(int k=nf-1;k>0;k--){
				if(ord[k][j]!=0){
					ord[k][j]=0;
					Numreductos++;
					break;
				}
			}
		}
	}

}

//imprime cadena

string Cadena(){
	string salida="";
	for(int i=0;i<nc;i++){
		if(Indices[i]!=nf){
			salida+="X"+to_string(Indices[i]+1)+"/"+
							to_string(Grados[i])+",";
		}
	}
	return salida;
}

//esta funcion checara si contribuye
//y si es reducto en caso afirmativo
void Evaluacion(int* Guardadas){
	 num_ind=0;//contara el numero de indices != nf
	int k;// axuliar
	int h=0; //otro auxiliar 
	int f=0; //para las filas
	int c,i,j,l;
	restantes=0;
	Contribuye=false;
	Reducto=false;
	//para verificar el tam\~no de la combinacion 
	for(i=0;i<nc;i++){
		if(Indices[i]!=nf){
			num_ind++;
		}
	}
	//arreglo auxiliar por si no contribuye regresar a las originales
	int aux[nf];
	for(i=0;i<nf;i++){
		aux[i]=Guardadas[i];
	}
	for(i=0;i<nf;i++){
		if(Guardadas[i]==1){continue;}
		else{
		if(BM[i][UltimoI]==UltimoG ){
			k=0;
			for(j=0;j<UltimoI;j++){
				if(Indices[j]!=nf && (BM[i][Indices[j]]>=Grados[j]) ){
							break;
						}
				else if(Indices[j]!=nf){k++;
				}
			}
			if(k==num_ind){Contribuye=true;aux[i]=1;Filas[f][UltimoI]=i;f++;}
		}
		else if(BM[i][UltimoI]>= UltimoG ){aux[i]=1;}
	}
	}

	if(Contribuye){
		Indices[UltimoI]=UltimoI;
		Grados[UltimoI]=UltimoG;
		num_ind++;
		for(i=0;i<nf;i++){
			Guardadas[i]=aux[i];
			if(Guardadas[i]==0){restantes++;}
		}
		c=0;
		for(j=0;j<UltimoI;j++){
			if(Grados[j]!=nf){
			c++;
			for(i=0;i<nf;i++){
				if(Filas[i][j]==-1){break;}
				else{
					k=0;
					for(l=j+1;l<UltimoI+1;l++){
						if((BM[Filas[i][j]][l]<Grados[l])&& (Grados[l]!=nf )){
							k++;
						}
					}
					if(k==(num_ind)-c){h++;break;}
				}
			}
			}
		}
		if(h==num_ind-1 && restantes==0){
			Reducto=true;
		}
	}
}

void Retorna(int *Guardadas, int *aux ){
	for(int i=0;i<nf;i++){
			Guardadas[i]=aux[i];
	}
}
void Zero(int n){
	for(int i=0;i<nf;i++){
		Filas[i][n]=-1;
	}
}
//funcion principal
void Lex(int n,int *Guardadas){
	int aux[nf];

	for(int w=0;w<nf;w++){
		aux[w]=Guardadas[w];
	}
	if(n==nc){
		return;
	}
	else{
		for(int i=0;i<nf;i++){
			if(ord[i][n]!=0){
					UltimoI=n;
					UltimoG=ord[i][n];
					Evaluacion(Guardadas);
					if(Contribuye){
						Verificadas++;
						if(Reducto){Numreductos++;
						//cout<<Cadena()<<endl;
						}
						else{Lex(n+1,Guardadas);}
						Indices[n]=nf;
						Grados[n]=nf;
						Zero(n);
					Retorna(Guardadas,aux);
				}
			}
		}
		Lex(n+1,aux);
	}
}


int main(){
	string name;
	cout<<"Dame el nombre del archivo: "<<endl;
	cin>>name;
	Lectura(name);
	fich.open("renewnord_"+name);
	Ordena();
	Minimos();
	int Guardadas[nf];
	for(int i=0;i<nf;i++){
		Guardadas[i]=0;
	}
	
	
	time(&ini);
	Lex(0,Guardadas);
	time(&fin);
	
	fich.close();

	cout<<"numero de combinaciones verificadas: "<< Verificadas<<endl;
	printf("Tiempo para calcular los TTG: %lf seg \n",difftime(fin,ini));
	cout<<"numero de reductos encontrados: "<<Numreductos<<endl;
	return 0;
}
