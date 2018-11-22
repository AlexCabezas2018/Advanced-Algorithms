/*
	Problema del Arbol ALV
	La entrada consta de un arbol. Se trata de averiguar si este arbol es del tipo ALV o no.
	Se dice que un Arbol es ALV si es un arbol binario de busqueda y, ademas, es equlibrado (Mirar problema del Arbol Equilibrado)
	Se dice que un arbol binario es de busqueda si se cumple que la raiz es estrictamente mayor que los nodos del hijo izquierdo y menor que los del hijo derecho
	y ademas es un arbol binario de busqueda para cada subarbol.

	Autor: Alejandro Cabezas Garriguez
	TAIS26
*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"

struct tSol {
	bool esEquilibrado = false;
	bool esDeBusqueda = false;
	bool esSol = false;
	int altura = 0;
	int minimo = -1;
	int maximo = -1;
};

bintree<int> leerArbol(std::istream &flujoEntrada);


// función que resuelve el problema
// Es posible que el codigo pueda ser mas corto, pero esta solucion es correcta.


tSol resolver(const bintree<int> &datos) {
	tSol sol;
	if (datos.empty()) { //El arbol vacio es ALV por definicion.
		sol.esEquilibrado = true;
		sol.esDeBusqueda = true;
		sol.esSol = true;

		return sol;
	}
	else if (datos.left().empty() && datos.right().empty()) { //Si es una hoja
		sol.esDeBusqueda = true;
		sol.esEquilibrado = true;
		sol.esSol = true;

		sol.minimo = datos.root();
		sol.maximo = datos.root();

		sol.altura = 1;

		return sol;

	}
	else if (datos.left().empty()) { //No es una hoja pero no tiene hijo izquierdo
		tSol solI = resolver(datos.left());
		tSol solD = resolver(datos.right());

		sol.altura = solD.altura + 1;

		sol.minimo = std::min(solD.minimo, datos.root());
		sol.maximo = std::max(solD.maximo, datos.root());

		sol.esDeBusqueda = solD.minimo > datos.root() && solI.esDeBusqueda && solD.esDeBusqueda;
		sol.esEquilibrado = solD.esEquilibrado && solI.esEquilibrado && abs(solD.altura - solI.altura) <= 1;
		sol.esSol = solI.esSol && solD.esSol && sol.esDeBusqueda && sol.esEquilibrado;

		return sol;
	}
	else if (datos.right().empty()) { //No es una hoja pero no tiene hijo derecho
		tSol solI = resolver(datos.left());
		tSol solD = resolver(datos.right());

		sol.altura = solI.altura + 1;

		sol.minimo = std::min(solI.minimo, datos.root());
		sol.maximo = std::max(solI.maximo, datos.root());

		sol.esDeBusqueda = solI.maximo < datos.root() && solI.esDeBusqueda && solD.esDeBusqueda;
		sol.esEquilibrado = solI.esEquilibrado && solD.esEquilibrado && abs(solI.altura - solD.altura) <= 1;
		sol.esSol = solI.esSol && solD.esSol && sol.esDeBusqueda && sol.esEquilibrado;
		
		return sol;

	}
	else {
		tSol solI = resolver(datos.left());
		tSol solD = resolver(datos.right());

		sol.altura = std::max(solI.altura, solD.altura) + 1;

		int minimoTotal = std::min(solI.minimo, solD.minimo);
		int maximoTotal = std::max(solI.maximo, solD.maximo);

		sol.minimo = std::min(minimoTotal, datos.root());
		sol.maximo = std::max(maximoTotal, datos.root());

		sol.esDeBusqueda = solI.maximo < datos.root() && solD.minimo > datos.root() && solI.esDeBusqueda && solD.esDeBusqueda;
		sol.esEquilibrado = solI.esEquilibrado && solD.esEquilibrado && abs(solI.altura - solD.altura) <= 1;
		sol.esSol = solI.esSol && solD.esSol && sol.esDeBusqueda && sol.esEquilibrado;
		

		return sol;
	}

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> datos = leerArbol(std::cin);

	tSol sol = resolver(datos);
	if (sol.esSol) std::cout << "SI\n";
	else std::cout << "NO\n";

}

bintree<int> leerArbol(std::istream &flujoEntrada) {
	int aux;
	flujoEntrada >> aux;
	if (aux == -1) {
		return bintree<int>();
	}
	else {
		bintree<int> izquierdo = leerArbol(flujoEntrada);
		bintree<int> derecho = leerArbol(flujoEntrada);

		return bintree<int>(izquierdo, aux, derecho);
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

	system("PAUSE");


	// Para restablecer entrada. Comentar para acepta el reto
/*#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif*/

	return 0;
}