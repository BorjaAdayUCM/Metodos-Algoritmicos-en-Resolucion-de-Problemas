#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Objeto {
	double peso, valor;
	bool operator<(Objeto const& otro) const {
		return otro.valor / otro.peso < valor / peso;
	}
};

struct Nodo {
	int k;
	double peso1; // peso acumulado cara 1
	double peso2; // peso acumulado cara 2
	double beneficio; // valor acumulado
	double beneficio_optimista; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_optimista > beneficio_optimista;
	}
};

// estrategia voraz, para calcular la estimación

void cota_optimista(vector<Objeto> const& objetos, double M, Nodo const& X, double& optimista) {
	//Cota optimista
	double hueco = 2 * M - X.peso1 - X.peso2;
	optimista = X.beneficio;
	int i = X.k + 1;

	//Mientras queden canciones y quepan entereas las seleccionamos.
	while (i < objetos.size() && objetos[i].peso <= hueco) {
		hueco -= objetos[i].peso;
		optimista += objetos[i].valor;
		++i;
	}

	//Si quedan canciones lleno el hueco con el trozo de cancion que queda.
	if (i < objetos.size()) {
		optimista += (hueco / objetos[i].peso) * objetos[i].valor;
	}
}

void cota_pesimista(vector<Objeto> const& objetos, double M, Nodo const& X, double& pesimista) {

	//Cota pesimista
	double hueco1 = M - X.peso1, hueco2 = M - X.peso2;
	pesimista = X.beneficio;
	int i = X.k + 1;
	
	//Mientras queden canciones y quede hueco en alguna de las caras.
	while (i < objetos.size() && (hueco1 > 0 || hueco2 > 0)) {
		//Si cabe en la cara1 lo pongo en la 1.
		if (objetos[i].peso <= hueco1) {
			hueco1 -= objetos[i].peso;
			pesimista += objetos[i].valor;
		}
		//Sino, si cabe en la cara 2 la pongo el la 2.
		else if (objetos[i].peso <= hueco2) {
			hueco2 -= objetos[i].peso;
			pesimista += objetos[i].valor;
		}
		i++;
	}
}

// objetos ordenados de mayor a menor valor/peso
void mochila_rp(vector<Objeto> const& objetos, double M, vector<bool>& sol, double& beneficio_mejor) {
	int N = objetos.size();
	// se genera la raíz
	Nodo Y;
	Y.k = -1;
	Y.peso1 = Y.peso2 = Y.beneficio = 0;
	double pesimista;
	cota_optimista(objetos, M, Y, Y.beneficio_optimista);
	cota_pesimista(objetos, M, Y, beneficio_mejor);
	priority_queue<Nodo> cola;
	cola.push(Y);
	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_optimista >= beneficio_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);

		++X.k;
		//Primera cara
		if (X.peso1 + objetos[X.k].peso <= M) {
			X.peso1 = Y.peso1 + objetos[X.k].peso;
			X.beneficio = Y.beneficio + objetos[X.k].valor;
			if (X.k == N - 1) {
				beneficio_mejor = X.beneficio;
			}
			else cola.push(X);
		}

		X.peso1 = Y.peso1;
		X.beneficio = Y.beneficio;
		if (X.peso2 + objetos[X.k].peso <= M && X.peso1 != X.peso2) {
			X.peso2 = Y.peso2 + objetos[X.k].peso;
			X.beneficio = Y.beneficio + objetos[X.k].valor;
			if (X.k == N - 1) {
				beneficio_mejor = X.beneficio;
			}
			else cola.push(X);
		}

		// probar a no meter el objeto
		X.peso1 = Y.peso1;
		X.peso2 = Y.peso2;
		X.beneficio = Y.beneficio;
		cota_optimista(objetos, M, X, X.beneficio_optimista);
		cota_pesimista(objetos, M, X, pesimista);
		if (X.beneficio_optimista >= beneficio_mejor) {

			if (X.k == N - 1) {
				beneficio_mejor = X.beneficio;
			}
			else {
				cola.push(X);
				beneficio_mejor = max(beneficio_mejor, pesimista);
			}
		}
	}
	
}

bool resuelveCaso() {
	int capacidad, valor, peso, numCanciones;
	cin >> numCanciones;
	if (numCanciones == 0) return false;
	vector<Objeto> objetos;
	cin >> capacidad;
	for (int i = 0; i < numCanciones; i++) {
		cin >> peso >> valor;
		Objeto objeto;
		objeto.valor = valor;
		objeto.peso = peso;
		objetos.push_back(objeto);
	}
	sort(objetos.begin(), objetos.end());

	vector<bool> sol_mejor;
	double beneficio_mejor;

	mochila_rp(objetos, capacidad, sol_mejor, beneficio_mejor);
	cout << beneficio_mejor << '\n';

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}