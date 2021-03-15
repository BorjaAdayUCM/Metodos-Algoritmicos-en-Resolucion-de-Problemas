#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INF = numeric_limits<int>::max();

typedef pair<string, int> elemDiccionario;

int minCoste(const vector<int> & cortes, const int num_cortes) {
    int n = num_cortes + 1;
    Matriz<int> tabla(num_cortes + 2, num_cortes + 2, 0);
    for (int d = 1; d <= n - 1; ++d) // recorre diagonales
        for (int i = 1; i <= n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            tabla[i][j] = INF;
            for (int k = i; k <= j - 1; ++k) {
                if (cortes[j] == 3 && cortes[i - 1] == 0) {
                    cout << endl;
                }
                int temp = tabla[i][k] + tabla[k + 1][j] + (2 * (cortes[j] - cortes[i - 1]));
                if (temp < tabla[i][j]) {
                    tabla[i][j] = temp;
                }
            }
        }
    return tabla[1][n];
}

bool resuelveCaso() {
    int longitud, numCortes, tamCorte;
    vector<int> cortes;
    cin >> longitud >> numCortes;

    if (longitud == 0 && numCortes == 0) return false;

    cortes.push_back(0);
    for (int i = 0; i < numCortes; i++) {
        cin >> tamCorte;
        cortes.push_back(tamCorte);
    }
    cortes.push_back(longitud);

    cout << minCoste(cortes, numCortes) << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}