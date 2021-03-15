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

typedef pair<int, int> pelicula;

int maxTiempo(const vector<pelicula> & peliculas, int numPeliculas) {
    int numMinutos = 24 * 60 + 10;
    vector<int> tabla(numMinutos + 1, 0);
    for (int i = 1; i <= numPeliculas; i++) {
        for (int j = numMinutos; j > 0; j--) {
            if (peliculas[i - 1].first + peliculas[i - 1].second + 10 <= j) {
                tabla[j] = max(tabla[j], tabla[peliculas[i - 1].first] + peliculas[i - 1].second);
            }
        }
    }
    return tabla[numMinutos];
}

bool resuelveCaso() {
    int numPeliculas;
    cin >> numPeliculas;
    if (numPeliculas == 0) return false;

    int hora, minutos, duracion;
    char ignore;
    vector<pelicula> peliculas;

    for (int i = 0; i < numPeliculas; i++) {
        cin >> hora >> ignore >> minutos >> duracion;
        peliculas.push_back(pelicula(hora * 60 + minutos, duracion));
    }
    sort(peliculas.begin(), peliculas.end());

    cout << maxTiempo(peliculas, numPeliculas) << '\n';

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