#include <iostream>
#include <fstream>
#include "Manchas.h"

using namespace std;

bool resuelveCaso() { 
    int F, C;

    cin >> F >> C; 

    if (!cin) return false;

    Mapa mapa(F);

    for (string& linea : mapa) cin >> linea;

    Manchas manchas(mapa);
    cout << manchas.numero() << ' ' << manchas.maximo() << '\n';

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