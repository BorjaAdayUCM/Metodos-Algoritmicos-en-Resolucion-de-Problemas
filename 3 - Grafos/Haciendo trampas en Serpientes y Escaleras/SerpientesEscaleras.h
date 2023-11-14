//
//  SerpientesEscaleras.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef SERPIENTESESCALERAS_H_
#define SERPIENTESESCALERAS_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class SerpientesEscaleras {

	public:

		SerpientesEscaleras(int const& tam, int const& k, vector<int> const& serpEsc) : _V(tam*tam), _visitados(_V + 1, false), _serpEsc(serpEsc), _caminoMin(INT_MAX), _K(k) {
            calculaCaminoMin();
		}
			
		int caminoMin() const { 
			return _caminoMin; 
		}

	private:

		int _V, _caminoMin, _K; // 
		vector<bool> _visitados;
		vector<int> _serpEsc;

        struct vertice {
            int vertice;
            int prioridad;
        };

        struct comparador {
            bool operator() (vertice const& a, vertice const& b) {
                return a.prioridad > b.prioridad || a.prioridad == b.prioridad && a.vertice > b.vertice;
            }
        };

		void calculaCaminoMin() {
            priority_queue<vertice, vector<vertice>, comparador> cola;

            cola.push({1, 0});

            while (!cola.empty() && cola.top().prioridad < _caminoMin) {

                auto vertice = cola.top(); cola.pop();

                _visitados[vertice.vertice] = true;

                if (vertice.vertice == _V)
                    _caminoMin = vertice.prioridad;

                for (int i = 1; i <= _K && vertice.vertice + i <= _V; i++) {

                    if (!_visitados[vertice.vertice + i]) {

                        if (_serpEsc[vertice.vertice + i] != -1)
                            cola.push({ _serpEsc[vertice.vertice + i], vertice.prioridad + 1});
                        else
                            cola.push({ vertice.vertice + i, vertice.prioridad + 1 });
                    }

                    _visitados[vertice.vertice + i] = true;
                }
            }
		}


};

#endif /* SERPIENTESESCALERAS_H_ */
