//Grupo 11

#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matriz.h"

using namespace std;

// Programacion dinamica descendente. El coste está en O(N*M) siendo N el tamano de la cadena1 y M el tamano de la cadena2.
// Esto se debe a que vamos descartando caracteres de ambas cadenas hasta agotar una o ambas.
void maxSubsecuencia(string const& cadena1, string const& cadena2, int const& n1, int const& n2, Matriz<int>& tabla) {
    for (int i = 0; i < n1 + 1; i++) tabla[i][0] = 0;
    for (int j = 0; j < n2 + 1; j++) tabla[0][j] = 0;

    for (int i = 1; i < n1 + 1; i++) {
        for (int j = 1; j < n2 + 1; j++) {
            if (cadena1[i - 1] == cadena2[j - 1]) tabla[i][j] = tabla[i - 1][j - 1] + 1;
            else tabla[i][j] = max(tabla[i - 1][j], tabla[i][j - 1]);
        }
    }
}

void reconstruir(string const& cadena1, string const& cadena2, int const& n1, int const& n2, Matriz<int> const & tabla, string & sol) {
    int i = n1, j = n2, maxSubsecuencia = tabla[i][j];
    while (maxSubsecuencia > 0) {
        if (cadena1[i - 1] == cadena2[j - 1]) {
            sol.push_back(cadena1[i - 1]);
            i--; j--;
            maxSubsecuencia--;
        }
        else {
            if (tabla[i - 1][j] == tabla[i][j - 1]) i--;
            else if (tabla[i - 1][j] != tabla[i][j - 1] && tabla[i][j] == tabla[i - 1][j]) i--;
            else j--;
        }
    }
}

bool resuelveCaso() {

    string cadena1, cadena2;

    cin >> cadena1;

    if (!std::cin) return false;

    cin >> cadena2;

    int n1 = cadena1.size(), n2 = cadena2.size();
    Matriz<int> tabla(n1 + 1, n2 + 1, -1);

    maxSubsecuencia(cadena1, cadena2, n1, n2, tabla);

    if (tabla[n1][n2] > 0) {
        string sol = "";
        reconstruir(cadena1, cadena2, n1, n2, tabla, sol);
        for (int i = sol.size() - 1; i >= 0; i--) {
            cout << sol[i];
        }
    }
    cout << '\n';

    return true;
}

int main() {

    while (resuelveCaso());

    return 0;
}
