#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
using namespace std;
//g++ poda.cpp -o poda

struct nodo{
	int pos;
	int p1;
	int p2;
};

bool EsHoja(nodo &n, int &tama){
	if(n.pos==tama-1)
		return true;
	else
		return false;
}

bool EsSolucion( nodo &n , const vector<int> &kids ){
	bool resultado = false;	
	int tama =kids.size();

//cout << "\nCOMPRUEBO NODO HOJA  pos=" << n.pos << "  p1=" << n.p1 << "  p2=" << n.p2 << endl << endl;

	/*if(n.p1 + kids[tama-1] == n.p2 || n.p1 == n.p2 + kids[tama-1] ){
		resultado = true;
	}*/
	if(n.p1 == n.p2)
		resultado=true;

	return resultado;
}

bool SePuedePodar(nodo &n ,const int &noelegidos){
	bool res=false;
	bool p1menor=false;

//cout << "intento podar pos=" << n.pos << "  p1=" << n.p1 << "  p2=" << n.p2 << "  noelegidos = " << noelegidos << endl;

	if(n.p1<=n.p2)
		p1menor=true;

	if(p1menor){
		return (n.p1+noelegidos < n.p2);
	}
	else{
		return (n.p2+noelegidos < n.p1);
	}
}



nodo CrearHijoIzquierdo(nodo &n, const vector<int> &kids){
	nodo sol;
	sol.pos=n.pos+1;
	sol.p1=n.p1+kids[sol.pos];
	sol.p2=n.p2;
	return sol;
}

nodo CrearHijoDerecho(nodo &n, const vector<int> &kids){
	nodo sol;
	sol.pos=n.pos+1;
	sol.p1=n.p1;
	sol.p2=n.p2+kids[sol.pos];
	return sol;
}

void algoritmo(nodo &n , bool &sol, const vector<int> &v , int noelegidos){
	bool podar;
//cout << " noelegidos =" << noelegidos << " le resto =" << v[n.pos] << endl ;
	noelegidos=noelegidos-v[n.pos];
	int tama=v.size();

	//cout << "pos del nodo al que se le va a aplicar el alg =" << n.pos << "  p1=" << n.p1 << "  p2=" << n.p2 << endl;

	if( !EsHoja(n,tama) && !sol){
		podar=SePuedePodar(n,noelegidos);
//if(podar)
//cout << "\n\nESTE NODO SE PODA " << endl << endl;

		if(!podar){
			if(!sol){
				nodo izq;
				izq=CrearHijoIzquierdo(n,v);
				algoritmo(izq,sol,v,noelegidos);
			}
			if(!sol){
				nodo der;
				der=CrearHijoDerecho(n,v);
				algoritmo(der,sol,v,noelegidos);
			}
		}

	}

	else if(!sol){
		sol=EsSolucion(n,v);
	}
}


int main(int argc, char * argv[]){
	
	if (argc != 2)
    {
      cerr << "Formato " << argv[0] << "<tam>" << endl;
      return -1;
    }

	bool sol=false;
	clock_t tantes, tdespues;
	vector <int> kids;
	int n=atoi(argv[1]);

	int sumatmp=0;
	for(int i=0;i<n; i++){
	int j=rand()%1000;
		sumatmp+=j;
	kids.push_back(j);
	}
	if(sumatmp%2==0){
	kids.push_back(1);}


	int noelegidos=0;

	for(int i=0 ; i<kids.size() ; i++){
		noelegidos=noelegidos+kids[i];
	}
	
	
	nodo inicial;
	inicial.pos=0;
	inicial.p1=kids[0];
	inicial.p2=0;
	
	tantes=clock();
	algoritmo(inicial,sol,kids,noelegidos);
	tdespues=clock();
	
	/*if(sol){
		cout << "\nTIENE SOLUCION\n";
	}
	else{
		cout << "\nNO TIENE SOLUCION\n";
	}*/
	
	double transcurrido = (double)(tdespues - tantes)/CLOCKS_PER_SEC;
	
	cout<<transcurrido<<endl;



}
