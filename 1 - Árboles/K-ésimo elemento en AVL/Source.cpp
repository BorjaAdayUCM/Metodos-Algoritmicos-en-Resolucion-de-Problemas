#include <iostream>
#include "TreeSet_AVL.h"
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {

    //Leer caso de prueba: cin>>...
    int nValores, elemento, nConsultas, consulta;
    Set<int> conjunto;

    cin >> nValores;
    if (nValores == 0) return false;
    
    for (int i = 0; i < nValores; i++) {
        cin >> elemento;
        conjunto.insert(elemento);
    }

    cin >> nConsultas;
    for (int i = 0; i < nConsultas; i++) {
        cin >> consulta;
        (consulta > conjunto.size()) ? cout << "??\n" : cout << conjunto.kesimo(consulta) << "\n";
    }
    cout << "---\n";

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