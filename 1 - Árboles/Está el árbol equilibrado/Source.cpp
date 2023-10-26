#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

bool equilibrado(bintree<char> const& arbol, int& altura) {

	if (arbol.empty()) {
		altura = 0;
		return true;
	}
	else {
		int alturaIzq, alturaDcha;
		bool equilibIzq, equilibDcha;

		equilibIzq = equilibrado(arbol.left(), alturaIzq);
		equilibDcha = equilibrado(arbol.right(), alturaDcha);

		altura = max(alturaIzq, alturaDcha) + 1;

		if (equilibIzq && equilibDcha && abs(alturaIzq - alturaDcha) <= 1) return true;
		return false;
	}
}

void resuelveCaso() {
	bintree<char> arbol = leerArbol('.');
	int altura;
	if (equilibrado(arbol, altura)) cout << "SI\n";
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