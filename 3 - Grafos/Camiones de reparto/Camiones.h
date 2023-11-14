//
//  Camiones.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef CAMIONES_H_
#define CAMIONES_H_

#include <vector>
#include <iostream>
#include "GrafoValorado.h"

using namespace std;

class Camiones {

public:

    Camiones(GrafoValorado<int> g) : _g(g), _visitados(_g.V(), false) {}

    bool esPosible(int origen, int destino, int ancho) {
        _visitados = vector<bool>(_g.V(), false);
        _esPosible = false;
        dfs(origen, destino, ancho);
        return _esPosible;
    }

protected:

    GrafoValorado<int> _g;
    vector<bool> _visitados;
    bool _esPosible = false;

    void dfs(int origen, int destino, int ancho) {
        _visitados[origen] = true;
        for (auto w : _g.ady(origen)) {
            if (!_visitados[w.otro(origen)] && w.valor() >= ancho) {
                if (w.otro(origen) == destino) {
                    _esPosible = true;
                    return;
                }
                dfs(w.otro(origen), destino, ancho);
            }
        }
    }

};


#endif
