// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

struct _Instrument {
	int _Initial = 0;
	int _Partitures = 1;

	_Instrument() : _Initial(0), _Partitures(0) {};
	_Instrument(int _I, int _P) : _Initial(_I), _Partitures(_P) {};
};

bool operator >(const _Instrument &t1, const _Instrument &t2) {
	int _a = t1._Initial / t1._Partitures;
	int _b = t2._Initial / t2._Partitures;

	if (t1._Initial % t1._Partitures != 0) _a++;
	if (t2._Initial % t2._Partitures != 0) _b++;

	return _a > _b;
}

//--- Orden de complejidad --- //
//--- O(_rest * log(_Instruments.size())) --- //

int resolver(PriorityQueue<_Instrument, std::greater<_Instrument>> &_Instruments, int _Partitures, int _NInstruments) {
	int _rest = _Partitures - _NInstruments;

	while (_rest--) {
		_Instrument _aux = _Instruments.top();
		_Instruments.pop();
		_aux._Partitures++;
		_Instruments.push({ _aux._Initial, _aux._Partitures });
	}
	_Instrument _max = _Instruments.top();
	int _sol = _max._Initial / _max._Partitures;
	if (_max._Initial % _max._Partitures != 0) _sol++;

	return _sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int _Partitures, _Ninstruments;
	PriorityQueue<_Instrument, std::greater<_Instrument>> _Instruments;

	std::cin >> _Partitures;
	std::cin >> _Ninstruments;

    if (! std::cin)
        return false;
    
	for (int i = 0; i < _Ninstruments; i++) {
		int _aux;
		std::cin >> _aux;
		_Instruments.push({_aux, 1});
	}

	std::cout << resolver(_Instruments, _Partitures, _Ninstruments) << "\n";
    
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