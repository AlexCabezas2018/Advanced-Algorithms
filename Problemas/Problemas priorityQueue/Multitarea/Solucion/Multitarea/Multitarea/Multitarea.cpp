// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"


struct _Assignment {
	int _begin;
	int _end;
	int _period = 0;
};

// --- Coste de la operacion --- //
// --- O(_timeToWatch * log(_assignments.size())) --- //

bool resolver(PriorityQueue<_Assignment> &_assignments, int _timeToWatch) {
	int _timeWithNoOverlapment = 0;
	if (_assignments.size() <= 1 || _timeToWatch == 0) { return false; } //1 or less than 1 assignment will never overlap with others. Without time to watch, there is no overlapment.
	else {
		_Assignment _aux = _assignments.top();
		while (_assignments.size() > 0 && _aux._begin < _timeToWatch) {
			_assignments.pop();
			if (_aux._begin < _timeToWatch) {
				if (_aux._begin < _timeWithNoOverlapment) return true;  //Checks if they overlap
			}
			_timeWithNoOverlapment = _aux._end;

			if (_aux._period > 0) {
				_aux._begin += _aux._period;
				_aux._end += _aux._period;
				_assignments.push(_aux);
			}
			_aux = _assignments.top();
		}
	}

	return false;
}

bool operator<(const _Assignment &a, const _Assignment &b) {
	return a._begin < b._begin || (a._begin == b._begin && a._end < b._end);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int _Nassignment, _NRAssignment, _timeToWatch;

	std::cin >> _Nassignment;
	std::cin >> _NRAssignment;
	std::cin >> _timeToWatch;

    if (! std::cin)
        return false;
	PriorityQueue<_Assignment> _assignments;

	while (_Nassignment--) {
		int _begAux, _endAux;
		std::cin >> _begAux >> _endAux;
		_Assignment _asAux;
		_asAux._begin = _begAux;
		_asAux._end = _endAux;

		_assignments.push(_asAux);
	}

	while (_NRAssignment--) {
		int _begAux, _endAux, _periodAux;
		std::cin >> _begAux >> _endAux >> _periodAux;
		_Assignment _asAux;
		_asAux._begin = _begAux;
		_asAux._end = _endAux;
		_asAux._period = _periodAux;

		_assignments.push(_asAux);
	}

	if (resolver(_assignments, _timeToWatch)) std::cout << "SI\n";
	else std::cout << "NO\n";
   
    
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