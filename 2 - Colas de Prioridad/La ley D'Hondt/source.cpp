//Borja Aday Guadalupe Luis
//Marcos Matute Fernandez

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/*
Estructura para almacenar los datos del partidos
*/
struct partido {
    int id;
    double k;
    double votos;
};

/*
Sobrecargamos el operador menor para que se ordene bien la cola:
Primero comparamos el factor k, a igualdad de este comparamos los votos y a igualdad de estos dos comparamos la id
*/
bool operator<(const partido &partido1, const partido &partido2) {
    return partido1.k < partido2.k || (partido1.k == partido2.k && partido1.votos < partido2.votos) ||
        (partido1.k == partido2.k && partido1.votos == partido2.votos && partido1.id > partido2.id);
}


/*
Para resolver el problema primero rellenamos los datos y lo que vamos haciendo es por cada escaño cogemos el top lo guardamos en una variable auxiliar
y lo borramos de la cola le aumentamos en 1 el escaño (los tenemos introducidos en un vector para poder mostrarlos en orden) volvemos a calcular su factor k
y lo volvemos a meter en la cola para volver a participar en el reparto del siguiente escaño.

El coste en espacio es de O(C) (el coste es 2c, la cola tiene un tamaño C y el vector de escaños de tamaño C)
El coste en tiempo es de O(N*log(N)) (el coste es el bucle que reparte cada escaño (N) * el coste de la insercion que es log(N))

*/
bool resuelveCaso() {
    int C, N;  //Candidaturas, escanhos por repartir

    cin >> C >> N;
    if (C == 0 && N == 0)
        return false;

    priority_queue<partido> cola;
    vector<int> escanhos(C, 0);

    for (int i = 0; i < C; i++) {
        double votos;
        cin >> votos;
        cola.push({ i, votos, votos });
    }

    //Escogemos el primero de la cola, le añadimos su escaño, actualizamos su factor k y lo volvemos a meter en la cola.
    for (int i = 0; i < N; i++) {
        partido aux = cola.top(); cola.pop();
        escanhos[aux.id]++;
        aux.k = aux.votos / (1 + escanhos[aux.id]);
        cola.push(aux);
    }

    //Muestra los escaños de cada candidatura en orden
    for (int i = 0; i < C; i++) {
        cout << escanhos[i] << ' ';
    }
    cout << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}