// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <queue>

/*
	Coste del problema:
		El coste del algoritmo que resuelve el problema es:
			- Se realizan N iteraciones sobre la cola, donde N es el numero de libros
			- Por cada vueltan se realizan operaciones sobre la cola, las cuales tiene coste O(log N)
			- Por tanto el coste total es O(N * log N) donde N es lo anteriormente contado.
*/

int descuento_maximo(std::priority_queue<int> &libros) {
	int max_descuento = 0;
	
	int i = 1;
	while (!libros.empty()) {
		int precio = libros.top();
		if (i == 3) {
			max_descuento += precio;
			i = 1;
		}
		else {
			i++;
		}
		libros.pop();
	}

	return max_descuento;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	std::cin >> N;
    
    if (! std::cin)
        return false;
    
	std::priority_queue<int> libros;
	int value;
	for (int i = 0; i < N; i++) {
		std::cin >> value;
		libros.push(value);
	}

	std::cout << descuento_maximo(libros) << "\n";
    
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