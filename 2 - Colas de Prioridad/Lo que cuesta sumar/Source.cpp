#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

bool resuelveCaso() {
    
    long long int nSumandos, sumando, esfuerzoTotal = 0, sumando1, sumando2;


    cin >> nSumandos;

    if (nSumandos == 0) return false;

    PriorityQueue<long long int> cola;

    for (int i = 0; i < nSumandos; i++) {
        cin >> sumando;
        cola.push(sumando);
    }

    while(cola.size() > 1) {
        sumando1 = cola.top(); cola.pop();
        sumando2 = cola.top(); cola.pop();
        esfuerzoTotal += sumando1 + sumando2;
        cola.push(sumando1 + sumando2);
    }

    cout << esfuerzoTotal << '\n';

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