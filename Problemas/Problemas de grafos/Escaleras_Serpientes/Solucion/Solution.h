#include "GrafoDirigido.h"
#include <vector>
#include <queue>

class Solution{
public:
	// --- Coste de la operacion --- //
	// O(V + E) donde V es el numero de vertices y E el numero de aristas.

	Solution(GrafoDirigido &G) : _marked(G.V(), false), _distTo(G.V()) {
		bfs(G, 0);
	}

	int getSolution(){ return _distTo[_distTo.size() - 1]; }

private:

	std::vector<bool> _marked;
	std::vector<int> _distTo;

	void bfs(const GrafoDirigido &G, int s){
		std::queue<int> q;
		_distTo[s] = 0;
		_marked[s] = true;
		q.push(s);
		while (!q.empty()){
			int v = q.front(); q.pop();
			for (int w : G.ady(v)){
				if (!_marked[w]){
					_distTo[w] = _distTo[v] + 1;
					_marked[w] = true;
					q.push(w);
				}
			}
		}
	}


};