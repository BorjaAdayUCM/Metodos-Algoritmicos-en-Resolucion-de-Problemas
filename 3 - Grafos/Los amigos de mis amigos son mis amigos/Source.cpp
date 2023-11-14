#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "MaximaCompConexa.h"

using namespace std;

void resuelveCaso() {

    Grafo grafo = Grafo(cin, 1);

    MaximaCompConexa mcc(grafo);

    cout << mcc.maximo() << '\n';
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;

    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}