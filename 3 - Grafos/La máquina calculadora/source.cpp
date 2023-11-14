#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 10000;

int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX;
    case 1: return (v * 2) % MAX;
    case 2: return v / 3;
    }
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;
    vector<int> distancia(MAX, INT_MAX);
    distancia[origen] = 0;
    queue<int> cola; cola.push(origen);
    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
        for (int i = 0; i < 3; ++i) {
            int w = adyacente(v, i);
            if (distancia[w] == INT_MAX) {
                distancia[w] = distancia[v] + 1;
                if (w == destino) return distancia[w];
                else cola.push(w);
            }
        }
    }
}

bool resuelveCaso() {
    int origen, destino;
    cin >> origen >> destino;
    if (!cin) return false;
    cout << bfs(origen, destino) << "\n";
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