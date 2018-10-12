#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int>::iterator maximo (vector<int> &myvector ){

	auto itm = myvector.begin();

	for (auto it = myvector.begin() ; it != myvector.end() ; it++){
		if ( *it > *itm){
			itm = it;
		}
	}
	return itm;	
}

int main(int argc , char *argv[]){

	int suma_cal_tapas = 0;
	int suma_tapas_max = 0;
	int contador = 0 ;
	

	if( argc != 3){
		cerr << "Formato " << argv[0] << " calorias que quiere el usuario y número de tapas totales " << endl;
		return -1;
	}

	int max_cal = atoi(argv[1]);
	int num_tapas = atoi(argv[2]);
	vector<int> tapas;
	for ( int i = 0 ; i < num_tapas ; i++ )
		tapas.push_back(rand() % 900 + 100);


	for (int i = 0 ; i < num_tapas ; i++){
		suma_cal_tapas = tapas[i] + suma_cal_tapas;
	}

	if ( suma_cal_tapas < max_cal){
		cerr << "No se pueden ofrecer tantas calorias" << endl;
		return -1;
	}
	

	vector<int>::iterator itaux ;
	while ( suma_tapas_max < max_cal){
		itaux = maximo(tapas);
		suma_tapas_max = *itaux + suma_tapas_max;
		tapas.erase(itaux);
		contador++;

	}
	cout << "Número de tapas tomadas = " << contador << endl;
	cout << "Calorias totales tomadas = " << suma_tapas_max << endl;


}