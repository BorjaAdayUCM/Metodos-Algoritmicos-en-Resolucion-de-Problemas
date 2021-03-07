#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void resuelve(int numObjetivo, int numSectores, vector<int> sectores, vector<vector<int>>& resultados) {
	auto it = sectores.cbegin();
	int resta;
	for(int i = *it + 1; i <= numObjetivo; i++) {
		while (it != sectores.cend() && i - *it >= 0) {
			resta = i - *it;
			if (resultados[resta].size() != 0) {
				if (resultados[i].size() == 0 || resultados[i].size() >= resultados[i - *it].size() + 1) {
					resultados[i] = resultados[i - *it];
					resultados[i].push_back(*it);
				}
			}
			it++;
		}
		it = sectores.cbegin();
	}
}

int main() {
	int numObjetivo, numSectores, num;
	while (cin >> numObjetivo) {
		cin >> numSectores;
		vector<int> sectores;
		vector<vector<int>> resultados(501);
		for (int i = 0; i < numSectores; i++) {
			cin >> num;
			auto it = find(sectores.begin(), sectores.end(), num);
			if(it == sectores.end()) {
				resultados[num].push_back(num);
				sectores.push_back(num);
			}
		}
		resuelve(numObjetivo, numSectores, sectores, resultados);
		reverse(resultados[numObjetivo].begin(), resultados[numObjetivo].end());
		int resultado = resultados[numObjetivo].size();
		if (resultado == 0) cout << "Imposible\n";
		else {
			cout << resultados[numObjetivo].size() <<  ":";
			for (int i = 0; i < resultados[numObjetivo].size(); i++) cout << " " << resultados[numObjetivo][i];
			cout << '\n';
		}
	}
}