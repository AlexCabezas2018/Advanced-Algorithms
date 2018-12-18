// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/*
	peliculas(i, j) === duracion maxima de minutos que puedo ver con las peliculas de i a N, sabiendo que la ultima pelicula la he visto en la hora j

	Recurrencia:
		peliculas(i, j) = peliculas(i + 1, j) si film(i).inicio + film(i).duracion < j + 10 (tiempo de demora)
		peliculas(i, j) = max(peliculas(i + 1, j), peliculas(i + 1, film(i).duracion + film(i).inicio) + film(i).inicio) en caso contrario.

		casos base:
			peliculas(0, j) = 0
*/


struct tPelicula {
	int inicio;
	int duracion;
	int fin;

	tPelicula(int i, int d) : inicio(i), duracion(d) {
		fin = inicio + duracion + 10;
	};

	tPelicula() {};
};

bool operator<(const tPelicula &t1, const tPelicula &t2){
	return t1.inicio < t2.inicio;
}

int max_duracion(const std::vector<tPelicula> &peliculas){
	int N = peliculas.size();
	std::vector<int> duraciones(24 * 60 + 1, 0);
	
	for (int i = N; i >= 1; i--) {
		for (int j = 0; j <= 24 * 60; j++) {
			if (peliculas[i - 1].inicio >= j) {
				duraciones[j] = std::max(duraciones[j], duraciones[peliculas[i - 1].fin] + peliculas[i - 1].duracion);
			}
		}
	}

	return duraciones[0];
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
		peliculas.push_back({ inicioH * 60 + inicioM, duracion});
	}

	std::sort(peliculas.begin(), peliculas.end());
    
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