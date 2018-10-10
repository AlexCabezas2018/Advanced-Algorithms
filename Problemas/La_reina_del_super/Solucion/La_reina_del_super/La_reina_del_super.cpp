// Alejandro Cabezas Garriguez
// TAIS26

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include <algorithm>

using namespace std;

struct _Client {
	int _time = 0;
	int _CashReg = -1;
};


// --- Coste de la operacion --- //
// --- O(C * log(_CashRegs.size())) --- //

int resolve(PriorityQueue<_Client> &_CashRegs, std::istream &_Input, int N, int C) {

	while (C--) {
		int _Nextime;
		_Client _aux = _CashRegs.top();
		_CashRegs.pop();
		_Input >> _Nextime;
		_aux._time += _Nextime;
		_CashRegs.push(_aux);
	}

	return _CashRegs.top()._CashReg;
}

bool operator<(const _Client &t1, const _Client &t2) {
	if (t1._time < t2._time) return true;
	else if (t1._time > t2._time) return false;
	else return t1._CashReg < t2._CashReg;
}


bool resuelveCaso() {
   int N, C;

   cin >> N;
   
   if (!cin || N == 0)
      return false;

   cin >> C;
   
   PriorityQueue<_Client> _CashRegs;
   int _Place = 1;
   
	for (int i = 0; i < N; i++) {
		_Client _aux;
		_aux._CashReg = _Place++;
		_CashRegs.push(_aux);
	}
	cout << resolve(_CashRegs, std::cin, N, C) << "\n";

	   
   // completa para terminar de leer y resolver un caso
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
