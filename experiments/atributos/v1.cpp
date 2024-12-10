//esta es la version 1.5
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <time.h>


using namespace std;

//declaramos las variables grobales
vector<vector<double>> bm;
vector<vector<double>> ord;
vector<int> indi_zero;//indices de atributos con zero
vector<int> no_zero;//indices de atributos sin zero
//vector<double>grados;//grados de pertenecia
vector<double> minimos;//las petencias minimas
vector<string> Reductos;//para guardar reductos
int verificadas=0; //numero de combinaciones verificadas

/* para tomar los tiempos */
time_t ini, fin;


vector<vector<double>> Lectura(string name){
	cout<<"lectura"<<name<<endl;
   ifstream archivo(name); // Abre el archivo
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << std::endl;
     //   return 1;
    }

    vector<vector<double>> matriz;

    string linea;
    while (getline(archivo, linea)) {
        vector<double> fila;
        istringstream ss(linea);
        double valor;
        while (ss >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }

    archivo.close(); // Cierra el archivo

    // Mostrar la matriz leída
		/*
    for (const auto& fila : matriz) {
        for (const auto& valor : fila) {
            cout << valor << ' ';
        }
        cout << '\n';
    }
		*/

    return matriz;
}

vector<vector<double>> Elimina(vector<vector<double>> ord){
	vector<vector<double>> temp;
	int n=ord.size();
	int m=ord[0].size();
	
	for(int i=0; i<n; i++){
		vector<double> fila;
		for(int j=1; j<m; j++){
			fila.push_back(ord[i][j]);
		}
		temp.push_back(fila);
	}
	return temp;
}

void SplitString(const string& str, char delimiter, vector<string>& result) {
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    // Agregar la última parte de la cadena
    result.push_back(str.substr(start));
}

string BorraU(string cadena){
	vector<string> partes;
	string temp;
	char c='/';
	SplitString(cadena,c,partes);
	for(int i=0;i<partes.size()-1;i++){
		temp+=partes[i]+"/";
	}
	return temp;
}


//compardor
bool Descendente(double a, double b){
	return a>b;
}

//ordena la matriz
void Ordena(){
	int m=ord[0].size();
	double ant;
	int j,k;
	for(int i=0;i<m;i++){
		vector<double> columna;
		for(int j=0; j<ord.size();j++){
			columna.push_back(ord[j][i]);
		}
		sort(columna.begin(),columna.end(),Descendente);

		ant=2;
		j=0;
		k=0;
		while(j<ord.size()){
			if(columna[j] != ant){
				ord[k][i]= columna[j];
				ant=columna[j];
				j+=1;
				k+=1;
			}
			else{j+=1; }
		}
		while(k<ord.size()){
			ord[k][i]=0;
			k++;
		}
	}
}

bool Is_Zeros(){
	bool zero=false;
	for(int i=0; i<bm.size(); i++){
		for(int j=0;j<bm[0].size();j++){
			if(bm[i][j]==0){
				zero=true;
				break;
			}
		}
	}
	return zero;
}

void Ind_zeros(){
	for(int j=0;j<bm[0].size();j++){
		for(int i=0;i<bm.size();i++){
			if(bm[i][j]==0){
				indi_zero.push_back(j);
				break;
			}
		}
	}
}

//aqui guardaremos las pertenecias minimas 
//de cada caracteristica
void Minimos(vector<double>& minimos){
	int k=0;
	if(!Is_Zeros()){
		for(int j=0;j<ord[0].size();j++){
			for(int i=ord.size()-1;i>0;i--){
				if(ord[i][j]!=0){
					minimos.push_back(ord[i][j]);
					ord[i][j]=0;
					break;
				}
			}
		}
	}
	else{
		Ind_zeros();
		for(int j=0;j<ord[0].size();j++){
			if(j!=indi_zero[k]){
				for(int i=ord.size()-1;i>0;i--){
					if(ord[i][j]!=0){
						minimos.push_back(ord[i][j]);
						ord[i][j]=0;
						break;
					}
				}
			}
			k++;
		}
		cout<<minimos.size()<<endl;
	}
}
//funciones necesarias para verificar propiedades
//checamos si contribuye una caracteristica
bool Contribuye( vector<int> indices,vector<double> grados, int ni, double mui){
	//cout<<"contribuye: ";
	int k;
	if(indices.empty() && grados.empty()){
		//cout<<"true vacio"<<endl;
		return true;
	}
	else{
		for(int i=0; i<bm.size();i++){
			//cout<<i<<endl;
			if(bm[i][ni]==mui){
				k=0;
				for(int j=0; j<indices.size(); j++){
					if(bm[i][indices[j]]<grados[j]){
						k++;
					}
				}
				if(k==indices.size()){
					//cout<<"true"<<endl;
					return true;
				}
				else{
					//cout<<"false"<<endl;
					continue;
					//return false;
				}
			}
		}
		return false;
	}
}

//queca si es reducto

