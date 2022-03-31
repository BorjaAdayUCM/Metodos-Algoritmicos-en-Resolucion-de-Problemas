#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Nodo {
    int k;
    vector<bool> marcaje;
    int beneficio;
    int beneficio_est;

    bool operator<(Nodo const& otro) const {
        return otro.beneficio_est > beneficio_est;
    }

};

int beneficio_optimista(vector<int> const& maxCalidades, Nodo const& nodo) {
    if (nodo.k + 1 == maxCalidades.size()) return nodo.beneficio;
    return nodo.beneficio + maxCalidades[nodo.k + 1];
}

void resolver(vector<int> const& anchuraCarros, vector<int> const& anchuraCaminos, vector<int> const& maxCalidades, vector<vector<int>> const& calidades, int & beneficio_mejor) {

    int N = anchuraCarros.size();
    int M = anchuraCaminos.size();

    Nodo Y;
    Y.k = -1;
    Y.marcaje = vector<bool>(M, false);
    Y.beneficio = 0;
    Y.beneficio_est = beneficio_optimista(maxCalidades, Y);
    beneficio_mejor = 0;
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        for (int i = 0; i < M; i++) {
            if (anchuraCarros[X.k] <= anchuraCaminos[i] && !X.marcaje[i]) {
                X.marcaje[i] = true;
                X.beneficio += calidades[X.k][i];
                X.beneficio_est = beneficio_optimista(maxCalidades, X);

                if (X.beneficio_est > beneficio_mejor) {
                    if (X.k == N - 1) {
                        beneficio_mejor = X.beneficio;
                    }
                    else cola.push(X);
                }

                X.marcaje[i] = false;
                X.beneficio = Y.beneficio;
            }

        }

        X.beneficio_est = beneficio_optimista(maxCalidades, X);
        if (X.beneficio_est > beneficio_mejor) {
            if (X.k == N - 1) {
                beneficio_mejor = X.beneficio;
            }
            else cola.push(X);
        }

    }

}

void resuelveCaso() {

    int numCarros, numCaminos, anchura, calidad, beneficio_mejor;
    vector<int> anchuraCarros, anchuraCaminos, maxCalidades;
    vector<vector<int>> calidades;

    cin >> numCarros >> numCaminos;
    
    for (int i = 0; i < numCarros; i++) {
        cin >> anchura;
        anchuraCarros.push_back(anchura);
    }

    for (int i = 0; i < numCaminos; i++) {
        cin >> anchura;
        anchuraCaminos.push_back(anchura);
    }

    for (int i = 0; i < numCarros; i++) {
        vector<int> vectorCalidades;
        int max = 0;
        for (int j = 0; j < numCaminos; j++) {
            cin >> calidad;
            if (calidad > max) max = calidad;
            vectorCalidades.push_back(calidad);
        }
        maxCalidades.push_back(max);
        calidades.push_back(vectorCalidades);
    }

    for (int i = numCarros - 2; i >= 0; i--) {
        maxCalidades[i] += maxCalidades[i + 1];
    }

    resolver(anchuraCarros, anchuraCaminos, maxCalidades, calidades, beneficio_mejor);

    cout << beneficio_mejor << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
