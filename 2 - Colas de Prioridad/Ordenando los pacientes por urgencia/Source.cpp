#include<iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;


struct registro {
	int siguienteEnvio;
	int identificador;
	int periodo;
};

bool operator<(registro const& a, registro const& b) {
	return a.siguienteEnvio < b.siguienteEnvio || (a.siguienteEnvio == b.siguienteEnvio && a.identificador < b.identificador);
}

bool resuelveCaso() {
	int nRegistros;
	cin >> nRegistros; 
	if (nRegistros == 0) return false;
	
	PriorityQueue<registro> cola;

	for (int i = 0; i < nRegistros; ++i)
	{
		int identificador, periodo;
		cin >> identificador >> periodo;
		cola.push({ periodo, identificador, periodo });
	}

	int nEnvios; // número de envíos a mostrar
	cin >> nEnvios;

	while (nEnvios--)
	{
		registro reg = cola.top(); cola.pop();
		cout << reg.identificador << '\n';
		reg.siguienteEnvio += reg.periodo;
		cola.push(reg);
	}
	cout << "---\n";
	return true;
}

int main()
{
// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}