#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <vector>
#include <climits>

/*
	El problema en cuestión consiste en averiguar el esfuerzo optimo (minimo) que debe realizar un repartidor para llevar los paquetes de la oficina a un punto, teniendo
	que volver de dicho punto a la oficina, pudiendo ser este un camino distinto. Además, el problema expone otras restricciones, como la que dice que solo puede repartir a
	un paquete en cada reparto.
	El problema en esencia se puede resolver aplicando la idea de grafo dirigido valorado. Es dirigido porque las carreteras van de un lado a otro (son solo de un sentido) y es 
	valorado porque los caminos conllevan un esfuerzo. Podemos llamar a los vertices las casas a repartir los paquetes y dos vertices se conectan mediante una arista si existe 
	un camino que los conecte. Una vez dicho esto, proponemos la solucion.

	-Como pide el camino de menor coste, necesitamos un algoritmo que realice dicha labor. Dijkstra nos averigua la distancia que hay desde un origen hacia los demas, es por ello
	que lo utilizamos. Aplicando el algoritmo de forma normal, obtenemos las distancias de la ida, es decir, lo que le cuesta al repartidor llegar a las casas, pero no tenemos en
	cuenta los viajes de vuelta. Para ello, recurrimos al albol inverso. Si nos fijamos, calcular los caminos minimos con el arbol inverso pero desde el mismo punto nos daria
	la distancia desde el origen hacia los demas. Pero las aristas (por estar el grafo invertido) están dadas las vuelta, es decir que si hay una arista tal que A -> B, el arbol
	invertido expresaria esa union como A <- B. Por tanto, lo que en realidad hemos descubierto es la distancia minima que hay desde cada uno de los puntos hasta el origen (porque
	en el arbol original, las aristas que en el arbol invertido llevan a una casa, en realidad llevan desde la casa al origen). Una vez descubiertla distancia minima de la ida
	y la distancia minima de la vuelta, lo unico que tenemos que hacer es sumarlas para las casas solicitadas, a excepcion de que no exista camino de ida, de vuelta, o ninguno de los dos,
	en ese caso, no se puede repartir el paquete a ese destinatario.

	-El coste total es el siguiente:
		- primero se realiza una llamada al algoritmo, del cual sabemos que realiza operaciones en una cola de prioridad (del orden de  O(log V) donde V es el numero de vertices/casas) E veces,
		por lo que el coste es O(E * log(V)) donde E es el numero de aristas / caminos.
		- pasamos los datos obtenidos a un vector auxiliar, con coste O(V) donde V descrito anteriormente.
		- Realizamos una segunda llamada al mismo algoritmo, coste O(E * log(V)) con E y V descritas anteriormente.
		- Finalmente realizamos un bucle que suma, el bucle da N2 vueltas (donde N2 es el numero de destinatarios). Las operaciones de su interior son O(1). En conclusion ese bucle es del
		orden de O(N2)

		-Por tanto nuestro coste total es O(V + 2*E*log(V) + N2) como N2 siempre es < V deducimos que el coste final es O(V + 2 * E * log(V)) = O(V + E * log(V)) con E y 
		V descritos anteriormente.

		
	*/


class Solution {
public:
	Solution(const GrafoDirigidoValorado<int> &g, int origen, const std::vector<int> &dests): minEffort(0), isSolution(true), distTo(g.V(), 0), pq(g.V()){

		DijkstraSP(g.inverso(), origen); //Sacamos los caminos de vuelta desde "origen" a los demas.

		std::vector<int> caminoVuelta;
		for (int i = 0; i < distTo.size(); i++) {
			caminoVuelta.push_back(distTo[i]);
		}

		DijkstraSP(g, origen); //Sacamos los caminos de ida desde "origen" a los demas.

		for (int i = 0; i < dests.size(); i++) {
			if(distTo[dests[i]] != INT_MAX && caminoVuelta[dests[i]] != INT_MAX) //Si no hay camino de ida o de vuelta o, directamente, no hay camino...
				minEffort += distTo[dests[i]] + caminoVuelta[dests[i]]; //El minimo esfuerzo para entregar el paquete i es el camino de ida desde origen a i + 
																		//camino de vuelta desde i hasta origen.
			else {
				isSolution = false;
				return;
			}
		}
	}

	int getSolution() {
		return minEffort;
	}

	bool isPossible() {
		return isSolution;
	}


private:
	int minEffort;
	bool isSolution;
	std::vector<int> distTo;
	IndexPQ<int> pq;

	void DijkstraSP(const GrafoDirigidoValorado<int> &G, int s) {
		for (int v = 0; v < G.V(); v++)
			distTo[v] = INT_MAX;

		distTo[s] = 0;
		pq.push(s, 0);
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto e : G.ady(v))
				relax(e);
		}
	}

	void relax(const AristaDirigida<int> &e) {
		int v = e.from(), w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			pq.update(w, distTo[w]);
		}
	}

};