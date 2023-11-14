#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
#include <math.h>
#include "SerpientesEscaleras.h"

using namespace std;

bool resuelveCaso() {
    int tam, k, s, e, v1, v2;

    cin >> tam >> k >> s >> e;

    if (tam == 0 && k == 0 && s == 0 && e == 0) return false;

    int vertices = tam * tam;

    vector<int> serpEsc(vertices + 1, -1);

    for (int i = 0; i < s + e; i++) {
        cin >> v1 >> v2;
        serpEsc[v1] = v2;
    }

    SerpientesEscaleras serpientesYescaleras = SerpientesEscaleras(tam, k, serpEsc);

    cout << serpientesYescaleras.caminoMin() << endl;

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