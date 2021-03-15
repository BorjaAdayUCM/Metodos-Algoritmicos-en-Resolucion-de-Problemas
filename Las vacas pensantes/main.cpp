#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <ostream>
#include "Matriz.h"

using namespace std;

int maxComida(vector<int> const& cubos, int numCubos) {
    Matriz<int> tabla(numCubos, numCubos, 0);

    for (int i = 0; i < numCubos; i++) tabla[i][i] = cubos[i];

    for (int d = 1; d <= numCubos - 1; ++d) { // recorre diagonales
        for (int i = 0; i < numCubos - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            int quitaIzquierdaCI = 1, quitaDerechaCI = 1, quitaIzquierdaCD = 1, quitaDerechaCD = 1;
            if (cubos[i + 1] > cubos[j]) {
                quitaIzquierdaCI = 2;
                quitaDerechaCI = 0;
            }
            if (cubos[j - 1] > cubos[i]) {
                quitaDerechaCD = 2;
                quitaIzquierdaCD = 0;
            }
            tabla[i][j] = max(cubos[i] + tabla[i + quitaIzquierdaCI][j - quitaDerechaCI], cubos[j] + tabla[i + quitaIzquierdaCD][j - quitaDerechaCD]);
        }
    }

    return tabla[0][numCubos - 1];
}

int maxComida(vector<int> const& cubos, int i, int j, Matriz<int>& tabla) {
    int& res = tabla[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else if (i == j) res = cubos[i];
        else {
            int quitaIzquierdaCI = 1, quitaDerechaCI = 1, quitaIzquierdaCD = 1, quitaDerechaCD = 1;
            if (cubos[i + 1] > cubos[j]) {
                quitaIzquierdaCI = 2;
                quitaDerechaCI = 0;
            }
            if (cubos[j - 1] > cubos[i]) {
                quitaDerechaCD = 2;
                quitaIzquierdaCD = 0;
            }
            res = max(maxComida(cubos, i + quitaIzquierdaCI, j - quitaDerechaCI, tabla) + cubos[i], maxComida(cubos, i + quitaIzquierdaCD, j - quitaDerechaCD, tabla) + cubos[j]);
        }
    }
    return res;
}

bool resuelveCaso() {
    int numCubos, cubo;
    cin >> numCubos;
    if (numCubos == 0) return false;

    vector<int> cubos;

    for (int i = 0; i < numCubos; i++) {
        cin >> cubo;
        cubos.push_back(cubo);
    }

    //Matriz<int> tabla(numCubos, numCubos, -1);
    //maxComida(cubos, 0, numCubos - 1, tabla);
    //cout << tabla[0][numCubos - 1] << '\n';

    cout << maxComida(cubos, numCubos) << '\n';

    

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