#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "ArbolLibre.h"

using namespace std;

bool resolver(Grafo grafo) {
    return ArbolLibre(grafo).esArbolLibre();
}

bool resuelveCaso() {

    Grafo grafo = Grafo(cin);

    if (!std::cin)
        return false;

    if (resolver(grafo)) cout << "SI\n";
    else cout << "NO\n";

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