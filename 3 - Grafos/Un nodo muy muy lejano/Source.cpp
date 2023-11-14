#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "NodoLejano.h"

using namespace std;



bool resuelveCaso() {

    Grafo grafo = Grafo(cin, 1);

    if (!std::cin)
        return false;

    NodoLejano nl = NodoLejano(grafo);

    int nConsultas, nodo, ttl;

    cin >> nConsultas;

    for (int i = 0; i < nConsultas; i++) {
        cin >> nodo >> ttl;
        cout << nl.nodosNoAlcanzablesDesde(nodo - 1, ttl) << '\n';
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