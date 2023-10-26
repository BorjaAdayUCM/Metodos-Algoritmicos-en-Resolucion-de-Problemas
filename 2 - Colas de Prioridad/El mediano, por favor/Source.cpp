#include <iostream>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"

using namespace std;

void resolver(int nEventos) {

    priority_queue<int> menores;
    PriorityQueue<int> mayores;

    int num;

    for (int i = 0; i < nEventos; i++) {

        cin >> num;

        if (num == 0) {
            if (menores.empty()) cout << "ECSA ";
            else {
                cout << menores.top() << " "; menores.pop();
                if (mayores.size() > menores.size()) {
                    menores.push(mayores.top()); mayores.pop();
                }
            }
        }
        else {
            if (menores.empty() || num < menores.top()) {
                menores.push(num);
                if (menores.size() > mayores.size() + 1) {
                    mayores.push(menores.top()); menores.pop();
                }
            }
            else {
                mayores.push(num);
                if (mayores.size() > menores.size()) {
                    menores.push(mayores.top()); mayores.pop();
                }
            }
        }
    }
    cout << '\n';
}

bool resuelveCaso() {

    int nEventos;

    cin >> nEventos;

    if (!std::cin)
        return false;

    resolver(nEventos);

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