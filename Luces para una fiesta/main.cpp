#include <iostream>
#include <algorithm>
#include <vector>
#include "EnterosInf.h"

using namespace std;

const int MAX = 1000;
const long long int INF = 1e18;

pair<EntInf, EntInf> resuelve(int const minPotencia, int const maxPotencia, vector<int> const & potencias, vector<int> const & costes) {
    
    int N = potencias.size();
    vector<EntInf> tabla(maxPotencia + 1, Infinito);
    tabla[0] = 0;

    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= N; ++i) {
        for (int j = potencias[i - 1]; j <= maxPotencia; ++j) {
            tabla[j] = min(tabla[j], tabla[j - potencias[i - 1]] + costes[i - 1]);
        }
    }

    EntInf minCoste = tabla[minPotencia];
    EntInf potenciaOptima = minPotencia;
    for (int i = minPotencia + 1; i <= maxPotencia; i++) {
        if (tabla[i] < minCoste) {
            minCoste = tabla[i];
            potenciaOptima = i;
        }
    }

    return make_pair(minCoste, potenciaOptima);
}

bool resuelveCaso() {

    int numBombillas, minPotencia, maxPotencia, potencia, coste;
    vector<int> potencias = vector<int>(), costes = vector<int>();

    cin >> numBombillas;

    if (!std::cin) return false;

    cin >> maxPotencia >> minPotencia;

    for (int i = 0; i < numBombillas; i++) {
        cin >> potencia;
        potencias.push_back(potencia);
    }

    for (int i = 0; i < numBombillas; i++) {
        cin >> coste;
        costes.push_back(coste);
    }

    pair<EntInf, EntInf> solucion = resuelve(minPotencia, maxPotencia, potencias, costes);

    if (solucion.first == Infinito) cout << "IMPOSIBLE\n";
    else cout << solucion.first << " " << solucion.second << '\n';

    return true;
}

int main() {

    while (resuelveCaso());

    return 0;
}