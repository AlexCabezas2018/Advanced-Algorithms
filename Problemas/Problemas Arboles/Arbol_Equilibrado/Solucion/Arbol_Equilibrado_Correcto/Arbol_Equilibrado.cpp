/*
    Problema del Arbol Equilibrado.
    La entrada consta de un arbol. El problema trata de averiguar si este es equilibrado o no.
    Se dice que un arbol es equilibrado si la diferencia de alturas entre los hijos es <= 1

    Autor: Alejandro Cabezas Garriguez
    TAIS26
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include "Arbin.h"

struct tSolucion {
	int altura = 0;
	bool esSol = false;
};

Arbin<char> leerArbol(std::istream &flujoEntrada);


// función que resuelve el problema
tSolucion resolver(const Arbin<char> &datos) {
	tSolucion sol;
	if (datos.esVacio()) {
		sol.esSol = true;

		return sol;
	}
	else {
		tSolucion solD, solI;

		solI = resolver(datos.hijoIz());
		solD = resolver(datos.hijoDr());

		sol.altura = std::max(solI.altura, solD.altura) + 1;

		if (abs(solD.altura - solI.altura) <= 1
			&& solD.esSol && solI.esSol)
			sol.esSol = true;

		return sol;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	Arbin<char> datos = leerArbol(std::cin);
    
    tSolucion sol = resolver(datos);
    if(sol.esSol) std::cout << "SI\n";
    else std::cout << "NO\n";

}

Arbin<char> leerArbol(std::istream &flujoEntrada) {
	char aux;
	flujoEntrada >> aux;
	if (aux == '.') {
		return Arbin<char>();
	}
	else {
		Arbin<char> izquierdo = leerArbol(flujoEntrada);
		Arbin<char> derecho = leerArbol(flujoEntrada);

		return Arbin<char>(izquierdo, aux, derecho);
	}
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    /*#ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif */
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();
    
    // Para restablecer entrada. Comentar para acepta el reto
     /*#ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}