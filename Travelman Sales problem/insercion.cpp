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

float Distancia(ciudad c1 , ciudad c2){
	return sqrt( pow(c1.x-c2.x,2)+pow( c1.y-c2.y,2) ) ;
}

float ObtenerDistanciaTotal(vector<ciudad> &v,vector<vector<double>> M){
	float res;
	for(int i=1 ; i<v.size();i++){
		res=res+M[v[i].id-1][v[i-1].id-1];
	}
	res=res+M[v[0].id-1][v[v.size()-1].id-1];
	return res;
}

void RecorridoParcial(vector<ciudad> &res , map<int, pair<double, double> > & M2 ){
	ciudad norte,este,oeste;
	auto it=M2.begin();
	norte.x=(*it).second.first;
	norte.y=(*it).second.second;
	norte.id=(*it).first;
	este.x=(*it).second.first;
	este.y=(*it).second.second;
	este.id=(*it).first;
	oeste.x=(*it).second.first;
	oeste.y=(*it).second.second;
	oeste.id=(*it).first;

	for(it=M2.begin() ; it!=M2.end() ; it++){
		if( (*it).second.second > norte.y ){
			norte.x=(*it).second.first;
			norte.y=(*it).second.second;
			norte.id=(*it).first;
		}
		else if( (*it).second.first > oeste.x ){
			oeste.x=(*it).second.first;
			oeste.y=(*it).second.second;
			oeste.id=(*it).first;
		}
		else if( (*it).second.first < este.x ){
			este.x=(*it).second.first;
			este.y=(*it).second.second;
			este.id=(*it).first;
		}
	}

	res.push_back(norte);
	res.push_back(oeste);
	res.push_back(este);
	M2.erase(norte.id);
	M2.erase(este.id);
	M2.erase(oeste.id);
	
}

int DistanciaMejorPosicion(vector<ciudad> &v,vector<vector<double>> &M, ciudad c ){
	float dactual=ObtenerDistanciaTotal(v,M);
	float dbase=dactual;
	float dtmp=dactual;
	dactual=dactual-Distancia(v[0],v[v.size()-1])+( Distancia(v[0],c) + Distancia(v[v.size()-1],c) );

	int mejor=0;
	for(int i=1 ; i<v.size() ; i++){
		dtmp=dtmp-Distancia(v[i],v[i-1])+( Distancia(v[i-1],c) + Distancia(v[i],c) );
		if(dtmp<dactual){
			dactual=dtmp;
			mejor=i;
		}
		dtmp=dbase;
	}
	return dactual;
	
}

ciudad SeleccionarCiudad(vector<ciudad> &v ,map<int, pair<double, double> > &ci ,vector<vector<double>> &dist){
	map<int, pair<double, double> >::iterator it = ci.begin();
	ciudad ctmp,city;
	ctmp.x=(*it).second.first;
	ctmp.y=(*it).second.second;
	ctmp.id=(*it).first;
	it++;
	float dtmp=DistanciaMejorPosicion(v,dist,ctmp);
	float d;


	for(it ; it!=ci.end() ; it++){
		city.x=(*it).second.first;
		city.y=(*it).second.second;
		city.id=(*it).first;
		d=DistanciaMejorPosicion(v,dist,city);
		if( d < dtmp){
			dtmp=d;
			ctmp=city;
		}
	}

	ci.erase(ctmp.id);
	return ctmp;
}



int MejorPosicion(vector<ciudad> &v,vector<vector<double>> &M, ciudad c ){
	float dactual=ObtenerDistanciaTotal(v,M);
	float dbase=dactual;
	float dtmp=dactual;
	dactual=dactual-Distancia(v[0],v[v.size()-1])+( Distancia(v[0],c) + Distancia(v[v.size()-1],c) );

	int mejor=0;
	for(int i=1 ; i<v.size() ; i++){
		dtmp=dtmp-Distancia(v[i],v[i-1])+( Distancia(v[i-1],c) + Distancia(v[i],c) );
		if(dtmp<dactual){
			dactual=dtmp;
			mejor=i;
		}
		dtmp=dbase;
	}
	return mejor;
	
}

void insertarCiudad(vector<ciudad> &v , ciudad c , int pos){
	ciudad tmp=v[pos];
	ciudad tmp2;
	v[pos]=c;
	for(int i=pos+1 ; i<v.size() ; i++){
		tmp2=v[i];
		v[i]=tmp;
		tmp=tmp2;
	}
	v.push_back(tmp);
}

int main(int argc, char* argv[]){

	map<int, pair<double, double> > ci;
	vector<vector<double>> Mdistancia;
	string fichero;
	vector<ciudad> resultado;
	ciudad seleccionada;
	int mejorpos;
	

	if(argc < 2) {
		fprintf(stderr,"\nFalta nombre archivo \n");
		exit(-1);
	}
	 
	string nombre=argv[1];
	leer_puntos(nombre,ci);
	int tama=ci.size();

	CrearMatrizDistancia(Mdistancia,ci);
	RecorridoParcial(resultado,ci);

	 

		while( resultado.size() != tama ){
			seleccionada=SeleccionarCiudad(resultado,ci,Mdistancia);
			mejorpos=MejorPosicion(resultado,Mdistancia, seleccionada );
			insertarCiudad(resultado,seleccionada,mejorpos);
		}
	
	cout << "DIMENSION: " << resultado.size() << endl;
	for(int i=0 ; i<resultado.size() ; i++){
		cout <<"\n"<<resultado[i].id << " ";
	}
	cout << "\n Distancia de recorrido = "<<ObtenerDistanciaTotal(resultado,Mdistancia) << endl;
	
	
}

