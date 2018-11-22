// Alejandro Cabezas Garriguez
// TAIS26
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Solution.h";

/*
Es un problema en el que debemos aplicar la idea de conjunto disjuntos, puesto que
necesitamos agrupar los pixeles negros en conjuntos independientes.
Cada vez que introducimos una mancha nueva, debemos comprobar si esta esta al lado de
alguno de los grupos analizados previamente. Para ello, comprobamos todos los vecinos, y si
este conecta con alguno, unimos ambos conjuntos. Despues, el tamaño maximo puede haber variado,
por lo que debemos recalcularlo.

Por tanto tenemos que el analisis inicial es una busqueda en profundidad del coste de O(F * C)
debido a que, el coste incial es O(V + E) pero V = F * C y E < V = F *C. 
Despues, cada llamada a actualizar es constante respecto al numero de vecinos. Pero si estamos frente a un
vecino entonces debemos unir, operacion cuyo coste es O(log(*)(tamaño del conjunto), lo cual es practicamente
constante. Por tanto, concluyo con que este algoritmo es, como maximo O(F*C + log*TAM_MANCHA) y como minimo
O(F * C)
*/



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int F, C;
	std::cin >> F >> C;

    if (! std::cin)
        return false;
		
	std::vector<std::string> map;

	std::cin.get();
	std::string x;

	for (int i = 0; i < F; i++){
		std::getline(std::cin, x);
		map.push_back(x);
	}

	Solution sol(map, F, C);
	std::cout << sol.getSolution() << " ";

	int casosNuevos;
	std::cin >> casosNuevos;
	for (int i = 0; i < casosNuevos; i++){
		int v, w;
		std::cin >> v >> w;
		sol.actualiza(v - 1, w - 1);
		std::cout << sol.getSolution() << " ";
	}
	std::cout << "\n";


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