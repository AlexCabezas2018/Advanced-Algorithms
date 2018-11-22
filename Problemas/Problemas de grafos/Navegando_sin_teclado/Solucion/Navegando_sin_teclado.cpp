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
	int pageNumbers;
	std::cin >> pageNumbers;
    
    if (!pageNumbers)
        return false;

	std::vector<int> times(pageNumbers);
	for (int i = 0; i < times.size(); i++) {
		int value;
		std::cin >> value;
		times[i] = value;
	}

	int links;
	std::cin >> links;

	GrafoDirigidoValorado<int> pages(pageNumbers);
	for (int i = 0; i < links; i++) {
		int from, to, value;
		std::cin >> from >> to >> value;
		pages.ponArista(AristaDirigida<int>(from - 1, to - 1, value));
	}

	Solution sol(pages, times);

	int solNumber = sol.getSolution();
	if (solNumber == 0) {
		std::cout << "IMPOSIBLE\n";
	}
	else std::cout << solNumber << "\n";

    
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