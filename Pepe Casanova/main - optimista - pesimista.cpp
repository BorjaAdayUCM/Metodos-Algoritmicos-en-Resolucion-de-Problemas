#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool sortbydensity(const pair<double, double>& a, const pair<double, double>& b) {
    return ((a.second / a.first) > (b.second / b.first));
}

struct Nodo {
    int k;
    double duracion1;
    double duracion2;
    double beneficio;
    double beneficio_optimista;
    double beneficio_pesimista;

    bool operator<(Nodo const& otro) const {
        return otro.beneficio_optimista > beneficio_optimista;
    }

};

double beneficio_optimista(vector<pair<double, double>> const& canciones, Nodo const& nodo, double const& N) {
    double beneficio = nodo.beneficio, duracion = nodo.duracion1 + nodo.duracion2, i = nodo.k + 1;
    while (i < N && canciones[i].first <= duracion) {
        beneficio += canciones[i].second;
        duracion -= canciones[i].first;
        i++;
    }
    if (i < N) {
        beneficio += ((canciones[i].second * duracion) / canciones[i].first);
    }
    return beneficio;
}



double beneficio_pesimista(vector<pair<double, double>> const& canciones, Nodo const& nodo, double const& N) {
    double beneficio = nodo.beneficio, duracion1 = nodo.duracion1, duracion2 = nodo.duracion2;
    for (double i = nodo.k + 1; i < N && (duracion1 + duracion2 > 0); i++) {
        if (canciones[i].first <= duracion1) {
            beneficio += canciones[i].second;
            duracion1 -= canciones[i].first;
        }
        else if (canciones[i].first <= duracion2) {
            beneficio += canciones[i].second;
            duracion2 -= canciones[i].first;
        }
    }
    return beneficio;
}

void resolver(vector<pair<double, double>> const& canciones, double const& duracionCara, double & beneficio_mejor) {

    double N = canciones.size();

    Nodo Y;
    Y.k = -1;
    Y.duracion1 = duracionCara;
    Y.duracion2 = duracionCara;
    Y.beneficio = 0;
    Y.beneficio_optimista = beneficio_optimista(canciones, Y, N);
    beneficio_mejor = beneficio_pesimista(canciones, Y, N);
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().beneficio_optimista >= beneficio_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        //Primera cara
        if (canciones[X.k].first <= X.duracion1) {
            X.duracion1 = Y.duracion1 - canciones[X.k].first;
            X.beneficio = Y.beneficio + canciones[X.k].second;

            if (X.k == N - 1) {
                beneficio_mejor = X.beneficio;
            }
            else {
                cola.push(X);
            }

            X.duracion1 += canciones[X.k].first;
            X.beneficio -= canciones[X.k].second;
        }

        //Segunda cara
        if (canciones[X.k].first <= X.duracion2 && X.duracion1 != X.duracion2) {
            X.duracion2 -= canciones[X.k].first;
            X.beneficio += canciones[X.k].second;

            if (X.k == N - 1) {
                beneficio_mejor = X.beneficio;
            }
            else {
                cola.push(X);
            }

            X.duracion2 += canciones[X.k].first;
            X.beneficio -= canciones[X.k].second;
        }

        //No escogerla
        X.beneficio_optimista = beneficio_optimista(canciones, X, N);

        if (X.beneficio_optimista >= beneficio_mejor) {
            if (X.k == N - 1) {
                beneficio_mejor = X.beneficio;
            }
            else {
                cola.push(X);
                X.beneficio_pesimista = beneficio_pesimista(canciones, X, N);
                if (X.beneficio_pesimista > beneficio_mejor) beneficio_mejor = X.beneficio_pesimista;
            }
        }
    }

}

bool resuelveCaso() {
    double N, duracionCara, beneficio_mejor = 0, duracion, puntuacion;

    cin >> N;
    
    if (N == 0) return false;

    cin >> duracionCara;

    vector<pair<double, double>> canciones;

    for (double i = 0; i < N; i++) {
        cin >> duracion >> puntuacion;
        canciones.push_back(make_pair(duracion, puntuacion));
    }

    sort(canciones.begin(), canciones.end(), sortbydensity);

    resolver(canciones, duracionCara, beneficio_mejor);

    cout << beneficio_mejor << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}