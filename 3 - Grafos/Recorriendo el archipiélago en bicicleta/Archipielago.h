//
//  Camiones.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef ARCHIPIELAGO_H_
#define ARCHIPIELAGO_H_

#include <vector>
#include <iostream>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

template <typename Valor>

class Archipielago {

private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
	bool _esConexo = false;

public:

	bool esConexo() {
		return _esConexo ;
	}

	Valor costeARM() const {
		return coste;
	}

	std::vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}

	Archipielago(GrafoValorado<Valor> const& g) : coste(0) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) {
					_esConexo = true;
					break;
				}
			}
		}
	}
};


#endif
