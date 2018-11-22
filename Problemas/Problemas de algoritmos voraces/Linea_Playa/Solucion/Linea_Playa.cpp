// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

/*
	El problema consiste en encontrar el numero minimo de tuneles necesarios para conectar los edificios.
	En esencia, dados unos segmentos (diferenciados por su inicio y su final), la idea es encontrar el menor
	numero de valores tales que se cumplen que dichos valores se encuentran dentro de la mayor cantidad de segmentos.

	Por tanto, debemos usar una cola de prioridad y la estrategia que seguiremos será sencillamente ordenar los edificios
	por su final. De este modo decimos que el menor de los edificios es el aquel edificio (donde a es el incio y b el final)
	que, mirandolo desde el extremo izquierdo (el extremo mas occidente) termina antes.

	Para iterar y obtener una solucion optima, basta con almacenar una variable (a parte de la que cuenta el numero de tuneles)
	que indique la ultima posicion donde fue colocada un tunel. Si el principio de algun edificio es mayor que la posicion donde
	está colocado el tunel, quiere decir que necesitamos construir otro.

	El coste total es iterar N veces sobre una cola de prioridad, realizando las operaciones pop() y top(), cuyo coste es O(N) donde N
	es el numero de edificios. Por tanto el coste final es O(N log N) donde N está explicado anteriormente.


*/



struct Building {
	int begin;
	int end;

	Building(int b, int e) : begin(b), end(e) {};
	Building() : begin(0), end(0) {};
};

// función que resuelve el problema
int resolver(PriorityQueue<Building> &buildings) {
	int ret = 1;
	int tunnel = buildings.top().end; //indica cual es la longitud maxima que esta cubriendo el tunel

	while (buildings.size() >= 1) {
		if (buildings.top().begin >= tunnel) { //Significa que este edificio no esta atravesado por ningun tunel
			ret++;
			tunnel = buildings.top().end;
		}
		buildings.pop();
	}
    
	return ret;
    
}

bool operator<(const Building &b1, const Building &b2) {
	return ((b1.end < b2.end) || (b1.end == b2.end && b1.begin < b2.begin));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	std::cin >> N;

    if (!N)
        return false;
    
	PriorityQueue<Building> buildings;
	for (int i = 0; i < N; i++) {
		int begin, end;
		std::cin >> begin >> end;
		buildings.push({ begin, end });
	}

	std::cout << resolver(buildings) << "\n";
    
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