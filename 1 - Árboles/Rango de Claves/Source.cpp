#include <iostream>
#include "TreeMap_AVL.h"
#include <fstream>
#include <vector>

using namespace std;

vector <int> devuelveList(map<int, int> const& arbol, int & k1, int & k2) {
    vector<int> list;
    
    map<int, int>::const_iterator it = arbol.cbegin();
    while (it != arbol.cend() && it->clave < k1) ++it;
    while (it != arbol.cend() && it->clave <= k2) {
        list.push_back(it->clave);
        ++it;
    }

    return list;
}

bool resuelveCaso() {

    //Leer caso de prueba: cin>>...
    int nClaves, elemento, k1, k2;
    vector<int> list;
    map<int, int> arbol;

    cin >> nClaves;
    if (nClaves == 0)
        return false;

    for (int i = 0; i < nClaves; i++) {
        cin >> elemento;
        arbol.insert(elemento);
    }
    cin >> k1 >> k2;

    list = arbol.entre(k1, k2);

    for (int i : list) {
        cout << i << " ";
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