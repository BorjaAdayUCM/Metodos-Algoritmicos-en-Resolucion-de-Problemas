//Grupo 11

#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matriz.h"

using namespace std;

// Programacion dinamica descendente. El coste está en O(N*M) siendo N el tamano de la cadena1 y M el tamano de la cadena2.
// Esto se debe a que vamos descartando caracteres de ambas cadenas hasta agotar una o ambas.
int maxSubsecuencia(string const& cadena1, string const& cadena2, int i, int j, Matriz<int>& tabla) {
    if (i < 0 || j < 0) {
        return 0;
    }
    int& res = tabla[i][j];
    if (res == -1) {
        if (i >= 0 && j >= 0 && cadena1[i] == cadena2[j]) {
            res = maxSubsecuencia(cadena1, cadena2, i - 1, j - 1, tabla) + 1;
        } 
        else if (i >= 0 && j >= 0 && cadena1[i] != cadena2[j]) {
            res = max(maxSubsecuencia(cadena1, cadena2, i - 1, j, tabla), maxSubsecuencia(cadena1, cadena2, i, j - 1, tabla));
        }
    }
    return res;
}

// El coste de esta función en el caso peor esta en O(N*M) siendo N el tamano de la cadena1 y M el tamano de la cadena2.
void reconstruir(string const& cadena1, string const& cadena2, Matriz<int> const& tabla, int i, int n2, int tam, string & sol) {
    int j = 0;
    if (tam > 0)
    {
        bool encontrado = false;
        while (j < n2 && !encontrado)
        {
            if (tabla[i][j] == tam)
                encontrado = true;
            else
                j++;
        }
        if(j == n2) reconstruir(cadena1, cadena2, tabla, i - 1, n2, tam, sol);
        else {
            reconstruir(cadena1, cadena2, tabla, i - 1, j, tam - 1, sol);
            sol.push_back(cadena2[j]);
        }
    }
}

bool resuelveCaso() {

    string cadena1, cadena2;

    cin >> cadena1;

    if (!std::cin) return false;

    cin >> cadena2;

    int n1 = cadena1.size(), n2 = cadena2.size();
    Matriz<int> tabla(n1, n2, -1);

    int max = maxSubsecuencia(cadena1, cadena2, n1 - 1, n2 - 1, tabla);

    string sol = "";
    
    reconstruir(cadena1, cadena2, tabla, n1 - 1, n2, max, sol);

    cout << sol << '\n';

    return true;
}

int main() {

    while (resuelveCaso());

    return 0;
}