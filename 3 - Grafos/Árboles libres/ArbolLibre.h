//
//  ArbolLibre.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef ARBOLLIBRE_H_
#define ARBOLLIBRE_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Grafo.h"

using namespace std;

class ArbolLibre {

public:

    ArbolLibre(Grafo const& g) : _esArbolLibre(false), _visitados(g.V(), false) {
        _esArbolLibre = dfs(g, 0) == g.V() && g.A() == g.V() - 1;
    }

    bool esArbolLibre() {
        return _esArbolLibre;
    }

private:

    bool _esArbolLibre;
    vector<bool> _visitados;

    int dfs(Grafo const& g, int v) {
        _visitados[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!_visitados[w])
                tam += dfs(g, w);
        }
        return tam;
    }

};

#endif /* ARBOLLIBRE_H_ */
