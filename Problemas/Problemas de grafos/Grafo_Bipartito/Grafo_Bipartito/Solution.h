//Alejandro Cabezas Garriguez
//TAIS26

#include "Grafo.h"
#include <vector>

struct _Node {
	bool _color = true; //There are only 2 colors.
};

// --- Coste de la solucion --- //
// --- O(V + E) donde V es el numero de vertices y E el numero de aristas. --- //

class Solution {
public:
	Solution(const Grafo &_G) : _marked(_G.V(), false), _bipartite(true), _nodes(_G.V()) {
		_Node _initial;
		_initial._color = false;
		for (int i = 0; i < _G.V(); i++){
			if (!_marked[i]){
				dfs(_G, i, _initial);
			}
		}
	}

	bool getSolution() const { return _bipartite; }

private:
	std::vector<bool> _marked;
	std::vector<_Node> _nodes;
	bool _bipartite;

	void dfs(const Grafo &G, int &v, _Node &_parent){
		_marked[v] = true;
		_nodes[v]._color = !_parent._color;

		for (int i: G.ady(v)) {
			if (_marked[i] && _nodes[i]._color == _nodes[v]._color) {
				_bipartite = false;
			}
			else if(!_marked[i]) {
				dfs(G, i, _nodes[v]);
			}
		}
	}
};