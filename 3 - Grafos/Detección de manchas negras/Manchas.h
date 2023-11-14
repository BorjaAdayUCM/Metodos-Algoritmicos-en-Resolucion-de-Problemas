//
//  MaximaCompConexa.h
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//

#ifndef MANCHAS_H_
#define MANCHAS_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

using Mapa = vector<string>; // grafo implícito en el mapa

class Manchas {

	public:

		Manchas(Mapa const& M) : _F(M.size()), _C(M[0].size()), _visitados(_F, vector<bool>(_C, false)), _nManchas(0), _maximo(0) {
			for (int i = 0; i < _F; ++i) {
				for (int j = 0; j < _C; ++j) {
					if (!_visitados[i][j] && M[i][j] == '#') {
						++_nManchas;
						int nuevotam = dfs(M, i, j);
						_maximo = max(_maximo, nuevotam);
					}
				}
			}
		}
			
		int numero() const { 
			return _nManchas; 
		}

		int maximo() const { 
			return _maximo; 
		}

	private:

		int _F, _C; // 
		vector<vector<bool>> _visitados;
		int _nManchas; 
		int _maximo;

		const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} };

		bool correcta(int i, int j) const {
			return 0 <= i && i < _F && 0 <= j && j < _C;
		}

			

		int dfs(Mapa const& M, int i, int j) {
			_visitados[i][j] = true;
			int tam = 1;
			for (auto d : dirs) {
				int ni = i + d.first, nj = j + d.second;
				if (correcta(ni, nj) && M[ni][nj] == '#' && !_visitados[ni][nj]) {
					tam += dfs(M, ni, nj);
				}
			}
			return tam;
		}
};

#endif /* MANCHAS_H_ */
