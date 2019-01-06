// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Solution.h"
#include <string>

struct Sensor {
	int i, j, value;
	Sensor(int fila, int columna, int valor) : i(fila), j(columna), value(valor) {};
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	std::vector<Sensor> sensores;
	int F, C;
	std::cin >> C >> F;
	std::vector<std::vector<char>> mapa(F, std::vector<char>(C, ' '));
	const std::vector<std::pair<int, int>> direcciones = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	std::pair<int, int> inicio, fin;
    
	// escribir sol
	char x;
	for (int i = 0; i < F; i++){
		for (int j = 0; j < C; j++){
			std::cin >> x;
			if (x == 'E') inicio = { i, j };
			if (x == 'P') fin = { i, j };

			int value = x - '0'; //Transforma un char en entero. El valor será correcto si el char contiene un numero (es decir, el char '9' lo pasa al entero 9 pero el char '%' lo pasa a otro numero).
			if (value >= 0 && value <= 9) {
				sensores.push_back({ i, j, value });
				mapa[i][j] = 'S';
			}
			else mapa[i][j] = x;

		}
	}

	//Ahora delimitamos el rango de los sensores
	for (Sensor x : sensores){
		for (auto dir: direcciones){
			bool correcto = true;
			for (int k = 1; k <= x.value && correcto; k++){
				int ni = x.i + k * dir.first;
				int nj = x.j + k * dir.second;
				bool ok = ni >= 0 && ni < F && nj >= 0 && nj < C;

				if (ok && mapa[ni][nj] == '#'){
					correcto = false;
				}

				if (ok && correcto){
					mapa[ni][nj] = 'S';
				}
			}
		}
	}

	Solution sol(mapa, inicio, fin);
	int solV = sol.getSolution();
	if (solV) std::cout << solV << "\n";
	else std::cout << "NO\n";

	    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}