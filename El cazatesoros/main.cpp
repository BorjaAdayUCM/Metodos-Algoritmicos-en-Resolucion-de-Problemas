#include <iostream>
#include <algorithm>
#include <numeric>
#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

vector<int> cofresRecuperados(int const maxSegundos, vector<int> const & profundidades, vector<int> const& valores, EntInf & oroMax) {
    int N = profundidades.size();
    Matriz<EntInf> tabla(N + 1, maxSegundos + 1, 0);
    
    tabla[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        tabla[i][0] = 0;
        for (int j = maxSegundos; j >= 1; j--) {
            if (j < 3*profundidades[i - 1]) tabla[i][j] = tabla[i - 1][j];
            else tabla[i][j] = max(tabla[i - 1][j], tabla[i - 1][j - 3*profundidades[i - 1]] + valores[i - 1]);
        }
    }
    
    oroMax = tabla[N][maxSegundos];

    vector<int> sol;
    if (tabla[N][maxSegundos] != 0) {
        int i = N, j = maxSegundos;
        while (i > 0) {
            if (3 * profundidades[i - 1] <= j && tabla[i][j] != tabla[i - 1][j] /*... && tabla[i][j] == tabla[i - 1][j - 3 * profundidades[i - 1]] + valores[i - 1]*/) {
                sol.push_back(i - 1);
                j = j - 3 * profundidades[i - 1];
            }
            --i;
        }
    }

    return sol;
}

bool resuelveCaso() {

    int maxSegundos, numCofres, profundidad, valor;
    vector<int> profundidades = vector<int>(), valores = vector<int>();

    cin >> maxSegundos;

    if (!std::cin) return false;

    cin >> numCofres;

    for (int i = 0; i < numCofres; i++) {
        cin >> profundidad >> valor;
        profundidades.push_back(profundidad);
        valores.push_back(valor);
    }

    EntInf oroMax = 0;

    vector<int> solucion = cofresRecuperados(maxSegundos, profundidades, valores, oroMax);
    if (oroMax == 0) cout << "0\n0\n"; 
    else {
        cout << oroMax << '\n' << solucion.size() << '\n';
        for (int i = solucion.size() - 1; i >= 0; i--) {
            cout << profundidades[solucion[i]] << " " << valores[solucion[i]] << '\n';
        }

    }
    cout << "---\n";
    return true;
}

int main() {

    while (resuelveCaso());

    return 0;
}