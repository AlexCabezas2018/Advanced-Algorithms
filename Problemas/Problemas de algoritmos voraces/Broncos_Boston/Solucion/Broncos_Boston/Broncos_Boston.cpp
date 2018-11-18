// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

/*
	El problema consiste en averiguar el maximo de puntos que obtendran nuestro equipo, definido como "puntos" a la diferencia entre
	los puntos entre nuestro equipo y el rival. Para ello tenemos una serie de N partidos a los que asociamos dos resultados, los puntos del rival
	y los puntos de nuestro equipo. En teoria, estos partidos aun no se han disputado, por lo que no sabemos en que orden van los puntos (es decir,
	que sabemos que se han dado los resultados de N partidos, pero no sabemos exactamente la puntuacion de cada equipo en cada partido). 
	Los puntos maximos se basan en la ideade que, primero, debemos ganar (es decir, la puntuacion de nuestro equipo debe ser > que la del rival).
	Tambien nos basaremos en que la diferencia maxima (lo que nos pide el problema) es la resta entre la maxima puntuacion de nuestro equipo
	menos la minima del rival. Sabien esto, lo que haremos será guardar las puntuaciones de nuestro equipo en una cola de prioridad de maximos (que facilita
	el acceso al maximo) y las puntuaciones del rival en una de minimos. Iteramos sobre las dos, sacamos el valor en la cima (el maximo de la cola de nuestro equi
	po y el minimo de la cola del equipo riva). Restamos ambas puntuaciones y comprobamos que esta diferencia es positiva. Si es asi, sumamos.
	Por lo tanto, como iteramos sobre dos colas del mismo tamaño (N, que es el numero de partidos predecidos) y eliminamos elementos simultaneamente en ambas, deducimos:
	- Las operaciones como top() y pop() son del coste de O(log N) con N descrito anteriormente.
	- Realizamos N iteraciones (puesto que ambas colas tienen la misma cantidad de elementos en cada iteracion)
	- El coste final del algoritmoa que resuelve el problema (descartamos la fase de obtencion de datos) es O(N log(N)) con N descrito anteriormente.
*/


// función que resuelve el problema
int resolver(PriorityQueue<int> &rivalTeam, PriorityQueue<int, std::greater<int>> &ourTeam) {
	int ret = 0; //puntos maximos
	while (!rivalTeam.empty() || !ourTeam.empty()) {
		int diff = ourTeam.top() - rivalTeam.top();
		if (diff > 0) ret += diff;
		rivalTeam.pop(); ourTeam.pop();
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
    
	PriorityQueue<int> rivalTeam;
	PriorityQueue<int, std::greater<int>> ourTeam;

	for (int i = 0; i < N; i++) {
		int points;
		std::cin >> points;
		rivalTeam.push(points);
	}
    
	for (int i = 0; i < N; i++) {
		int points;
		std::cin >> points;
		ourTeam.push(points);
	}
    
	std::cout << resolver(rivalTeam, ourTeam) << "\n";
    
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