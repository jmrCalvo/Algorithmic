#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void leer_puntos(string & nombre, map<int, pair<double, double> > & M){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    
    
    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    int i=0;
    while (i<n) {
        datos >> act >> p.first >> p.second;
	M[act] = p;
	i++;
      }
       
    datos.close();
    }
   else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
 }

struct ciudad{
	double x;
	double y;
	int id;
};

void CrearMatrizDistancia( vector<vector<double>> &M ,map<int, pair<double, double> > & M2 ){
	vector<double> aux;

	for(auto it=M2.begin() ; it!=M2.end() ; it++){
		for(auto it2=M2.begin() ; it2!=M2.end() ; it2++){
			aux.push_back( sqrt( pow((*it).second.first-(*it2).second.first,2)+pow((*it).second.second-(*it2).second.second,2) ) );
		}
	M.push_back(aux);
	aux.clear();
	}
}

float ObtenerDistanciaTotal(vector<ciudad> &v,vector<vector<double>> M){
	float res;
	for(int i=1 ; i<v.size();i++){
		res=res+M[v[i].id][v[i-1].id];
	}
	res=res+M[v[0].id][v[v.size()-1].id];
	return res;
}

bool MatrizNula ( vector<vector<double>> &M ){

	bool resultado = true;

	for (int i = 0 ; i < M.size(); i++ ){
		for (int j = 0 ; j < M.size(); j++){
		
			if(M[i][j] != 0)
				resultado = false;

		}
	}

	return resultado;
}


double MinimoVector ( vector<double> &V , int &posicion){



	double minimo=V[0];
	int j=1;
	while(minimo==0 && j<V.size()){
		minimo=V[j];
		j++;

	}
		j--;
		posicion=j;
	
	for ( int i = j ; i < V.size() ; i++){
		if(minimo>V[i] && V[i]!=0){	
 			minimo = V[i];
			posicion = i;
		}		
	}

	return minimo;
}

void CopiaVectores ( vector<double> &V , vector<vector<double>> &M , int &posicion ){

	
	
	for ( int i = 0 ; i < M.size() ; i++){
		V.push_back(M[posicion][i]);
		
	}



}



void AnularColumna (vector<vector<double>> &M , int &posicion ){

	
	for (int i = 0 ; i < M.size(); i++ ){
			M[i][posicion] = 0 ;	
	}

}


void CopiaMatrices ( vector<vector<double>> &A , vector<vector<double>> &B){

	vector<double> aux;

		for (int i = 0 ; i < A.size(); i++ ){
			for (int j = 0 ; j < A.size(); j++){
				aux.push_back(A[i][j]);
		}
		B.push_back(aux);
		aux.clear();
	}



}
void Greedy( vector<double> &N ,vector<vector<double>> &CopiaM , double &distancia_total , int &posicion ,
 int posicion_inicial , vector<vector<double>> M , vector<int> &ciudades ){

double distancia_menor;// distancia de una ciudad a otra (la minima)



	AnularColumna(CopiaM,posicion);
	

if ( !MatrizNula(CopiaM) ){

	
	
	CopiaVectores( N , CopiaM , posicion );
	distancia_menor = MinimoVector(N,posicion);
	ciudades.push_back(posicion);



	/*cout << " -------------------------MATRIZ COPIAM -------------------------------"<< endl;
	for ( int i = 0 ; i < CopiaM.size() ; i++){
		for  (int j = 0 ; j< CopiaM.size() ; j++){
			cout << CopiaM[i][j]<< "  ";
		}
		cout << endl;
	}
	*/
	
	distancia_total = distancia_menor + distancia_total;
	N.clear();
	Greedy( N , CopiaM , distancia_total , posicion  , posicion_inicial , M , ciudades);



}else {

	distancia_total = distancia_total + M[posicion][posicion_inicial];
	
	
}


}

int main(int argc, char* argv[]){
	
	//Variables necesarias para el algoritmo greedy:
	vector<double> N;
	double distancia_total;
	int posicion_inicial;
	vector<int> ciudades;
	

	string fichero;

	fichero = argv[1];
	vector<vector<double>> M;
	vector<vector<double>> CopiaM;
	vector<double> ResultadosGreedy; // vector que almacenara la suma total empezando por las distintas ciudades del algoritmo greedy
	map<int, pair<double, double> >  M2;
	double resultado = 0;

	leer_puntos( fichero , M2 );
	CrearMatrizDistancia(M,M2);

	
for ( int i = 0 ; i < M2.size() ; i++ ){  // que empiece por la ciudad 0 y haga el algoritmo empezando por todas las ciudades
	posicion_inicial=i;
	distancia_total=0;
	int tmp=i;
	CopiaM.clear();
	CopiaMatrices( M , CopiaM );
	posicion_inicial=i;
	Greedy(N,CopiaM,distancia_total,tmp,posicion_inicial,M,ciudades);
	ResultadosGreedy.push_back(distancia_total);

}
	
	CopiaM.clear();
	CopiaMatrices( M , CopiaM );
	resultado = MinimoVector(ResultadosGreedy , posicion_inicial);
	ciudades.clear();
	ciudades.push_back(posicion_inicial);

	

	Greedy(N,CopiaM,distancia_total,posicion_inicial,posicion_inicial,M,ciudades);
	cout<<"DIMENSION: "<<ciudades.size()<<endl;
	for ( int i = 0 ; i < ciudades.size() ; i++)
		cout <<"\n"<<ciudades[i] +1  << "  " ;	
	cout << "\n Distancia de recorrido =  " << resultado << endl;
}
