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
    
	int V, E;
	std::cin >> V >> E;

    if (! std::cin)
        return false;

	GrafoValorado<int>g(V);
	for (int i = 0; i < E; i++){
		int v, w, value;
		std::cin >> v >> w >> value;
		g.ponArista(Arista<int>(v - 1, w - 1, value));
	}

	int K;
	std::cin >> K;

	for (int i = 0; i < K; i++){
		int orig, dest, weigth;
		std::cin >> orig >> dest >> weigth;
		Solution sol(g, orig - 1, dest - 1, weigth);
		std::cout << sol.getSolution();
	}
     
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