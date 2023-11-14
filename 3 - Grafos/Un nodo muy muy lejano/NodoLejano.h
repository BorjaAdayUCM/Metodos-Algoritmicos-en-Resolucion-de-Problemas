//
//  NodoLejano.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef NODOLEJANO_H_
#define NODOLEJANO_H_

#include <queue>
#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Grafo.h"
#include <climits>

using namespace std;

class NodoLejano {

public:

    NodoLejano(Grafo const& g) : _g(g), _visitados(g.V(), false), _dist(g.V()) {}

    int nodosNoAlcanzablesDesde(int v, int ttl) {
        int nodosNoAlcanzables = 0;
        _visitados = vector<bool>(_g.V(), false);
        _dist = vector<int>(_g.V(), INT_MAX);
        bfs(_g, v);

        for (int i = 0; i < _g.V(); i++) {
            if (_dist[i] > ttl) nodosNoAlcanzables++;
        }
        return nodosNoAlcanzables;
    }

private:

    Grafo _g;
    vector<bool> _visitados;
    vector<int> _dist;


    void bfs(Grafo const& g, int s) {
        queue<int> q;
        _dist[s] = 0; _visitados[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!_visitados[w]) {
                    _dist[w] = _dist[v] + 1; 
                    _visitados[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

#endif /* NODOLEJANO_H_ */