bool Es_reducto(vector<int> indices, vector<double> grados){
	//cout<<"reducto"<<endl;
	bool c=true;
	int count;
	int cart=0;
	int filas=0;
	int nf=bm.size();
	int nc=indices.size();
	int atri=0;
	vector<int> temp=indices;
	//checo condicion 1
	for(int i=0; i<nf; i++){
		for(int j=0; j<nc;j++){
			if(bm[i][indices[j]]>= grados[j]){
				filas++;
				break;
			}
		}
	}
	if(filas!=bm.size()){
		c=false;
	}
	//si cumple la 1
	//checo la 3
	//cout<<"c:"<<c<<endl;
	if(c){
		//cout<<"condicion 3"<<endl;
		for(int k=0; k<indices.size();k++){
			for(int i=0; i<bm.size();i++){
				if(bm[i][indices[k]]==grados[k]){
					count=0;
					for(int j=0; j<indices.size();j++){
						if(j!=k && bm[i][indices[j]]<grados[j]){
							count++;			
						}
					}
					if(count==(indices.size()-1)){
						atri++;
						break;
					}
				}
			}
		}
	}
//	cout<<"atri:"<<atri<<endl;
	if(atri==indices.size() && c){
	//	cout<<"es reducto"<<endl;
		return true;
	}
	else{
		//cout<<"no es reducto"<<endl;
		return false;
	}
}


void Print_vector(vector<int> indices){
	for(int i=0; i<indices.size();i++){
		cout<<indices[i]<<",";
	}
	cout<<endl;
}

void Print_vector(vector<double> indices){
	for(int i=0; i<indices.size();i++){
		cout<<indices[i]<<",";
	}
	cout<<endl;
}
void Print_vector(vector<string> indices){
	for(int i=0; i<indices.size();i++){
		cout<<indices[i]<<endl;
	}
}

void Print_minimos(vector<double> minimos){
	if(minimos.size()==0){
		cout<<" "<<endl;
	}
	else{
		int k=0;
		int i=0;
		int c=0;
		while(i<bm[0].size()){
			if(i==indi_zero[k]){
				k++;
				i++;
			}
			else{
				cout<<"X"+to_string(i+1)+"/"+to_string(minimos[c])<<endl;
				i++;
				c++;
			}
		}
	}
}

//cambiaremos dm,bm,indices,grados
void Lex(int n,string cadena,vector<int> indices, vector<double> grados){
	//cout<<"Lexdd"<<endl;
	string temp;
	temp=cadena;
	vector<vector<double>> mb;
	cadena += "X"+ to_string(n+1)+"/";
	if(n==bm[0].size()-1){
		for(int i=0; i<ord.size(); i++){
			if(ord[i][n]!=0){
				//cout<<cadena<<dm[i][0]<<endl;
				if(Contribuye(indices,grados,n,ord[i][n])){
					//cout<<"contribuye"<<endl;
					verificadas++;
					grados.push_back(ord[i][n]);
					indices.push_back(n);
					temp=cadena;
					temp+= to_string(ord[i][n])+",";
					//cout<<temp<<endl;
					if(Es_reducto(indices,grados)){
						//cout<<"Reducto"<<endl;
						Reductos.push_back(temp);
					}
					indices.pop_back();
					grados.pop_back();
				}
				/*
				else{
					cout<<"no con u"<<endl;
				}
				*/
			}
		}
	}
	else{
		//mb=Elimina(dm);
		for(int i=0;i<ord.size();i++){
			if(ord[i][n]!=0){
				//cout<<cadena<<dm[i][0]<<endl;
				if(Contribuye(indices,grados,n,ord[i][n])){
					//cout<<"contribuye"<<endl;
					verificadas++;
					cadena+=to_string(ord[i][n])+",";
					indices.push_back(n);
					grados.push_back(ord[i][n]);
				//	cout<<cadena<<endl;
					if(Es_reducto(indices,grados)){
						//cout<<"Reducto"<<endl;
						Reductos.push_back(cadena);
						//continue;
					}
					else{
						Lex(n+1,cadena,indices,grados);
					}
					indices.pop_back();
					grados.pop_back();
				}
				/*
				else{
				//	cout<<"no contribuye"<<endl;
					continue;
				}
				*/
			}//acaba if
			cadena=BorraU(cadena);
		}

		Lex(n+1,temp,indices,grados);
	}
}

void Imprimir(vector<vector<double>> dm){
	int n=dm.size();//filas
	int m=dm[0].size();//columnas

	for(int i=0; i<n;i++){
		for(int j=0; j<m;j++){
			cout<<dm[i][j]<<",";
		}
		cout<<endl;
	}
}


int main(){
	vector<double> minimos;//las petencias minimas
	vector<int> indices;//indices de la lista
	vector<double> grados;//grados de pertenecia
	//vector<int> indices={0,1,2,3};//indices de la lista
	//vector<double> grados={0.14,0.040,0.080,0.080};//grados de pertenecia

	string name;
//	cout<<"Dame el nombre del archivo: ";
	cin>> name;
	cout<<"name:"<<name<<endl;

//	cout<<"lectiura"<<endl;
	bm=Lectura(name);
	//bm=Lectura("iris.txt");
//	bm=Lectura("p1.txt");
	cout<<endl;
	//cout<<Es_reducto(indices,grados)<<endl;

	ord=bm;
	Ordena();
	Minimos(minimos);
//	Imprimir(ord);

	
	time(&ini);
	Lex(0,"",indices,grados);
	time(&fin);

	cout<<"Numero de combinaciones verificadas:"<<verificadas<<endl;
	printf( "Tiempo para calcular los TTG: %lf seg \n\n", difftime(fin, ini) );
	cout<<"Reductos encontrados: "<<Reductos.size()+minimos.size()<<endl;
//	cout<<"reductos:"<<endl;
//	Print_vector(Reductos);
//	Print_minimos(minimos);
	return 0;
}
