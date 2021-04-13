#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Objeto {
	double peso, valor;
};

struct Nodo {
	vector<bool> sol;
	int k;
	double peso; // peso acumulado
	double beneficio; // valor acumulado
	double beneficio_est; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_est > beneficio_est;
	}
};

// estrategia voraz, para calcular la estimación
double calculo_voraz(vector<Objeto> const& objetos, double M,
	Nodo const& X) {
	double hueco = M - X.peso, estimacion = X.beneficio;
	int i = X.k + 1;
	while (i < objetos.size() && objetos[i].peso <= hueco) {
		// podemos coger el objeto j entero
		hueco -= objetos[i].peso;
		estimacion += objetos[i].valor;
		++i;
	}
	if (i < objetos.size())
		estimacion += (hueco / objetos[i].peso) * objetos[i].valor;
	return estimacion;
}

// objetos ordenados de mayor a menor valor/peso
void mochila_rp(vector<Objeto> const& objetos, double M,
	vector<bool>& sol_mejor, double& beneficio_mejor) {
	int N = objetos.size();
	// se genera la raíz
	Nodo Y;
	Y.sol = vector<bool>(N);
	Y.k = -1;
	Y.peso = Y.beneficio = 0;
	Y.beneficio_est = calculo_voraz(objetos, M, Y);
	priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = -1;
	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);
		++X.k;
		// probamos a meter el objeto en la mochila
		if (Y.peso + objetos[X.k].peso <= M) {
			X.sol[X.k] = true;
			X.peso = Y.peso + objetos[X.k].peso;
			X.beneficio = Y.beneficio + objetos[X.k].valor;
			X.beneficio_est = Y.beneficio_est;
			if (X.k == N - 1) {
				sol_mejor = X.sol; beneficio_mejor = X.beneficio;
			}
			else cola.push(X);
		}
		// probar a no meter el objeto
		X.sol[X.k] = false;
		X.peso = Y.peso; X.beneficio = Y.beneficio;
		X.beneficio_est = calculo_voraz(objetos, M, X);
		if (X.beneficio_est > beneficio_mejor) {
			if (X.k == N - 1) {
				sol_mejor = X.sol; beneficio_mejor = X.beneficio;
			}
			else
				cola.push(X);
		}
	}
	
}

bool resuelveCaso() {
	int capacidad, numObjetos, valor, peso;
	cin >> capacidad;
	if (capacidad == 0) return false;
	cin >> numObjetos;
	vector<Objeto> objetos;
	for (int i = 0; i < numObjetos; i++) {
		cin >> valor >> peso;
		Objeto objeto;
		objeto.valor = valor;
		objeto.peso = peso;
		objetos.push_back(objeto);
	}

	vector<bool> sol_mejor;
	double beneficio_mejor;

	mochila_rp(objetos, capacidad, sol_mejor, beneficio_mejor);
	cout << beneficio_mejor << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}