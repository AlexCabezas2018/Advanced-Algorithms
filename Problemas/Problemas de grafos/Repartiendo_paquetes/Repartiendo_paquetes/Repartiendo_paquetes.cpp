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
	int N, C;
	std::cin >> N >> C;
    
    if (! std::cin)
        return false;
	GrafoDirigidoValorado<int>graph(N);

	for (int i = 0; i < C; i++) {
		int from, to, effort;
		std::cin >> from >> to >> effort;
		graph.ponArista({ from - 1, to - 1, effort });
	}

	std::vector<int> destinatarios;
	int origen, numeroPaquetes;
	std::cin >> origen >> numeroPaquetes;
	for (int i = 0; i < numeroPaquetes; i++) {
		int dests;
		std::cin >> dests;
		destinatarios.push_back(dests - 1);
	}

	Solution sol(graph, origen - 1, destinatarios);
	if (!sol.isPossible()) std::cout << "Imposible\n";
	else std::cout << sol.getSolution() << "\n";
    
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