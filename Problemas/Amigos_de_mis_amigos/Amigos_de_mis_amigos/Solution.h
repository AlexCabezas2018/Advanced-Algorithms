//Alejandro Cabezas Garriguez
//TAIS26

#include "Grafo.h"
#include <vector>
#include <algorithm>

class Solution {
public:
	// --- Coste de la operacion --- //
	// --- O( V + E ) donde V es el numero de vertides del grafo y E el numero de aristas --- //

	Solution(Grafo const &G) : _marked(G.V(), false), _max(0) {
		for (int i = 0; i < G.V(); i++){
			if (!_marked[i]){
				int tam = 0;
				dfs(G, i, tam);
				_max = std::max(_max, tam);
			}
		}
	};

	int maxTam() const { return _max; }

private:
	std::vector<bool> _marked;
	int _max;

	void dfs(const Grafo &_G, int &_v, int &_tam){
		_marked[_v] = true;
		++_tam;
		for (int w : _G.ady(_v)){
			if (!_marked[w]){
				dfs(_G, w, _tam);
			}
		}
	}
};
