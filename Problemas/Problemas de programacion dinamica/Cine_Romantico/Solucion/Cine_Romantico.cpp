// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/*
	El problema consiste en encontrar el máximo tiempo que puede estar viendo películas, sabiendo la hora a la que empieza cada pelicula y la duracion que esta tiene,
	y sabiendo tambien que entre pelicula y pelicula, invierte 10 minutos en cambiar de sala, comprar palomitas...
	Como no encontramos una estrategia voraz que asegure que siempre vamos a obtener el máximo tiempo, tenemos que explorar todo el arbol de soluciones. Para mejorar
	en costes tanto en tiempo como en espacio adiciona, optaremos por solucionar el problema mediante programacion dinamica. Asi pues:
		Llamamos peliculas(i, j) a la duracion máxima de minutos que puedo ver con las peliculas de i a N, sabiendo que la ultima pelicula que he visto he terminado de verla
		a la hora j, contando tambien con los 10 minutos de los que hemos hablado antes. La llamada inicial de este problema seria peliculas(N, 0).
		Teniendo en cuenta esa definicion, optaremos por las siguientes ecuaciones de recurrencia:
			peliculas(i, j) = peliculas(i + 1, j) si film(i).inicio < j
			peliculas(i, j) = max(peliculas(i + 1, j), peliculas(i + 1, film(i).fin) + film(i).duracion) en caso contrario.

		Los casos base que debemos considerar son los siguientes:
			peliculas(0, j) = 0

	Como sabemos que todas las peliculas se realizan en el mismo dia, podemos usar las 24 horas como una ventaja a la hora de crear las estructuras de datos
	---VERSION SIN OPTIMIZAR---
	El coste del problema usando programacion dinamica y sin optimizacion extra es, en termimos de tiempo, del orden de O(N * 24*60) donde N es el numero de peliculas
	y 24*60 el numero de minutos que tiene un día, que es lo que usamos como ventaja para determinar la solucion. La complejidad en espacio adicional es del orden de
	O(N * 24*60) puesto que creamos una matriz de dichas dimensiones.
	---VERSION OPTIMIZADA---
	En este caso, aunque tenemos solo un vector (lo cual mejora la complejidad en espacio adicional), iteramos sobre todos los elementos del vector N veces, por lo que
	la complejidad en tiempo es igual a la complejidad de la version sin optimizar. Sin embargo, la complejidad en espacio adicional se ha visto afectada, siendo en este
	caso del orden de O(24*60) donde esa cifra ya la hemos comentado antes.
*/


struct tPelicula {
	int inicio;
	int duracion;
	int fin;

	tPelicula(int i, int d) : inicio(i), duracion(d) {
		fin = inicio + duracion + 10; //Le añadimos el tiempo de demora
	};

	tPelicula() {};
};

bool operator<(const tPelicula &t1, const tPelicula &t2){ //debemos ordenar las peliculas por inicio.
	return t1.inicio < t2.inicio;
}

int max_duracion(const std::vector<tPelicula> &peliculas){
	int N = peliculas.size();
	std::vector<int> duraciones(24 * 60 + 11, 0); //es +11 y no +1 porque es posible que una pelicula acabe mas tarde de las "00:00"
	
	for (int i = N; i >= 1; i--) {
		for (int j = 0; j <= 24 * 60; j++) {
			if (peliculas[i - 1].inicio >= j && peliculas[i - 1].fin <= 24 * 60 + 10) {
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