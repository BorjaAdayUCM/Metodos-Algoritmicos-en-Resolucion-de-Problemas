#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include "OrdenTopologico.h"
#include <deque>

using namespace std;


bool resuelveCaso() {

    Digrafo grafo = Digrafo(cin, 1);

    if (!std::cin)
        return false;

    OrdenTopologico tareas = OrdenTopologico(grafo);
    deque<int> tareasOrdenadas = tareas.orden();

    if (tareas.hayCiclos()) cout << "Imposible";
    else {
        for (int tarea : tareasOrdenadas) {
            cout << tarea + 1 << ' ';
        }
    }
    cout << '\n';

    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}