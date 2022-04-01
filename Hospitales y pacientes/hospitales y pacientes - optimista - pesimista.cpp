//Borja Aday Guadalupe Luis
//Oscar Morujo Fernández

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
    int k; //Nivel actual
    vector<int> marcaje; // Capacidades actuales de cada hospital
    int coste; // Coste actual de la solucion
    int coste_optimista; // Coste estimado.
    int coste_pesimista;

    //Cola de minimos
    bool operator<(Nodo const& otro) const {
        return otro.coste_optimista < coste_optimista;
    }

};

//Completamos una solución cualquiera valida desde el nivel k+1.
int coste_pesimista(vector<vector<int>> const& distancias, Nodo const& nodo, int const& N, int const& M) {
    int coste = nodo.coste;
    vector<int> marcaje_aux(nodo.marcaje);
    for (int i = nodo.k + 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (marcaje_aux[j] > 0) {
                marcaje_aux[j]--;
                coste += distancias[i][j];
                break;
            }
        }
    }
    return coste;
}


// Tenemos precalculados la mínima distancia de cada persona a su hospital mas cercano.
// MinDistancias tiene precalculadas las sumas parciales para hacerlo constante.
// Coste: O(1)
int coste_optimista(vector<int> const& minDistancias, Nodo const& nodo) {
    if (nodo.k == minDistancias.size() - 1) return nodo.coste;
    return nodo.coste + minDistancias[nodo.k + 1];
}


//Espacio de soluciones: N^M
// El espacio de soluciones completo sería Sum: (i = 0 hasta N) (M^i)
// Las distancias vienen multiplicadas por 2 desde la lectura.
void resolver(vector<vector<int>> const& distancias, vector<int> const& minDistancias, int const& N, int const& M, vector<int> const& capacidades, int& coste_mejor) {

    Nodo Y;
    Y.k = -1;
    Y.marcaje = vector<int>(capacidades);
    Y.coste = 0;
    Y.coste_optimista = coste_optimista(minDistancias, Y); 
    coste_mejor = coste_pesimista(distancias, Y, N, M); //Se inicializa al INT_MAX porque estamos minimizando.
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().coste_optimista <= coste_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        for (int i = 0; i < M; i++) {
            //Comprobamos si podemos asignar la persona k al hospital i (si es factible).
            if (X.marcaje[i] > 0) {
                //Marcamos el hijo con sus nuevas propiedades.
                X.marcaje[i]--;
                X.coste += distancias[X.k][i];
                X.coste_optimista = coste_optimista(minDistancias, X);

                //Comprobamos si es prometedor
                if (X.k == N - 1) {
                    if (X.coste <= coste_mejor) {
                        coste_mejor = X.coste;
                    }
                }
                else {
                    if (X.coste_optimista <= coste_mejor) {
                        cola.push(X);
                        X.coste_pesimista = coste_pesimista(distancias, X, N, M);
                        if (X.coste_pesimista < coste_mejor) {
                            coste_mejor = X.coste_pesimista;
                        }
                    }
                }

                //Desmarcamos para dejarlo como estaba.
                X.marcaje[i] = Y.marcaje[i];
                X.coste = Y.coste;
            }

        }

    }

}

void resuelveCaso() {
    int N, M, capacidad, distancia, coste_mejor;

    cin >> N >> M;

    vector<vector<int>> distancias;
    vector<int> capacidades;
    vector<int> minDistancias;

    for (int i = 0; i < M; i++) {
        cin >> capacidad;
        capacidades.push_back(capacidad);
    }

    for (int i = 0; i < N; i++) {
        int min = INT_MAX;
        vector<int> vectorDistancias;
        for (int j = 0; j < M; j++) {
            cin >> distancia;
            distancia *= 2;
            vectorDistancias.push_back(distancia);
            if (distancia < min) min = distancia;
        }
        distancias.push_back(vectorDistancias);
        minDistancias.push_back(min);
    }

    for (int i = N - 2; i >= 0; i--) {
        minDistancias[i] += minDistancias[i + 1];
    }

    resolver(distancias, minDistancias, N, M, capacidades, coste_mejor);

    cout << coste_mejor << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}