// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct tPelicula {
	int inicio;
	int duracion;

	tPelicula(int i, int d) : inicio(i), duracion(d) {};
	tPelicula() {};
};

bool operator<(const tPelicula &t1, const tPelicula &t2){
	return t1.inicio < t2.inicio;
}

int max_duracion(const std::vector<tPelicula> &peliculas){
	int N = peliculas.size();
	std::vector<std::vector<int>> duraciones(N + 2, std::vector<int>(24 * 60 + 1, 0));

	for (int i = N; i >= 1; i--){
		for (int j = 24 * 60; j >= 1; j--){
			if (peliculas[i - 1].inicio < j + 10){
				duraciones[i][j] = duraciones[i + 1][j];
			}
			else{
				duraciones[i][j] = std::max(duraciones[i + 1][peliculas[i - 1].inicio + peliculas[i - 1].duracion] + peliculas[i - 1].duracion,
					duraciones[i + 1][j]);
			}
		}
	}

	return duraciones[1][1];

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N;
	std::cin >> N;
    if (!N)
        return false;
    
	std::vector<tPelicula> peliculas;

	for (int i = 0; i < N; i++){
		int inicioH, inicioM, duracion;
		char x;
		std::cin >> inicioH >> x >> inicioM >> duracion;
		peliculas.push_back({ inicioH * 60 + inicioM, duracion });
	}
    
    // escribir sol
	std::cout << max_duracion(peliculas) << "\n";

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