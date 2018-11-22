// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

struct registro {
	int momento = -1;
	int id = -1;
	int periodo = -1;
};

bool operator<(const registro &r1, const registro &r2) {
	return r1.momento < r2.momento ||
		(r1.momento == r2.momento && r1.id < r2.id);
}

// --- Coste de la operacion --- //
// --- O(max(numUsers*Log(N), numEnvios*Log(N))) donde N es el numero de usuarios registrados.

void resolver(int numUsers) {
	PriorityQueue<registro> regs;
	int numEnvios, i = 0;
	while (i++ < numUsers) {
		registro toPush;
		int id;
		int periodo;
		std::cin >> id;
		std::cin >> periodo;
		toPush.id = id;
		toPush.periodo = periodo;
		toPush.momento = periodo;

		regs.push(toPush);
	}
	std::cin >> numEnvios;
	while (numEnvios--) {
		registro poped = regs.top();
		regs.pop();
		std::cout << poped.id << "\n";
		poped.momento += poped.periodo;
		regs.push(poped);
	}
	std::cout << "----\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int numeroUsuarios;
	std::cin >> numeroUsuarios;

    if (!numeroUsuarios)
        return false;
    
	resolver(numeroUsuarios);
    
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

    
  /*  // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}