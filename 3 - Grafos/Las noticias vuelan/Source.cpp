#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "Noticias.h"

using namespace std;

bool resuelveCaso() { 
    int nUsuarios, nGrupos, nIndividuos, individuo1, individuo2;

    cin >> nUsuarios >> nGrupos; 

    if (!cin) return false;

    Grafo grafo = Grafo(nUsuarios);

    for (int i = 0; i < nGrupos; i++) {
        cin >> nIndividuos;
        if (nIndividuos == 1) cin >> individuo1;
        else if (nIndividuos >= 2) {
            cin >> individuo1 >> individuo2;
            for (int j = 2; j < nIndividuos; j++) {
                grafo.ponArista(individuo1 - 1, individuo2 - 1);
                individuo1 = individuo2;
                cin >> individuo2;
            }
            grafo.ponArista(individuo1 - 1, individuo2 - 1);
        }
        
    }

    Noticias noticias = Noticias(grafo);

    for (int i = 0; i < nUsuarios; i++) {
        cout << noticias.noticiasDesde(i) << " ";
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