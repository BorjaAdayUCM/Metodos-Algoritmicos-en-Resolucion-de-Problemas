#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include "ConjuntosDisjuntos.h"

using namespace std;

bool correcta(int i, int j, int F, int C) {
    return 0 <= i && i < F && 0 <= j && j < C;
}

bool resuelveCaso() {
    int F, C, N, nf, nc;
    bool mancha = false;

    cin >> F >> C;

    if (!cin) return false;

    char c[1000][1000];
    ConjuntosDisjuntos areasInfectadas = ConjuntosDisjuntos(F * C);
    cin.ignore(1);

    string line;

    for (int i = 0; i < F; i++) {
        getline(cin, line);
        for (int j = 0; j < C; j++) {
            c[i][j] = line[j];
        }
    }

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            if (c[i][j] == '#') {
                mancha = true;
                for (int fila = -1; fila <= 1; fila++) {
                    for (int col = -1; col <= 1; col++) {
                        if (correcta(i + fila, j + col, F, C)) {
                            if (c[i + fila][j + col] == '#') {
                                areasInfectadas.unir(i * C + j, (i + fila) * C + j + col);
                            }
                        }
                    }
                }
            }
        }
    }

    if (areasInfectadas.maxConjunto() == 0 && mancha) cout << 1 << ' ';
    else cout << areasInfectadas.maxConjunto() << ' ';

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> nf >> nc;
        nf -= 1; nc -= 1;
        c[nf][nc] = '#';
        for (int fila = -1; fila <= 1; fila++) {
            for (int col = -1; col <= 1; col++) {
                if (correcta(nf + fila, nc + col, F, C)) {
                    if (c[nf + fila][nc + col] == '#') {
                        areasInfectadas.unir(nf * C + nc, (nf + fila) * C + nc + col);
                    }
                }
            }
        }
        if (areasInfectadas.maxConjunto() == 0) cout << 1 << ' ';
        else cout << areasInfectadas.maxConjunto() << ' ';
    }

    cout << endl;


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