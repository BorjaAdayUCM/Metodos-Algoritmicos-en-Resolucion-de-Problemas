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
		return otro.beneficio_est > beneficio_est;
	}
};

int beneficio_estimado_camion(vector<int> const& maxCalidad, Nodo const& X, int N) {
	if (X.k + 1 == N) return X.beneficio;
	return X.beneficio + maxCalidad[X.k + 1];
}

void funcionarios_rp_camion(Matriz<int> const& calidades, vector<int> const& anchuraCarros, vector<int> const& anchuraCaminos, vector<int> const& maxCalidad, vector<int> & sol_mejor, int& beneficio_mejor, int N, int M) {
	// se genera la raíz
	Nodo Y;
	Y.marcaje = vector<bool>(M, false);
	Y.sol = vector<int>(N, -1);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_est = beneficio_estimado_camion(maxCalidad, Y, N);
	priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = 0;

	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {

		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		++X.k;

		// probamos a asignar esta máquina a cada camino.
		for (int i = 0; i < M; i++) {
			if (!X.marcaje[i] && anchuraCaminos[i] >= anchuraCarros[X.k]) {
				X.marcaje[i] = true;
				X.sol[X.k] = i;
				X.beneficio = Y.beneficio + calidades[X.k][i];
				X.beneficio_est = beneficio_estimado_camion(maxCalidad, X, N);
				if (X.beneficio_est > beneficio_mejor) {
					if (X.k == N - 1) {
						sol_mejor = X.sol;
						beneficio_mejor = X.beneficio;
					}
					else cola.push(X);
				}
				X.sol[X.k] = -1;
				X.marcaje[i] = false;
				X.beneficio = Y.beneficio;
			}
			
		}
		X.beneficio = Y.beneficio;
		X.beneficio_est = beneficio_estimado_camion(maxCalidad, X, N);
		if (X.beneficio_est > beneficio_mejor) {
			if (X.k == N - 1) {
				sol_mejor = X.sol;
				beneficio_mejor = X.beneficio;
			}
			else cola.push(X);
		}

	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCasoCamion() {
	/*int N = 49, M = 50;
	int N = rand() % 50, M = (N + 1) + rand() % (51 - (N + 1));
	cout << N << " " << M << endl;

	vector<int> anchuraCarros(N);
	vector<int> anchuraCaminos(M);
	Matriz<int> calidades(N, M);
	vector<int> maxCalidad(N, -1);

	for (int i = 0; i < N; i++) anchuraCarros[i] = rand() % 1001;
	for (int i = 0; i < M; i++) anchuraCaminos[i] = rand() % 1001;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			calidades[i][j] = rand() % 1001;
			if (calidades[i][j] > maxCalidad[i]) maxCalidad[i] = calidades[i][j];
		}
	}*/

	int N, M;
	cin >> N >> M;

	vector<int> anchuraCarros(N);
	vector<int> anchuraCaminos(M);
	Matriz<int> calidades(N, M);
	vector<int> maxCalidad(N, -1);

	for (int i = 0; i < N; i++) cin >> anchuraCarros[i];
	for (int i = 0; i < M; i++) cin >> anchuraCaminos[i];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> calidades[i][j];
			if (calidades[i][j] > maxCalidad[i]) maxCalidad[i] = calidades[i][j];
		}
	}

	for (int i = N - 2; i >= 0; i--) maxCalidad[i] += maxCalidad[i + 1];

	vector<int> sol_mejor(N);
	int beneficio_mejor;
	if (N == 0) cout << "0\n";
	else {
		funcionarios_rp_camion(calidades, anchuraCarros, anchuraCaminos, maxCalidad, sol_mejor, beneficio_mejor, N, M);
		cout << beneficio_mejor << '\n';
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	/*srand(time(NULL));
	while (true) resuelveCasoCamion();*/
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) {
		resuelveCasoCamion();
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
