#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <ctime>
using namespace std;
//g++ -O2 -std=c++11 tspbb.cpp -o tspbb

int podados=0;
int expandidos=0;
int tamamax=0;

void pintavector(vector<int> v){
for(int i=0 ; i<v.size();i++)
cout << v[i] << " ";

cout << endl << endl;
}

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

class ciudad{

	public:
	vector<int> recorrido;
	double cotainf;
	float distancia=0;
	int tama=0;

	void SetCotainf(int &c){
		cotainf=c;
	}

	int GetCotainf(){
		return cotainf;
	}
	void Insert(int &c){
		recorrido.push_back(c);
	}
	float GetDistancia(vector<vector<double>> M){
		float res=0;
		res=res+distancia+M[recorrido[0]-1][recorrido[recorrido.size()-1]-1];
		return res;
	}
	bool operator<(const ciudad &c)const{
		return (cotainf>c.cotainf);	
	}

	
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



bool esta(int j,vector<int> &v){
	bool res=false;
	for(int i=0; i<v.size() && !res ; i++){
		if(j==v[i])
			res=true;
	}
	return res;
}
double calcularMinimo(vector<double> &v){
	double min=999999;

	for(int i=0 ; i<v.size();i++){
		if(v[i]<min && v[i]!=0)
			min=v[i];
	}
	return min;
}

double CalcularCota(ciudad &c,vector<vector<double>> &M ){

	double sum=0;

	for(int i=0 ; i<M.size() ; i++)
		if (!esta(i+1,c.recorrido) || ( i+1==c.recorrido[c.recorrido.size()-1] && c.recorrido.size()!=c.tama) ){
			sum=sum+calcularMinimo(M[i]);
		}
		else{
			if(c.recorrido[c.recorrido.size()]==i){
				sum=sum+calcularMinimo(M[i]);
			}
		}
	return c.distancia+sum;
}




bool esHoja(ciudad &c, int tama){
	if(c.recorrido.size()==tama)
		return true;
	return false;
}



void expandir(ciudad &resultado, priority_queue<ciudad> &pq,vector<vector<double>> &M,double &cotaglobal){
	ciudad aux;
	int tama=resultado.recorrido.size()+1;
	for(int i=2 ; i<M.size()+1 ; i++){
		if( !esta(i,resultado.recorrido) ){

			aux.recorrido=resultado.recorrido;
			aux.recorrido.push_back(i);	
			aux.tama=resultado.tama;
			aux.distancia=resultado.distancia+M[aux.recorrido[tama-1]-1][aux.recorrido[tama-2]-1];
			aux.cotainf=CalcularCota(aux,M);
			if(aux.cotainf < cotaglobal){
				pq.push(aux);
				expandidos++;
				if(tamamax<pq.size()){
					tamamax=pq.size();
				}
			}
			else{
				podados++;
			}
			
		}
	}
}



void BranchBound(double &cotaglobal,ciudad &res, priority_queue<ciudad> &pq,vector<vector<double>> &M){
	ciudad comprobar=pq.top();
	pq.pop();
	
	if(!esHoja(comprobar,M.size()) && comprobar.cotainf<cotaglobal ){
		expandir(comprobar,pq,M,cotaglobal);
	}
	else{
		if(comprobar.cotainf<cotaglobal){
			int tama=comprobar.recorrido.size();
			comprobar.distancia=comprobar.distancia+M[comprobar.recorrido[tama-1]-1][comprobar.recorrido[0]-1];
			if(comprobar.distancia<cotaglobal){
				res=comprobar;
				cotaglobal=comprobar.distancia;
			}
		}

	}

		if(!pq.empty()){
			BranchBound(cotaglobal,res,pq,M);		
		}
}



int main(int argc, char* argv[]){

	map<int, pair<double, double> > ci;
	vector<vector<double>> Mdistancia;
	string fichero;
	vector<ciudad> resultado;
	ciudad seleccionada;
	int mejorpos;
	clock_t tantes, tdespues;

	if(argc < 2) {
		fprintf(stderr,"\nFalta nombre archivo \n");
		exit(-1);
	}
	 
	string nombre=argv[1];
	leer_puntos(nombre,ci);
	int tama=ci.size();

	CrearMatrizDistancia(Mdistancia,ci);
	int tamam=Mdistancia.size();

	ciudad padre;
	padre.recorrido.push_back(0);
	double cotaglobal=99999999;
	padre.tama=tamam;

	priority_queue<ciudad> pq;
	

	padre.cotainf=CalcularCota(padre,Mdistancia);
	padre.recorrido.clear();
	padre.recorrido.push_back(1);
	padre.distancia=0;

	/*for(int i=0 ; i<Mdistancia.size();i++){
		for(int j=0;j<Mdistancia.size();j++){
			cout << Mdistancia[i][j] << " ";
		}
	cout << endl;
	}*/

	pq.push(padre);
	ciudad res;
	
	tantes=clock();
	BranchBound(cotaglobal,res,pq,Mdistancia);
	tdespues=clock();

	double tiempo= (double)(tdespues - tantes)/CLOCKS_PER_SEC;
	
	cout<<"DIMENSION: "<<res.recorrido.size()<<endl;
	for(int i=0 ; i<res.recorrido.size(); i++){
	cout <<"\n"<<res.recorrido[i] << " ";
	}
	cout << endl << "\ndistancia =" << res.distancia << " expandidos=" << expandidos << " podados=" << podados << " tama=" << tamamax << " tiempo empleado: " << tiempo << endl;

}
