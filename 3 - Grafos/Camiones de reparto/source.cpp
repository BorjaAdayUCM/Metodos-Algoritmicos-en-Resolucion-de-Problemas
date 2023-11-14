#include <iostream>
#include <fstream>
#include "Camiones.h"
#include "GrafoValorado.h"

using namespace std;

bool resuelveCaso() {
    int V, A, Q, v1, v2, ancho;

    cin >> V >> A;

    if (!std::cin)
        return false;

    GrafoValorado<int> grafo = GrafoValorado<int>(V);

    for (int i = 0; i < A; i++) {
        cin >> v1 >> v2 >> ancho;
        grafo.ponArista(Arista<int>(v1 - 1, v2 - 1, ancho));
    }

    Camiones camiones = Camiones(grafo);

    cin >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> v1 >> v2 >> ancho;
        if (camiones.esPosible(v1 - 1, v2 - 1, ancho)) cout << "SI\n";
        else cout << "NO\n";
    }

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