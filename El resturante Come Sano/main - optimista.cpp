#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Nodo {
    int k;
    vector<bool> marcaje;
    vector<int> sol;
    int beneficio;
    int beneficio_optimista;

    bool operator<(Nodo const& otro) const {
        return otro.beneficio_optimista > beneficio_optimista;
    }

};

bool asientoValido(Nodo const& nodo, vector<vector<float>> const& distancias, vector<vector<bool>> const& allegados, int const& asiento) {
    if (nodo.marcaje[asiento]) return false;
    for (int i = 0; i < nodo.k; i++) {
        if (!allegados[nodo.k][i] && distancias[asiento][nodo.sol[i]] < 2) return false;
    }
    return true;
}

int nuevo_beneficio(Nodo const& nodo, vector<vector<float>> const& distancias, vector<vector<bool>> const& allegados, int const& asiento) {
    int parejas = 0;
    for (int i = 0; i < nodo.k; i++) {
        if (allegados[nodo.k][i] && distancias[asiento][nodo.sol[i]] < 2) parejas++;
    }
    return parejas;
}

int beneficio_optimista(Nodo const& nodo, vector<int> const& numAllegados, int const& M) {
    if (nodo.k == M - 1) return nodo.beneficio;
    else return nodo.beneficio + numAllegados[nodo.k + 1];
}

void resolver(int const& N, int const& M, vector<vector<float>> const& distancias, vector<vector<bool>> const& allegados, vector<int> const& numAllegados, int & beneficio_mejor) {

    Nodo Y;
    Y.k = -1;
    Y.marcaje = vector<bool>(N, false);
    Y.beneficio = 0;
    Y.beneficio_optimista = beneficio_optimista(Y, numAllegados, M);
    Y.sol = vector<int>(M, -1);
    beneficio_mejor = -1;
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().beneficio_optimista > beneficio_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        for (int i = 0; i < N; i++) {

            if (asientoValido(X, distancias, allegados, i)) {
                X.marcaje[i] = true;
                X.sol[X.k] = i;
                X.beneficio = Y.beneficio + nuevo_beneficio(X, distancias, allegados, i);
                X.beneficio_optimista = beneficio_optimista(X, numAllegados, M);

                if (X.beneficio_optimista > beneficio_mejor) {
                    if (X.k == M - 1) {
                        if(X.beneficio > beneficio_mejor) beneficio_mejor = X.beneficio;
                    }
                    else cola.push(X);
                }

                X.sol[X.k] = Y.sol[X.k];
                X.beneficio = Y.beneficio;
                X.marcaje[i] = Y.marcaje[i];
            }

        }
    }
}

void resuelveCaso() {
    int M, N, beneficio_mejor;
    float distancia;
    bool cercano;

    vector<vector<float>> distancias;
    vector<vector<bool>> allegados;
    
    cin >> N >> M;
    vector<int> numAllegados(M, 0);

    for (int i = 0; i < N; i++) {
        vector<float> vectorDistancias;
        for (int j = 0; j < N; j++) {
            cin >> distancia;
            vectorDistancias.push_back(distancia);
        }
        distancias.push_back(vectorDistancias);
    }

    for (int i = 0; i < M; i++) {
        vector<bool> vectorCercanos;
        for (int j = 0; j < M; j++) {
            cin >> cercano;
            vectorCercanos.push_back(cercano);
        }
        allegados.push_back(vectorCercanos);
    }

    for (int i = 0; i < M; i++) {
        for (int j = i; j < M; j++) {
            if (allegados[i][j]) numAllegados[j]++;
        }
    }
    
    for (int i = M - 2; i >= 0; i--) {
        numAllegados[i] += numAllegados[i + 1];
    }

    resolver(N, M, distancias, allegados, numAllegados, beneficio_mejor);

    if (beneficio_mejor == -1) cout << "CANCELA\n";
    else cout << "PAREJAS " << beneficio_mejor << '\n';
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}