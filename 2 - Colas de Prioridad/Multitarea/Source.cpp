#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct Tarea {
    int inicio;
    int duracion;
    int periodo;
    bool periodica;
};

bool operator<(Tarea const& a, Tarea const& b) {
    return a.inicio < b.inicio || (a.inicio == b.inicio && a.duracion > b.duracion);
}

bool resolver(int tareasUnicas, int tareasRepetitivas, int tiempo) {
    
    PriorityQueue<Tarea> cola;

    for (int i = 0; i < tareasUnicas; i++) {
        int ini, fin;
        cin >> ini >> fin;
        cola.push({ ini, fin - ini, 0, false });
    }

    for (int i = 0; i < tareasRepetitivas; i++) {
        int ini, fin, periodo;
        cin >> ini >> fin >> periodo;
        cola.push({ ini, fin - ini, periodo, true });
    }

    while (!cola.empty() && cola.top().inicio <= tiempo) {
        Tarea t = { cola.top().inicio, cola.top().duracion, cola.top().periodo, cola.top().periodica }; cola.pop();
        int finTarea = (t.inicio + t.duracion > tiempo) ? tiempo : t.inicio + t.duracion;
        if (!cola.empty() && finTarea > cola.top().inicio) return true;
        if (t.periodica) cola.push({ t.inicio + t.periodo, t.duracion, t.periodo, t.periodica });
    }

    return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int tareasUnicas, tareasRepetitivas, tiempo;

    cin >> tareasUnicas;

    if (!std::cin)
        return false;

    cin >> tareasRepetitivas >> tiempo;

    if (resolver(tareasUnicas, tareasRepetitivas, tiempo)) cout << "SI\n";
    else cout << "NO\n";


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
