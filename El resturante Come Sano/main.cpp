#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
	vector<int> sol;
	int k;
	vector<bool> asientos_asignados;
	double beneficio; // valor acumulado
	double beneficio_opt; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_opt > beneficio_opt;
	}
};


//True si al sentar la persona X.k en el asiento no produce conflicto con las anteriores
bool esSolParcialValida(vector<vector<double>> const& distancias, vector<vector<int>> const& allegados, Nodo const& X,int asiento,int&num_parejas) {
	for (int i = 0; i < X.k; i++) {
		//si no son allegados, la distancia debe de ser > 2
		if (allegados[X.k][i] == 0 && distancias[asiento][X.sol[i]] < 2) {
			return false;
		}
		//si son allegados y su distancia es < que 2 tenemos una pareja mas
		if (allegados[X.k][i] == 1 && distancias[asiento][X.sol[i]] < 2) {
			num_parejas++;
		}
	}
	return true;
}

void compra_rp(vector<vector<double>> const& distancias, vector<vector<int>> const& allegados,vector<int>const& opt,
	int m,int n,vector<int> sol_mejor, int& coste_mejor) {
	// se genera la raíz
	Nodo Y;
	Y.asientos_asignados = vector<bool>(n, false);
	Y.sol = vector<int>(m);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_opt = opt[0];
	priority_queue<Nodo> cola;
	cola.push(Y);
	coste_mejor = INT_MIN;

	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_opt > coste_mejor) {
		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		++X.k;
		//recorremos todos los vertices por cada persona
		for (int i = 0; i < n; i++) {
			int num_parejas=0;
			if (!X.asientos_asignados[i] && esSolParcialValida(distancias,allegados,X,i,num_parejas)) {
				//marcamos
				X.sol[X.k] = i;
				X.asientos_asignados[i] = true;
				X.beneficio = Y.beneficio + num_parejas;
				X.beneficio_opt = X.beneficio + opt[X.k];
				if (X.k == m - 1) {
					if (X.beneficio > coste_mejor) {
						sol_mejor = X.sol;
						coste_mejor = X.beneficio;
					}
				}
				else if (X.beneficio_opt > coste_mejor) {
					cola.push(X);
				}

				X.asientos_asignados[i] = false;	
			}
		}
	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

	int n_asientos, m_comensales;
	cin >> n_asientos >> m_comensales;

	vector<vector<double>> distancias(n_asientos, vector<double>(n_asientos));
	vector<vector<int>> allegados(m_comensales, vector<int>(m_comensales));
	vector<int> opt(m_comensales);
	for (int i = 0; i < n_asientos; i++) {
		for (int j = 0; j < n_asientos; j++) {
			cin >> distancias[i][j];
		}
	}

	for (int i = 0; i < m_comensales; i++) {
		for (int j = 0; j < m_comensales; j++) {
			cin >> allegados[i][j];
		}
	}
	//Calculamos los costes estimados sumando las allegadas restantes(recorrido triangulo inferior de la matriz para las personas restantes)
	int num_allegados = 0;
	for (int i = m_comensales-1; i >=0; i--) {
		opt[i] = num_allegados;
		for (int j = 0; j < i; j++) {
			if (allegados[i][j] == 1)
				num_allegados++;				
		}
	}
	vector<int> sol(m_comensales);
	int coste_mejor;
	compra_rp(distancias, allegados,opt,m_comensales,n_asientos, sol, coste_mejor);

	if (coste_mejor <= 0)
		cout << "CANCELA\n";
	else
		cout <<"PAREJAS "<< coste_mejor << '\n';
}



int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}