// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Solution.h"



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K, E, S;

	std::cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && E == 0 && S == 0)
		return false;

	GrafoDirigido g(N * N);
	for (int i = 0; i < S + E; i++){
		int v, w;
		std::cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}
	for (int i = 0; i < g.V(); i++) {
		for (int j = 1; j <= K; j++){
			if (j + i < g.V()){
				if (g.ady(j + i).size() > 0){
					int x = g.ady(j + i).at(0);
					g.ponArista(i, x);
				}
				else g.ponArista(i, j + i);
			}
		}
	}


	Solution sol(g);
	std::cout << sol.getSolution() << "\n";
	// escribir sol


	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}