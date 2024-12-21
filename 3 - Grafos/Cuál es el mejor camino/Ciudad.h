//
//  Ciudad.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef CIUDAD_H_
#define CIUDAD_H_

#include <vector>
#include <iostream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

class Ciudad {

public:
    Ciudad(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), minCalles(g.V(), INF), ult(g.V()), pq(g.V()) {
        dist[origen] = 0;
        minCalles[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }

    int distancia(int v) const { return dist[v]; }

    int minimasCalles(int v) const { return minCalles[v]; }

    int numCallesMinDistancia(int v) const { return numCallesCamino(v); }

private:

    const int INF = numeric_limits<int>::max();
    int origen;
    vector<int> dist;
    vector<int> minCalles;
    vector<AristaDirigida<int>> ult;
    IndexPQ<int> pq;

    int numCallesCamino(int v) const {
        AristaDirigida<int> a;
        int tam = 0;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()]) tam++;
        return tam;
    }

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (minCalles[w] > minCalles[v] + 1) {
            minCalles[w] = minCalles[v] + 1;
        }
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
    }
};


#endif
