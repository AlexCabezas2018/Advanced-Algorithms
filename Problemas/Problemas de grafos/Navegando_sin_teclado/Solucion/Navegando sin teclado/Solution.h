#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <climits>
#include <vector>

/*
	El problema consiste en encontrar el camino mas rapido entre enlaces para llegar a una determinada pagina. Los enlaces llevan
	un determinado tiempo en cargarse (debido al tiempo como tal de cargarse y el tiempo empleado en buscar el enlace) y, además,
	las páginas tambien tardan cierto tiempo en cargarse. Si lo vemos desde una perspectiva mas abstracta, tenemos, en esencia, un
	grafo valorado dirigido, en el que los vertices son las paginas y dos vertices comparten una arista si existe un enlace que las une.
	Los enlaces van de una pagina a otra, de ahi que el grafo sea dirigido. También las aristas tienen valores diferentes, de ahí que el grafo
	sea valorado. 
	Dado ese grafo, el problema en esencia consiste en encontrar el camino con menor valor entre el vertice 1 hasta el vertice N (con las aristas y vertices definidos mas arriba).
	Utilizaremos el algoritmo de dijkstra, que realiza concretamente dicha labor. En este caso tenemos que modificar un poco cierta parte del algoritmo porque, como hemos dicho
	anteriormente, hay que tener en cuenta tanto el valor de las aristas como el de los vertices. Una vez realizado el algoritmo nos encontramos con las distancias que existen desde
	el vertice 1 hasta los demas, sin tener en cuenta el valor de los demás vertices (es decir, la distancia entre dos vertices A y B es valor(arista(A, B)) + valor(A))
	por tanto, tenemos que sumar el valor de los demas vertices, pero en este caso no es necesario, debido a que nos preguntan solo por la distancia entre los vertices 1 a N, que llamaremos A y B.
	Dicho esto, la distancia sera: [valor(A) + valor(arista(A, B))] + valor(B). Si el valor [] (que es el que obtenemos por el algoritmo) es justamente el valor incial con el que ha
	sido inicializado, entonces nos encotramos con que no existe camino que lleve desde el vertice 1 hasta el N, por lo tanto no hay solucion. En otro caso devolvemos el dato
	con la formula ya dicha anteriormente.

	Por tanto, el coste del algoritmo que resuelve el problema es el coste del algoritmo de dijkstra, puesto que despues de aplicarlo, no realizamos ninguna operacion de coste mayor que
	O(1).
	El algortimo realiza operaciones sobre una cola de prioridad (de coste O(log V) donde V es el numero de vertices (paginas)) y dichas operaciones las realiza E veces (E = numero de aristas/enlaceSs)
	Por tanto, el coste final es grosso modo O(E * log(V)) donde E y V son datos ya explicados anteriormente.
*/



class Solution {
public:
	Solution(const GrafoDirigidoValorado<int> &g, const std::vector<int> &times) : distTo(g.V(), 0), pq(g.V()), timesPage(times) {
		DijkstraSP(g, 0);

		if (distTo[g.V() - 1] != INT_MAX) { // [valor(A) + valor(arista(A, B))] = distTo[B]
			solution = distTo[g.V() - 1] + timesPage[g.V() - 1]; //[valor(A) + valor(arista(A, B))] + valor(B)
		}
		else solution = 0;

	}

	int getSolution() {
		return solution;
	}


private:
	std::vector<int> distTo;
	std::vector<int> timesPage;
	int solution;
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
		if (distTo[w] > distTo[v] + e.valor() + timesPage[v]) { //Aqui es donde obetenemos que distTo[B] = [valor(A) + valor(arista(A, B))]
			distTo[w] = distTo[v] + e.valor() + timesPage[v];
			pq.update(w, distTo[w]);
		}
	}
};
