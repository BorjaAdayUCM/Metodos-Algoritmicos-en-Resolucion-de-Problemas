#include <iostream>
#include <fstream>
#include <limits.h>
#include "bintree_eda.h"

using namespace std;

bool esAVL(bintree<int> const& arbol, int& altura, int& minimo, int& maximo) {

	if (arbol.empty()) {
		altura = 0;
		minimo = INT_MAX;
		maximo = INT_MIN;
		return true;
	}
	else {
		int alturaIzq, alturaDcha, minimoIzq, minimoDer, maximoIzq, maximoDer;
		bool esAVLIzq, esAVLDer;

		esAVLIzq = esAVL(arbol.left(), alturaIzq, minimoIzq, maximoIzq);
		esAVLDer = esAVL(arbol.right(), alturaDcha, minimoDer, maximoDer);

		altura = max(alturaIzq, alturaDcha) + 1;
		minimo = min(minimoIzq, arbol.root());
		maximo = max(maximoDer, arbol.root());


		if (esAVLIzq && esAVLDer && abs(alturaIzq - alturaDcha) <= 1 && maximoIzq < arbol.root() && arbol.root() < minimoDer) return true;
		return false;
	}
}

void resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	int altura, minimo, maximo;
	if (esAVL(arbol, altura, minimo, maximo)) cout << "SI\n";
	else cout << "NO\n";
}

int main() {
	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	unsigned int numCasos;
	std::cin >> numCasos;
	// Resolvemos
	for (int i = 0; i < numCasos; ++i) {
		resuelveCaso();
	}


#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}