
// Nombre y Apellidos
// Borja Aday Guadalupe Luis
// Óscar Morujo Fernández
// Roberto Plaza Hermira
// Pablo Martínez

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema


#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(Matriz<int> tablero, int N) {
	vector<int> tabla(N);
	//Matriz<int> tabla(2, N);
	for (int j = 0; j < N; j++)
	{
		tabla[j] = tablero[0][j];
	}

	for (int i = 1; i < N; i++)
	{
		int aux1, aux2;
		for (int j = N - 1; j >= 0; j--)
		{
			aux1 = tabla[j];
			if (j > 0 && j < N - 1)
				tabla[j] = max(max(tabla[j], tabla[j - 1]), aux2) + tablero[i][j];
				//tabla[i % 2][j] = max(max(tabla[(i + 1) % 2][j - 1], tabla[(i + 1) % 2][j]), tabla[(i + 1) % 2][j + 1]) + tablero[i][j];
			else if (j > 0)
				tabla[j] = max(tabla[j], tabla[j - 1]) + tablero[i][j];
				//tabla[i % 2][j] = max(tabla[(i + 1) % 2][j - 1], tabla[(i + 1) % 2][j]) + tablero[i][j];
			else
				tabla[j] = max(tabla[j], aux2) + tablero[i][j];
				//tabla[i % 2][j] = max(tabla[(i + 1) % 2][j], tabla[(i + 1) % 2][j + 1]) + tablero[i][j];
			aux2 = aux1;
		}
	}

	int max = 0;
	int pos = 0;
	for (int j = 0; j < N; j++) {
		if (tabla[j] > max) {
			max = tabla[j];
			pos = j + 1;
		}

	}

	cout << max << " " << pos << '\n';
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	Matriz<int> tablero(N, N);
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> tablero[i][j];
		}
	}

	resolver(tablero, N);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
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
