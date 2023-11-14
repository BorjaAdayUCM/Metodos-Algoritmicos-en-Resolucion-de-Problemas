//
//  OrdenTopologico.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef ORDENTOPOLOGICO_H_
#define ORDENTOPOLOGICO_H_

#include <queue>
#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Digrafo.h"
#include <climits>
#include <deque>

using namespace std;

class OrdenTopologico {

	public:
		
		OrdenTopologico(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), ant(g.V()), _hayCiclo(false) {
			for (int v = 0; v < g.V(); ++v)
				if (!visit[v])
					dfs(g, v);
		}
		
		deque<int> const& orden() const {
			return _orden;
		}

		bool const& hayCiclos() const {
			return _hayCiclo;
		}

	private:
		vector<bool> visit;
		deque<int> _orden; 
		vector<int> ant; 
		vector<bool> apilado;
		bool _hayCiclo;

		void dfs(Digrafo const& g, int v) {
			apilado[v] = true;
			visit[v] = true;
			for (int w : g.ady(v)) {
				if (_hayCiclo) // si hemos encontrado un ciclo terminamos
					return;
				if (!visit[w]) { // encontrado un nuevo vértice, seguimos
					ant[w] = v; dfs(g, w);
				}
				else if (apilado[w]) {
					_hayCiclo = true;
				}
			}
			apilado[v] = false;
			_orden.push_front(v);
		}

};

#endif /* ORDENTOPOLOGICO_H_ */