// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

/*
	El problema consiste en encontrar la estrategia que mayor puntuacion genere. Como no encontramos una estrategia
	voraz que resuelva el problema, probaremos a aplicar programación dinamica.
	El problema nos indica que se elige una casilla de la ultima fila y explica que un movimiento consiste en
	elegir una de las tres casillas que hay encima de la que hemos elegido: la diagonal izquierda, la vertica y la diagonal derecha.
	El objetivo es llegar hasta una casilla de la primera fila realizando movimientos desde la casilla de abajo del todo.

	Consideraremos como casos base las casillas adyacentes que se encuentren fuera del tablero, cuya puntuacion será -1 debido a que el problema
	nos indica que el tablero esta compuesto por numero naturales. Esto quiere decir que "rodeamos" el tablero de -1

	La recursion de este problema esta definida de la siguiente manera:
		puntuacion(x, y) = valor(x, y) si x - 1 == 0 Si la fila de encima esta fuera del tablero
		puntuacion(x, y) = max(puntuacion(x - 1, y - 1), puntuacion(x - 1, y), puntuacion(x - 1, y + 1)) + valor(x, y) si x - 1 > 0 en otro caso

	El coste en tiempo del algoritmo que resuelve el problema es del orden de O(N * N) donde N es el numero de filas y columnas del tablero
	El coste en espacio es O(N * N) tambien, donde N está explicado más arriba.
*/


struct tSol {
	int value;
	int indiceParaEmpezar;
};


tSol puntuacion(const std::vector<std::vector<int>> &tablero, const int N) {
	tSol ret;
	std::vector<std::vector<int>> puntuaciones(N + 1, std::vector<int>(N + 2, -1));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (puntuaciones[i - 1][j] == -1) puntuaciones[i][j] = tablero[i][j];
			else {
				int maxDiagonales = std::max(puntuaciones[i - 1][j - 1], puntuaciones[i - 1][j + 1]);
				int maxTotal = std::max(maxDiagonales, puntuaciones[i - 1][j]);
				puntuaciones[i][j] = maxTotal + tablero[i][j];
			}
		}
	}

	ret.indiceParaEmpezar = 1;
	
	//Buscamos el indice por donde empezar
	for (int j = 1; j <= N; j++) {
		if (puntuaciones[N][j] > puntuaciones[N][ret.indiceParaEmpezar])
			ret.indiceParaEmpezar = j;
	}

	ret.value = puntuaciones[N][ret.indiceParaEmpezar];
	
	return ret;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	std::cin >> N;

    if (! std::cin)
        return false;

	std::vector<std::vector<int>> tablero(N + 1, std::vector<int>(N + 2, -1));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int value;
			std::cin >> value;
			tablero[i][j] = value;
		}
	}

	tSol sol = puntuacion(tablero, N);
	std::cout << sol.value << " " << sol.indiceParaEmpezar << "\n";


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