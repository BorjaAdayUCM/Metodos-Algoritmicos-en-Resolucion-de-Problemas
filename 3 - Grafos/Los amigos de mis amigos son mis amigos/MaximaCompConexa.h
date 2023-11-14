//
//  MaximaCompConexa.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef MAXIMACOMPCONEXA_H_
#define MAXIMACOMPCONEXA_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Grafo.h"

using namespace std;

class MaximaCompConexa {

    public:

        MaximaCompConexa(Grafo const& g) : _visitados(g.V(), false), _maximo(0) {
            for (int v = 0; v < g.V(); ++v) {
                if (!_visitados[v]) { // se recorre una nueva componente conexa
                int tam = dfs(g, v);
                _maximo = max(_maximo, tam);
                }
            }
        }

        int maximo() const {
            return _maximo;
        }

    private:

        vector<bool> _visitados;
        int _maximo; 

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

#endif /* MAXIMACOMPCONEXA_H_ */
