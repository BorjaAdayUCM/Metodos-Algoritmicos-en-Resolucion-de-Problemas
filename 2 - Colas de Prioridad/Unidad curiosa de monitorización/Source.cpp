#include<iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct paciente {
	string nombre;
	int llegada;
	int gravedad;
};

bool operator<(paciente const& a, paciente const& b) {
	return a.gravedad > b.gravedad || (a.gravedad == b.gravedad && a.llegada < b.llegada);
}

bool resuelveCaso() {
	int nEventos, gravedad;
	string tipoEvento, nombre;

	cin >> nEventos;

	if (nEventos == 0) return false;
	
	PriorityQueue<paciente> cola;

	for(int i = 0; i < nEventos; i++) {
		cin >> tipoEvento;

		if (tipoEvento == "I") {
			cin >> nombre >> gravedad;
			cola.push({ nombre, i, gravedad });
		}
		else {
			cout << cola.top().nombre << '\n';
			cola.pop();
		}
	}
	cout << "---\n";

	return true;
}

int main() {

	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}