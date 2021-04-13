#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include "Matriz.h"

using namespace std;

struct Nodo {
	vector<int> sol;
	int k;
	vector<bool> marcaje;
	int beneficio; // valor acumulado
	int beneficio_est; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_est < beneficio_est;
	}
};

int beneficio_estimado(vector<int> const& minTiempos,Nodo const& X, int N) {
	if (X.k + 1 == N) return X.beneficio;
	return X.beneficio + minTiempos[X.k + 1];
}

void funcionarios_rp(Matriz<int> const& trabajos, 
	vector<int> & sol_mejor, vector<int> const& minimos, int& beneficio_mejor, int N) {
	// se genera la raíz
	Nodo Y;
	Y.marcaje = vector<bool>(N, false);
	Y.sol = vector<int>(N);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_est = beneficio_estimado(minimos, Y, N);
	priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = INT_MAX;

	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_est < beneficio_mejor) {

		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		++X.k;

		// probamos a asignar este trabajo a cada trabajador.
		for (int i = 0; i < N; i++) {
			if (!X.marcaje[i]) {
				X.marcaje[i] = true;
				X.sol[X.k] = i;
				X.beneficio = Y.beneficio + trabajos[i][X.k];
				X.beneficio_est = beneficio_estimado(minimos, X, N);
				if (X.beneficio_est < beneficio_mejor) {
					if (X.k == N - 1) {
						if (X.beneficio < beneficio_mejor) {
							sol_mejor = X.sol;
							beneficio_mejor = X.beneficio;
						}
					}
					else cola.push(X);
				}
				X.marcaje[i] = false;
			}
		}

	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
	int N;
	cin >> N;

	if (N == 0) return false;

	Matriz<int> datos(N, N);
	vector<int> minTiempo(N, INT_MAX);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> datos[i][j];
			if (datos[i][j] < minTiempo[j]) minTiempo[j] = datos[i][j];
		}
	}

	for (int i = N - 2; i >= 0; i--) {
		minTiempo[i] += minTiempo[i + 1];
	}

	vector<int> sol_mejor(N);
	int beneficio_mejor;
	funcionarios_rp(datos, sol_mejor, minTiempo, beneficio_mejor, N);
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
