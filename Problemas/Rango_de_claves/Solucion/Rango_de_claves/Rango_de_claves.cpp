// Alejandro Cabezas Garriguez
// TAIS 26


#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "TreeMap_AVL.h"



/*
	Atencion!!
	la solucion no está implementada como funcion externa a la clase, sino como una operación de la misma.
	Esto quiere decir que la solucion se encuentra dentro del archivo TreeMap_AVL.h
	Entra en dicho archivo y busca el metodo "randoClaves()".
*/


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int numElems;
	std::cin >> numElems;
    if (numElems == 0)
        return false;
    
	int k1, k2;
	map<int, int> datos;
	for (int i = 0; i < numElems; i++) {
		int aux;
		std::cin >> aux;
		datos.insert(aux);
	}
	std::cin >> k1;
	std::cin >> k2;
	std::vector<int> sol;

	datos.rangoClaves(sol, k1, k2);
	
	for (int num : sol) {
		std::cout << num << " ";
	}
	std::cout << "\n";
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    /*#ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif*/ 
    
    
    while (resuelveCaso())
        ;

    
   /* // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}