#include "GrafoValorado.h"
#include <vector>
#include <string>

/*
El problema consiste en averiguar si existe un camino entre el origen y el destino por el que el camion pueda pasar.
Por tanto, este problema se puede resolver aplicando grafos valorados. Como no necesitamos saber el camino, si no mas bien saber
si existe, no necesitamos una busqueda en anchura, basta con un recorrido en profundidad, avanzar en cada cruce y comprobar si dicho
cruce es el destino.

No comprobamos si existen cruces sin calles porque podria dar la casualidad de que el cruce destino no tenga calles (entonces el algoritmo
deberia devolver "NO") y, al hacer la llamada y comprobar que el origen de donde partimos es el destino, el algoritmo daria de forma equivocada
"SI".

Respecto al coste, podemos afirmar que realizamos una llamada a la busqueda, la cual va por cada una de las calles de la primera componente conexa
que se encuentra. Como en el peor de los casos el grafo es conexo y solo existe una componente conexa (todos los cruces estan conectados con los otros)
concluimos con que el algoritmo realiza la comprobacion con un coste O(V + 2E) = O(V + E) donde V(vertices) son los cruces y E(aristas) las calles.
*/

class Solution{
public:
	Solution(const GrafoValorado<int> &g, int orig, int dest, int weight) :_marked(g.V(), false), 
		_sol(false), _dest(dest), _weight(weight) {

		dfs(g, orig);
	}

	std::string getSolution(){ return _sol ? "SI\n": "NO\n"; }


private:
	std::vector<bool> _marked;
	bool _sol;
	int _dest, _weight;

	void dfs(const GrafoValorado<int> &g, int &v){
		_marked[v] = true;
		for (auto w : g.ady(v)){
			int other = w.otro(v);
			if (!_marked[other] && w.valor() >= _weight){
				if (other == _dest) _sol = true;
				else{
					dfs(g, other);
				}
			}
		}
	}
};