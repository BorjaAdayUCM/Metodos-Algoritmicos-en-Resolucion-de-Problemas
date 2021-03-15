#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "Matriz.h"


using namespace std;

int esPosible(string const cadena) {
    int n = cadena.size() - 1;

    Matriz<bool> A(n + 1, n + 1, false);
    Matriz<bool> B(n + 1, n + 1, false);
    Matriz<bool> C(n + 1, n + 1, false);

    //CASOS BASE
    for (int i = 0; i <= n; i++) {
        if (cadena[i] == 'a') A[i][i] = true;
        if (cadena[i] == 'b') B[i][i] = true;
        if (cadena[i] == 'c') C[i][i] = true;
    }

    for (int d = 1; d <= n; ++d) {// recorre diagonales
        for (int i = 0; i <= n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            for (int k = i; k <= j - 1; ++k) {
                //FORMAS DE A (AxC, BxC, CxA)
                if ((A[i][k] && C[k + 1][j]) || (B[i][k] && C[k + 1][j]) || (C[i][k] && A[k + 1][j])) A[i][j] = true;

                //FORMAS DE B (AxA, AxB, BxB)
                if ((A[i][k] && A[k + 1][j]) || (A[i][k] && B[k + 1][j]) || (B[i][k] && B[k + 1][j])) B[i][j] = true;

                //FORMAS DE C (BxA, CxB, CxC)
                if ((B[i][k] && A[k + 1][j]) || (C[i][k] && B[k + 1][j]) || (C[i][k] && C[k + 1][j])) C[i][j] = true;
            }
        }
    }
    return A[0][n];
}

bool resuelveCaso() {
    string cadena;
    
    cin >> cadena;

    if (!std::cin) return false;

    if (esPosible(cadena)) cout << "SI\n";
    else cout << "NO\n";

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