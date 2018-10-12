#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
//#include <algorithm>


//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

void pintarM( vector<vector<int> > P ){
	for(int i=0; i<P.size() ; i++){
		for(int j=0 ; j<P[0].size() ; j++){
			cout << P[i][j] << "  ";
		}
		cout << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<int> > Mezclar(vector<vector<int> > v1 , vector<vector<int> > v2){
	int contadorv1=0,contadorv2=0;
	int fil1=0,fil2=0,col1=0,col2=0;
	int fila=0,col=0;
	int tamav1=v1[0].size()*v1.size();
	int tamav2=v2[0].size()*v2.size();

	vector<vector<int> > resultado;
	resultado.resize(v1.size()+v2.size());
	for(int i=0 ; i<v1.size()+v2.size() ; i++){
		resultado[i].resize(v1[0].size());
	}

//cout << "V1 " << endl;
//pintarM(v1);
//cout << "V2 " << endl;
//pintarM(v2);
	while(contadorv1 < tamav1 && contadorv2 < tamav2 ){
		if(v1[fil1][col1] < v2[fil2][col2]){
			resultado[fila][col]=v1[fil1][col1];
			contadorv1++;
			col++;
			col1++;
			if(col == v1[fil1].size()){
				col=0;
				fila++;
			}
			if(col1 == v1[fil1].size()){
				fil1++;
				col1=0;
			}
		}

		else{
			resultado[fila][col]=v2[fil2][col2];
			contadorv2++;
			col++;
			col2++;
			if(col == v2[fil2].size()){
				col=0;
				fila++;
			}
			if(col2 == v2[fil2].size()){
				fil2++;
				col2=0;
			}

		}

	}

//cout << "resultado despues de primera pasada " << endl;
//pintarM(resultado);
//cout << "\n";
	if(contadorv1!=tamav1){
		
		for(int i=contadorv1 ; i<tamav1 ; i++){
			resultado[fila][col]=v1[fil1][col1];
			col++;
			col1++;
			if(col == v1[fil1].size()){
				col=0;
				fila++;
			}
			if(col1 == v1[fil1].size()){
				fil1++;
				col1=0;
			}
		}
	}
	else if (contadorv2!=tamav2){
		for(int i=contadorv2 ; i<tamav2 ; i++){
			resultado[fila][col]=v2[fil2][col2];
			col++;
			col2++;
			if(col == v2[fil2].size()){
				col=0;
				fila++;
			}
			if(col2 == v2[fil2].size()){
				fil2++;
				col2=0;
			}
		}	
	}
//cout << "resultado despues de SEGUNDA pasada " << endl;
//pintarM(resultado);
//cout << "\n\n\n";
	return resultado;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int> > mezclarVectores(vector<vector<int> > &T){
	if(T.size()>1){
		int medio=0;
		vector<vector<int> > mitadSup;
		vector<vector<int> > mitadInf;
		bool impar;

		if(T.size()%2 == 0){
			impar=false;
			medio=(T.size()/2);
			for(int i =0 ; i<medio ; i++){
				mitadSup.push_back(T[i]);
			}
			for(int i =medio ; i<T.size() ; i++){
				mitadInf.push_back(T[i]);
			}
//cout << "\n\n\nmitad SUP con fil = " << medio<< " Y col = " << T[0].size() << "\n";
//pintarM(mitadSup);
//cout << "\n\n\nmitad INF confil = " << medio<< " Y col = " << T[0].size() << "\n";
//pintarM(mitadInf);
			mitadSup=mezclarVectores(mitadSup);
			mitadInf=mezclarVectores(mitadInf);
		}
		else{
			impar=true;
			medio=T.size()/2;
			for(int i =0 ; i<medio+1 ; i++){
				mitadSup.push_back(T[i]);
			}
			for(int i =medio+1 ; i<T.size() ; i++){
				mitadInf.push_back(T[i]);
			}
//cout << "\n\n\nmitad SUP con fil = " << medio+1<< " Y col = " << T[0].size() << "\n";
//pintarM(mitadSup);
//cout << "\n\n\nmitad INF con fil = " << medio<< " Y col = " << T[0].size() << "\n";
//pintarM(mitadInf);
			mitadSup=mezclarVectores(mitadSup);
			mitadInf=mezclarVectores(mitadInf);
		}
		vector<vector<int> > resultado;
		if(impar){
			resultado=Mezclar(mitadSup,mitadInf);
		}
		else{
			resultado=Mezclar(mitadSup,mitadInf);
		}

		return resultado;
	}

	else{
		return T;		
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


int **T;
T =  new int * [k];
  assert(T);

 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
  assert(aux);

srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;

//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
for (int i=0; i<k; i++) {
   int t=0;
   int m=0;
   while (m<n) {
    double u=uniforme();
    if ((N-t)*u >= (n-m)) t++;
    else {
        T[i][m]=aux[t];
	t++;
	m++;
    }
  }
}
vector<vector<int> > matriz;
vector<int> Aux;
delete [] aux;
for (int i=0; i<k; i++) {
	for (int j=0; j<n; j++){
		Aux.push_back(T[i][j]);
	}
	matriz.push_back(Aux);
	Aux.clear();
}

//pintarM(matriz);

//cout << " \n AHORA EL METODO : \n\n" << endl;

vector<vector<int> > resultado;
clock_t tantes, tdespues;

tantes=clock();
resultado=mezclarVectores(matriz);
tdespues=clock();

double transcurrido = (double)(tdespues - tantes)/CLOCKS_PER_SEC;

cout<<transcurrido<<endl;

//cout << "El resultado es = " << endl;
//pintarM(resultado);



} 
