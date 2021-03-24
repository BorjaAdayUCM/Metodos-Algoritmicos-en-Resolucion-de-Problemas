// Grupo 11

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <vector>
#include <algorithm>
#include "EnterosInf.h"
// propios o los de las estructuras de datos de clase

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

struct Moneda { 
	int valor; 
	int cantidad; 
};

bool minMonedas(vector<Moneda> moneda, int N, int C) {
	vector<EntInf> M(C + 1);

	M[0] = 0;

	for (int j = 1; j < C + 1; ++j)
		M[j] = Infinito;

	for (int i = 1; i < N + 1; ++i)
		for (int j = C; j >= 1; --j) {
			EntInf mini = Infinito;
			for (int k = 0; k <= moneda[i - 1].cantidad && k * moneda[i - 1].valor <= j; ++k) {
				if (M[j - k * moneda[i - 1].valor] != Infinito) {
					mini = min(M[j - k * moneda[i - 1].valor] + k, mini);
				}
			}
			M[j] = mini;
		}

	if (M[C] == Infinito)
		cout << "NO";
	else
		cout << "SI " << M[C];

	cout << '\n';

	return true;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
	int N;
	cin >> N;

   if (!std::cin)  // fin de la entrada
      return false;
   
   vector<Moneda> moneda(N);

   for (int i = 0; i < N; ++i) {
	   cin >> moneda[i].valor;
   }

   for (int i = 0; i < N; ++i) {
	   cin >> moneda[i].cantidad;
   }

   int C;
   cin >> C;

   minMonedas(moneda, N, C);
   
   // escribir sol
   
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
