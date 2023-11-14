//
//  MaximaCompConexa.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef NOTICIAS_H_
#define NOTICIAS_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Grafo.h"

using namespace std;

class Noticias {

    public:

        Noticias(Grafo const& g) : _visitados(g.V(), false), _tam(g.V(), 1) {
            for (int v = 0; v < g.V(); ++v) {
                if (!_visitados[v]) {
                    _tam[v] = dfs(g, v);
                    for (int vertice : _visitadosdfs) _tam[vertice] = _tam[v];
                    _visitadosdfs.clear();
                }
            }
        }

        int noticiasDesde(int v) const {
            return _tam[v];
        }

    private:

        vector<bool> _visitados;
        vector<int> _tam;
        vector<int> _visitadosdfs;

    int dfs(Grafo const& g, int v) {
        _visitadosdfs.push_back(v);
        _visitados[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!_visitados[w]) {
                tam += dfs(g, w);
            }
        }
        return tam;
    }
};

#endif /* NOTICIAS_H_ */
