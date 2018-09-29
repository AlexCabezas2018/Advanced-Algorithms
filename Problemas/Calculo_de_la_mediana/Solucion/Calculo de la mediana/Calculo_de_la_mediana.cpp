// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"



// --- Coste de la operacion --- //
// O(max(_numberOfDigits*log(_NQueue.size()), _numberOfDigits*log(_N1Queue.size()))

void resolver(std::istream &flujoEntrada, int _numberOfDigits) {
	PriorityQueue<long int, std::greater<long int>>_NQueue;
	PriorityQueue<long int>_N1Queue;
	long int _numberToInsert;
	long int _currentNumbers = 0;
	flujoEntrada >> _numberToInsert;
	_NQueue.push(_numberToInsert);
	_currentNumbers++;
	std::cout << 2 * _NQueue.top() << "\n";

	while (_currentNumbers < _numberOfDigits) {
		flujoEntrada >> _numberToInsert;
		if (_numberToInsert > _NQueue.top()) {
			_N1Queue.push(_numberToInsert);
			if (_N1Queue.size() - _NQueue.size() > 1) {
				long int aux = _N1Queue.top();
				_N1Queue.pop();
				_NQueue.push(aux);
			}
		}
		else {
			_NQueue.push(_numberToInsert);
			if (_NQueue.size() > _N1Queue.size()) {
				long int aux = _NQueue.top();
				_NQueue.pop();
				_N1Queue.push(aux);
			}
		}

		long int _m;
		_currentNumbers++;
		if (_currentNumbers % 2 != 0) {
			_m =  2 *_N1Queue.top();
		}
		else {
			_m = _N1Queue.top() + _NQueue.top();
		}
		std::cout << _m << "\n";
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int numeroDatos;
	std::cin >> numeroDatos;

    if (!numeroDatos)
        return false;
    
    resolver(std::cin, numeroDatos);
    
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

    
   /* // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}