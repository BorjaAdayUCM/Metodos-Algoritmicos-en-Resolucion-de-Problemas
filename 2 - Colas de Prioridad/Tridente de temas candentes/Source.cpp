#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "IndexPQ.h"

using namespace std;

struct prioridad {
    int citas;
    int llegada;

    prioridad operator += (const prioridad& rhs) {
        citas += rhs.citas;
        llegada = rhs.llegada;
        return *this;
    }

    prioridad operator -= (const prioridad& rhs) {
        citas -= rhs.citas;
        llegada = rhs.llegada;
        return *this;
    }

    bool operator<(prioridad const& a) const {
        return citas > a.citas || (citas == a.citas && llegada > a.llegada);
    }

};

void resolver(int nEventos) {

    IndexPQ<string, prioridad, less<prioridad>> tendencias;

    string evento, tendencia;
    int citas;

    for (int i = 0; i < nEventos; i++) {
        cin >> evento;

        if (evento == "C") {
            cin >> tendencia >> citas;
            tendencias.update(tendencia, { citas, i }, true);
        }
        else if (evento == "E") {
            cin >> tendencia >> citas;
            tendencias.update(tendencia, { citas, i }, false);
        }
        else {
            vector<pair<string, prioridad>> recuperaTendencias;
            for (int i = 0; i < 3 && !tendencias.empty(); i++) {
                cout << i + 1 << " " << tendencias.top().elem << '\n';
                recuperaTendencias.push_back({ tendencias.top().elem, tendencias.top().prioridad });
                tendencias.pop();
            }
            for (int i = 0; i < recuperaTendencias.size(); i++) {
                tendencias.push(recuperaTendencias[i].first, recuperaTendencias[i].second);
            }
        }
    }
    cout << "---\n";
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int nEventos;

    cin >> nEventos;

    if (!std::cin)
        return false;

    resolver(nEventos);

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
