#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct Cliente {
    int tiempo;
    int caja;
};

bool operator<(Cliente const& a, Cliente const& b) {
    return a.tiempo < b.tiempo || (a.tiempo == b.tiempo && a.caja < b.caja);
}

int resolver(int nCajas, int nClientes) {

    if (nCajas == 1 || nCajas > nClientes) {
        int tiempo;
        for (int i = 0; i < nClientes; i++) cin >> tiempo;
        if (nCajas == 1) return 1;
        else return nClientes + 1;
    }

    PriorityQueue<Cliente> cola;

    for (int i = 0; i < nCajas; i++) {
        int tiempo, caja;
        cin >> tiempo;
        cola.push({ tiempo, i + 1 });
    }

    for (int i = 0; i < nClientes - nCajas; i++) {
        int tiempo, tiempoTranscurrido = cola.top().tiempo, cajaLibre = cola.top().caja; cola.pop();
        cin >> tiempo;
        cola.push({ tiempo + tiempoTranscurrido, cajaLibre });
    }

    return cola.top().caja;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int nCajas, nClientes;

    cin >> nCajas >> nClientes;

    if (nCajas == 0 && nClientes == 0) return false;

    cout << resolver(nCajas, nClientes) << '\n';

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
