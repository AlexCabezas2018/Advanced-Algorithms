// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

/*
	El problema consiste en encontrar la suma minima de diferencias entre las longitudes de los skies y la altura de los
	participantes. Para obtener la suma minima, lo unico que tenemos que hacer es asignar el ski de minima longitud
	con la persona más baja, despues el siguiente mas corto con el siguiente mas bajo... asi sucesivamente.
	Por tanto, una idea son las colas de prioridad, que siempre tienen a tu disposicion el datos mínimo (en este caso es asi debido a que
	la cola de prioridad es de minimos). Dicho esto, almacenamos en una las alturas y en otra las longitudes, y lo unico que tenemos que 
	hacer (y es en lo que consiste el algoritmo) es iterar en las dos colas, sacando los minimos de ambas, obteniendo la diferencia en
	valor absoluto y añadir dicha cantidad a una variable total. 
	El coste de las operaciones es O(log N) en ambas colas, siendo N el numero de participantes y de skis (puesto que se le asigna uno a cada
	participante) luego, como se hacen N iteraciones, el coste total del algoritmo que resuelve el problema (descartamos el proceso de obtencion de
	datos) es O(N log (N)) donde N es lo comentado anteriormente.
*/


// función que resuelve el problema
int resolver(PriorityQueue<int> &heigths, PriorityQueue<int> &lengths) {
	int ret = 0;
	while (!heigths.empty() || !lengths.empty()) {
		ret += std::abs(heigths.top() - lengths.top());
		heigths.pop(); lengths.pop();
	}
	return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	std::cin >> N;
    
    if (!N)
        return false;

	PriorityQueue<int> heigths;
	PriorityQueue<int> lengths;
    
	for (int i = 0; i < N; i++) {
		int value;
		std::cin >> value;
		heigths.push(value);
	}
	for (int i = 0; i < N; i++) {
		int value;
		std::cin >> value;
		lengths.push(value);
	}


	std::cout << resolver(heigths, lengths) << "\n";
    
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