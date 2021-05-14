
#include<iostream>
#include<vector>
#include <fstream>
#include <queue>
#include<climits>
#include<algorithm>

using namespace std;

struct Nodo {
    vector<bool> asientos_asignados;
    bool hermano_invitado;
    int n_ocurrencias;
    int k;
    int num_libres;
    double beneficio;
    double beneficio_opt; // estimación, prioridad
    bool operator<(Nodo const& otro) const { return otro.beneficio_opt > beneficio_opt; }
};

bool esFactible(vector<vector<int>>const& satisfacciones, Nodo const& X, int pos_hermano, int m_asientos) {
    if (X.hermano_invitado) return true;
    if (!X.hermano_invitado && X.num_libres <= 0) return false;
    for (int i = 0; i < m_asientos; i++) {
        if (satisfacciones[i][pos_hermano] >= 0 && !X.asientos_asignados[i] && (X.n_ocurrencias > 0 || pos_hermano % m_asientos != i))
            return true;
    }

    return false;
}

int coste_opt(vector<int> const& maximos, Nodo const& X, int& n_personas) {
    if (X.k + 1 == n_personas) return X.beneficio;
    return X.beneficio + maximos[X.k + 1];
}

int coste_pes_hermano(vector<vector<int>> const& satisfacciones, Nodo const& X, int m_asientos, int n_personas, int pos_hermano) {
    int pes = X.beneficio;
    bool invitado = X.hermano_invitado;
    if (!invitado && X.num_libres > 0) {
        int asiento = 0;
        while (asiento < m_asientos && (X.asientos_asignados[asiento] || satisfacciones[asiento][pos_hermano] < 0 || (X.n_ocurrencias == 0 && pos_hermano % m_asientos == asiento))) asiento++;
        if (asiento < m_asientos) {
            invitado = true;
            pes += satisfacciones[asiento][pos_hermano];
        }
    }

    if (!invitado) return 0;

    return pes;
}



void funcionarios(vector<vector<int>>const& satisfacciones, vector<int>const& maximos, int& m_asientos,
    int& n_personas, int& pos_hermano, int& mejor_beneficio, vector<int>& sol_mejor) {

    Nodo Y;
    Y.asientos_asignados = vector<bool>(m_asientos, false);
    Y.k = -1;
    Y.beneficio = 0;
    Y.num_libres = m_asientos;
    Y.n_ocurrencias = (int)((int)m_asientos / (int)3);
    Y.hermano_invitado = false;
    Y.beneficio_opt = coste_opt(maximos, Y, n_personas);
    mejor_beneficio = INT_MIN;
    priority_queue<Nodo> cola;
    cola.push(Y);

    mejor_beneficio = coste_pes_hermano(satisfacciones, Y, m_asientos, n_personas, pos_hermano);


    while (!cola.empty() && cola.top().beneficio_opt >= mejor_beneficio) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k += 1;

        //Por cada persona probamos a asignarle un asiento
        for (int i = 0; i < m_asientos; i++) {
            if (!X.asientos_asignados[i] && satisfacciones[i][X.k] >= 0 && (X.n_ocurrencias > 0 || X.k % m_asientos != i)) {
                if (X.k % m_asientos == i) {
                    X.n_ocurrencias--;
                }

                X.num_libres--;
                X.asientos_asignados[i] = true;
                X.beneficio = Y.beneficio + satisfacciones[i][X.k];
                X.beneficio_opt = coste_opt(maximos, X, n_personas);

                if (X.k == pos_hermano) {
                    X.hermano_invitado = true;
                }

                if (X.beneficio_opt >= mejor_beneficio) {
                    if (X.k == n_personas - 1 || X.num_libres <= 0) {
                        if (X.hermano_invitado && X.beneficio > mejor_beneficio) {
                            mejor_beneficio = X.beneficio;
                        }
                    }
                    else if (esFactible(satisfacciones, X, pos_hermano, m_asientos)) {
                        cola.push(X);
                        mejor_beneficio = max(mejor_beneficio, coste_pes_hermano(satisfacciones, X, m_asientos, n_personas, pos_hermano));
                    }
                }

                X.asientos_asignados[i] = false;
                X.beneficio = Y.beneficio;
                X.num_libres++;
                if (X.k == pos_hermano) {
                    X.hermano_invitado = false;
                }
                if (X.k % m_asientos == i) {
                    X.n_ocurrencias++;
                }
            }
        }

        if (X.k != pos_hermano) {
            X.beneficio = Y.beneficio;
            X.beneficio_opt = coste_opt(maximos, X, n_personas);
            if (X.beneficio_opt >= mejor_beneficio) {
                if (X.k == n_personas - 1 || X.num_libres <= 0) {
                    if (X.hermano_invitado && X.beneficio > mejor_beneficio) {
                        mejor_beneficio = X.beneficio;
                    }
                }
                else if (esFactible(satisfacciones, X, pos_hermano, m_asientos)) {
                    cola.push(X);
                    mejor_beneficio = max(mejor_beneficio, coste_pes_hermano(satisfacciones, X, m_asientos, n_personas, pos_hermano));
                }
            }
        }

    }
}



bool resuelveCaso(int n_personas) {
    int m_asientos;
    int pos_hermano;
    cin >> m_asientos >> pos_hermano;

    vector<vector<int>> satisfacciones(m_asientos, vector<int>(n_personas)); //matriz m*n

    vector<int> maximos(n_personas, 0);// array con la maxima satisfacion de cada asiento

    for (int i = 0; i < m_asientos; i++) {
        for (int j = 0; j < n_personas; j++) {
            cin >> satisfacciones[i][j];
            if (satisfacciones[i][j] > maximos[j]) maximos[j] = satisfacciones[i][j];

        }
    }
    int mejor_tiempo;
    vector<int> sol_mejor(n_personas);

    for (int i = n_personas - 2; i >= 0; i--) {
        maximos[i] += maximos[i + 1];
    }

    funcionarios(satisfacciones, maximos, m_asientos, n_personas, pos_hermano, mejor_tiempo, sol_mejor);
    if (mejor_tiempo < 0) cout << "0\n";
    else cout << mejor_tiempo << '\n';

    return true;

}
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int n;
    cin >> n;
    while (n != -1) {
        resuelveCaso(n);
        cin >> n;
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
