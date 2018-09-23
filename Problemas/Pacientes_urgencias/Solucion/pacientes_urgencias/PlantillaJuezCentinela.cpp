// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

struct tPaciente {
	std::string nombre = "";
	int gravedad = -1;
	int tiempoEspera = -1;
};

bool operator<(const tPaciente &t1, const tPaciente &t2) { //
	if (t1.gravedad == t2.gravedad) {
		return t1.tiempoEspera < t2.tiempoEspera;
	}
	return t1.gravedad > t2.gravedad;
}

// --- Coste de la operacion --- //
// --- O(numeroEventos*Log(N)) donde N es el numero de pacientes --- //

void resolver(int numeroEventos) {
	PriorityQueue<tPaciente> paciente;
	int espera = 0;
	while (numeroEventos--) {
		std::string evento;
		std::cin >> evento;
		if (evento == "I") {
			tPaciente pacienteNuevo;
			std::string nombre;
			int gravedad;
			std::cin >> nombre;
			std::cin >> gravedad;
			pacienteNuevo.nombre = nombre;
			pacienteNuevo.gravedad = gravedad;
			pacienteNuevo.tiempoEspera = espera;
			paciente.push(pacienteNuevo);

			espera++;
		}
		else { //Evento tipo A
			tPaciente pacientePop = paciente.top();
			std::cout << pacientePop.nombre << "\n";
			paciente.pop();
		}
	}

	std::cout << "----\n";
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int numeroEventos;
	std::cin >> numeroEventos;

    if (!numeroEventos)
        return false;
	
	resolver(numeroEventos);
   
    
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
    /* #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}