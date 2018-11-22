#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include <vector>
#include <string>
#include <queue>

/*
	El problema consiste en encontrar la construccion mas barata de puentes para poder conectar
	todos las islas.
	Si llamamos a las islas vertices y a los puentes posibles aristas, basicamente lo que tenemos es un
	grafo valorado en el que dor vertices estan conectados por una arista si es posible construir un puente
	entre ellos.
	El objetivo del problema es, en esencia, encontrar una arbol de recubrimiento minimo. Pero tambien hay que tener
	en cuenta que el grafoo inicial sea conexo, es decir, que existan puentes suficientes para poder ir de una isla a otra
	(que no hayan islas aisladas), por tanto, debemos de tener en cuenta el numero de componentes conexas y asegurarnos que este
	numero no supere 1. 
	Usaremos el algoritmo de Prim, aunque en este caso cualquier otro serviria. El coste de este algoritmo es O(E log E)
	donde E es el numero de aristas, es decir, el numero de puentes.

*/


class Solution {
public:
	Solution(const GrafoValorado<int> &g) : marked(g.V(), false), money(0), isConnected(true) {
		int connectedComponents = 0;
		for (int i = 0; i < g.V(); i++){
			if (!marked[i]){
				connectedComponents++;
				if (connectedComponents > 1){ //No es conexo.
					isConnected = false;
					return;
				}
				lazyPrimMST(g);
			}
		}
	
	}

	bool getConnected(){
		return isConnected;
	}
	
	int getSolution(){
		return money;
	}


private:
	std::vector<bool> marked;
	std::queue<Arista<int>> mst;
	PriorityQueue<Arista<int>> pq;
	int money;
	bool isConnected;

	void lazyPrimMST(const GrafoValorado<int> &g){
		visit(g, 0);
		while (!pq.empty() && mst.size() < g.V() - 1){
			Arista<int> e = pq.top(); pq.pop();
			int v = e.uno(), w = e.otro(v);
			if (marked[v] && marked[w]) continue;
			mst.push(e);
			money += e.valor();
			if (!marked[v]) visit(g, v);
			if (!marked[w]) visit(g, w);
		}
	}

	void visit(const GrafoValorado<int> &G, int v){
		marked[v] = true;
		for (auto e : G.ady(v)){
			if (!marked[e.otro(v)]) pq.push(e);
		}

	}
};