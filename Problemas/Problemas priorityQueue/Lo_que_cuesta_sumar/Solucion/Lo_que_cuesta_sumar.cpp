//Alejandro Cabezas Garriguez
//TAIS 26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"


// --- Coste de la funcion --- //
// O(NlogN) donde N es el numero de datos de la cola.

long long int resolver(PriorityQueue<long long int> &datos) {
	long long int esfuerzo = 0;
	long long int sumaActual = 0;
	if (datos.size() <= 1) return 0; //El esfuerzo de sumar solo un dato es 0
	//En este punto nos aseguramos que la cantidad de datos en la cola es mayor o igual que 2
	else {
		while (datos.size() > 1) {
			long long int a = datos.top();
			datos.pop();
			long long int b = datos.top();
			datos.pop();

			sumaActual = a + b;
			esfuerzo += sumaActual;

			datos.push(sumaActual);
		}

		return esfuerzo;
	}

    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	long long int tamDatos;
	std::cin >> tamDatos;
    
    if (!tamDatos)
        return false;
	PriorityQueue<long long int> datos;
	long long int sumaObjetivo = 0;

	for (long long int i = 0; i < tamDatos; i++) {
		long long int aux;
		std::cin >> aux;
		datos.push(aux);
		sumaObjetivo += aux;
	}

	std::cout << resolver(datos) << "\n";
    
    // escribir sol
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    /*#ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif */
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     /*#ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}