#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void resolver(int nDrones, int nBateriasG, int nBateriasP) {
    
    priority_queue<int> bateriasG, bateriasP;

    for (int i = 0; i < nBateriasG; i++) {
        int bateria;
        cin >> bateria;
        bateriasG.push(bateria);
    }

    for (int i = 0; i < nBateriasP; i++) {
        int bateria;
        cin >> bateria;
        bateriasP.push(bateria);
    }

    vector<int> sabados;
    while (!bateriasG.empty() && !bateriasP.empty()) {

        vector<int> bateriasGR, bateriasPR;
        int horasVuelo = 0, dron = 0;
        while (!bateriasG.empty() && !bateriasP.empty() && dron < nDrones) {
            if (bateriasG.top() < bateriasP.top()) bateriasPR.push_back(bateriasP.top() - bateriasG.top());
            else if (bateriasG.top() > bateriasP.top()) bateriasGR.push_back(bateriasG.top() - bateriasP.top());
            horasVuelo += bateriasG.top() > bateriasP.top() ? bateriasP.top() : bateriasG.top();
            bateriasG.pop(); bateriasP.pop();
            dron++;
        }
        for (int bateria : bateriasGR) bateriasG.push(bateria);
        for (int bateria : bateriasPR) bateriasP.push(bateria);

        sabados.push_back(horasVuelo);
    }

    for (int i = 0; i < sabados.size() - 1; i++) cout << sabados[i] << " ";
    cout << sabados[sabados.size() - 1] << '\n';
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int nDrones, nBateriasG, nBateriasP;

    cin >> nDrones;

    if (!std::cin)
        return false;

    cin >> nBateriasG >> nBateriasP;

    resolver(nDrones, nBateriasG, nBateriasP);

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
