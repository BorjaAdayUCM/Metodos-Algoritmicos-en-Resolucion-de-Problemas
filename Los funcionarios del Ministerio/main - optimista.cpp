#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Nodo {
    int k;
    vector<bool> marcaje;
    int beneficio;
    int beneficio_optimista;

    bool operator<(Nodo const& otro) const {
        return otro.beneficio_optimista < beneficio_optimista;
    }

};

int beneficio_optimista(vector<int> const& minTiempos, Nodo const& nodo) {
    if (nodo.k + 1 == minTiempos.size()) return nodo.beneficio;
    return nodo.beneficio + minTiempos[nodo.k + 1];
}

void resolver(vector<vector<int>> const& tiempos, vector<int> const& minTiempos, int& beneficio_mejor) {

    int N = minTiempos.size();

    Nodo Y;
    Y.k = -1;
    Y.marcaje = vector<bool>(N, false);
    Y.beneficio = 0;
    Y.beneficio_optimista = beneficio_optimista(minTiempos, Y);
    beneficio_mejor = N * 10000;
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().beneficio_optimista < beneficio_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        for (int i = 0; i < N; i++) {
            if (!X.marcaje[i]) {
                X.marcaje[i] = true;
                X.beneficio += tiempos[X.k][i];
                X.beneficio_optimista = beneficio_optimista(minTiempos, X);

                    if (X.beneficio_optimista < beneficio_mejor) {
                        if (X.k == N - 1) {
                            beneficio_mejor = X.beneficio;
                        }
                        else cola.push(X);
                    }

                X.marcaje[i] = false;
                X.beneficio = Y.beneficio;
            }

        }

    }

}

bool resuelveCaso() {
    int N, tiempo, beneficio_mejor;

    cin >> N;

    if (N == 0) return false;

    vector<vector<int>> tiempos;
    vector<int> minTiempos;

    for (int i = 0; i < N; i++) {
        vector<int> vectorTiempos;
        int min = 10000;
        for (int j = 0; j < N; j++) {
            cin >> tiempo;
            if (tiempo < min) min = tiempo;
            vectorTiempos.push_back(tiempo);
        }
        minTiempos.push_back(min);
        tiempos.push_back(vectorTiempos);
    }

    for (int i = N - 2; i >= 0; i--) {
        minTiempos[i] += minTiempos[i + 1];
    }

    resolver(tiempos, minTiempos, beneficio_mejor);

    cout << beneficio_mejor << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}