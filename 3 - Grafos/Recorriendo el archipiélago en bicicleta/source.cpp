#include <iostream>
#include <fstream>
#include "Archipielago.h"
#include "GrafoValorado.h"

using namespace std;

bool resuelveCaso() {
    int nIslas, nPuentes, v1, v2, precio;

    cin >> nIslas >> nPuentes;

    if (!std::cin)
        return false;

    GrafoValorado<int> grafo = GrafoValorado<int>(nIslas);

    for (int i = 0; i < nPuentes; i++) {
        cin >> v1 >> v2 >> precio;
        grafo.ponArista(Arista<int>(v1 - 1, v2 - 1, precio));
    }

    Archipielago<int> archipielago = Archipielago<int>(grafo);

    if (archipielago.esConexo() || nIslas == 1) cout << archipielago.costeARM() << endl;
    else cout << "No hay puentes suficientes" << endl;

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