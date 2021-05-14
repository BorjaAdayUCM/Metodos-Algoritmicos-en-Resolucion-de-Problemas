//Borja Aday Guadalupe Luis

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <ostream>

using namespace std;

int cuantasFormas(vector<vector<bool>> & mapa, int N, int M) {

    vector<vector<int>> tabla(N, vector<int>(M));

    tabla[0][0] = 1;

    //Rellenamos los datos
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mapa[i][j]) {
                if (i > 0 && j > 0) tabla[i][j] = tabla[i - 1][j] + tabla[i][j - 1];
                else if (i > 0) tabla[i][j] = tabla[i - 1][j];
                else if (j > 0) tabla[i][j] = tabla[i][j - 1];
            }
            else tabla[i][j] = 0;
        }
    }

    return tabla[N - 1][M - 1];
}


//Resuelve un caso de prueba, leyendo de la entrada la configuración, y escribiendo la respuesta.
bool resuelveCaso() {

    int N, M;

    cin >> N;

    if (!std::cin) return false;

    cin >> M;

    vector<vector<bool>> mapa(N, vector<bool>(M));
    char c;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> c;
            if (c == '.') mapa[i][j] = true;
            else mapa[i][j] = false;
        }
        
    }

    cout << cuantasFormas(mapa, N, M) << '\n';

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
    system("PAUSE");
#endif
    return 0;
}
