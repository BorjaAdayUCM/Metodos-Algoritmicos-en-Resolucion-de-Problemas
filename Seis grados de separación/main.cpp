#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"


using namespace std;

typedef pair<string, int> elemDiccionario;

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                EntInf temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {
    int numPersonas, numRelaciones;
    string persona1, persona2;
    int id = 0;

    cin >> numPersonas;

    if (!std::cin) return false;

    cin >> numRelaciones;

    Matriz<EntInf> G(numPersonas, numPersonas, Infinito), C;

    unordered_map<string, int> diccionario;

    for (int i = 0; i < numRelaciones; i++) {
        cin >> persona1 >> persona2;
        if (diccionario.find(persona1) == diccionario.cend()) {
            diccionario.insert(elemDiccionario(persona1, id));
            id++;
        }
        if (diccionario.find(persona2) == diccionario.cend()) {
            diccionario.insert(elemDiccionario(persona2, id));
            id++;
        }
        int id1 = diccionario.at(persona1), id2 = diccionario.at(persona2);
        G[id1][id2] = 1;
        G[id2][id1] = 1;
    }

    for (int i = 0; i < numPersonas; i++) {
        G[i][i] = 0;
    }

    Floyd(G, C);

    EntInf max = C[0][0];
    for (int i = 0; i < numPersonas; i++) {
        for (int j = i; j < numPersonas; j++) {
            if (C[i][j] > max) max = C[i][j];
        }
    }
    if (max == Infinito) cout << "DESCONECTADA\n";
    else cout << max << '\n';

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