#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matriz.h"

using namespace std;

int patin_rec(string const& patitos, int i, int j, Matriz<int>& patin) {
    int& res = patin[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else if (i == j) res = 1;
        else if (patitos[i] == patitos[j])
            res = patin_rec(patitos, i + 1, j - 1, patin) + 2;
        else
            res = max(patin_rec(patitos, i + 1, j, patin),
                patin_rec(patitos, i, j - 1, patin));
    }
    return res;
}

void reconstruir(string const& patitos, Matriz<int> const& patin, int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(patitos[i]);
    else if (patitos[i] == patitos[j]) {
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j - 1, sol);
        sol.push_back(patitos[j]);
    }
    else if (patin[i][j] != patin[i + 1][j]) {
        sol.push_back(patitos[j]);
        reconstruir(patitos, patin, i, j - 1, sol);
        sol.push_back(patitos[j]);
    }
    else {
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j, sol);
        sol.push_back(patitos[i]);
    }
        
}

bool resuelveCaso() {

    string patitos;

    cin >> patitos;

    if (!std::cin) return false;

    int n = patitos.length();
    Matriz<int> patindromo(n, n, -1);

    cout << n - patin_rec(patitos, 0, n - 1, patindromo) << " ";

    string sol;

    reconstruir(patitos, patindromo, 0, n - 1, sol);
    
    cout << sol << '\n';

    return true;
}

int main() {

    while (resuelveCaso());

    return 0;
}