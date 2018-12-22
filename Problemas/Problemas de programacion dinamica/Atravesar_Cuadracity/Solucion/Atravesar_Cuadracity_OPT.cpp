// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

/*
	El problema consiste en encontrar el numero de caminos que logran llevar desde el punto de inicio
	que se encuentra en la esquina superior izquierda, al final que se encuentra en el otro extremo.
	Como no encontramos una estrategia voraz, optaremos por explorar todo el arbol de opciones.
	Para optimizar costes en espacio adicional, hemos decidido usar programacion dinamica.

	Llamaremos camino(i, j) al numero de caminos que hay desde el inicio hasta la posicion i y j del 
	mapa. En cada paso, decidimos qué camino escoger dependiendo de la casilla en la que nos encontremos 
	en cada situacion.

	Diferenciaremos dos situaciones: si encontramos un pasadizo o no. Por tanto, tenemos que:
		camino(i, j) = 0 si mapa[i][j] = "PASADIZO"
	Si por el contrario, no nos encontramos sobre un pasadizo, entonces el numero de caminos que hay
	en dicha posicion son, tanto los que vienen de encima suya como los que viene de su izquierda. Por tanto:
		camino(i, j) = camino(i, j - 1) + camino(i - 1, j) si mapa[i][j] != "PASADIZO"

	El unico caso base que necesitamos es que el numero de caminos que hay es 1, por tanto camino(0, 1) = 1.

	---VERSION SIN OPTIMIZAR---
	Para este caso, optaremos por una matriz de tamaño (M + 1) * (N + 1) con M y N dados. Recorreremos entera
	dicha matriz, rellenandola como es debido (y siguiendo las ecuaciones antes descritas).
		-La complejidad, por tanto, del algoritmo que resuelve el problema es, en terminos de complejidad
		en tiempo, O(M * N) donde N el el numero de manzanas de norte a sur y M las de este a oeste.
		-La complejidad en espacio adicional es del orden de O(M * N) tambien.

	---VERSION OPTIMIZADA---
	En este caso, optamos por un vector de tamaño M + 1, y observar el mapa de la misma forma. En este caso, la comple
	jidad del algoritmo en tiempo es la misma, pero es espacio adicional es solo O(M), con M descrito anteriormente.
*/

// función que resuelve el problema
int max_paths(const std::vector<std::string> &mapa) {
	int N = mapa.size();
	int M = mapa[0].size();

	std::vector<int> vector(M + 1, 0);
	vector[1] = 1;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			if (mapa[i - 1][j - 1] != 'P'){
				vector[j] = vector[j] + vector[j - 1];	
			}
			else vector[j] = 0;
		}
	}
	
	return vector[M];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, M;
	std::cin >> N >> M;

    if (! std::cin)
        return false;
	std::vector<std::string> mapa;

	for (int i = 0; i < N; i++){
		std::string aux;
		std::cin >> aux;
		mapa.push_back(aux);
	}

	std::cout << max_paths(mapa) << "\n";

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