// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*
	El problema consiste en encontrar el numero minimo de llamadas a la funcion "trim" para eliminar completamente la palabra.
	La funcion trim está explicada en el problema.
	Como no existe una estrategia voraz, optamos por resolverlo recursivamente, analizando todas las opciones posibles. 
	Como queremos que sea eficiente, lo haremos por programacion dinamica.
	Por tanto, llamaremos trim(i, j) al numero minimo de llamadas a la funcion trim para eliminar la subcadena obtenida 
	de la palabra principal desde i hasta j.

	Las ecuaciones de recurrencia son las siguientes:
		trim(i, j) = 1 + trim(i + k1, j - k2) si palabra[i] == palabra[j], donde k1 y k2 son el numerod de posiciones en los que deben colocarle i
		y j tal que palabra[i + k1] != palabra[i] y palabra[j - k2] != palabra[j]
		trim(i, j) = 1 + min(trim(i + k1, j), trim(i, j - k2)) si palabra[i] != palabra[j].

	Creamos una matriz (N + 1)*(N + 1). y la rellenamos por diagonales. El input inicial tiene que ser modificado para que se analicen todas las letras
	de la palabra (de no ser modificado, empezaria a analizar desde la segunda letra.)

	El coste de resolucion del problema es O((N - 1) * (N - d)) donde N es el numero de palabras y d son el numero de diagonales de la matriz.
	El coste en espacio adicional es O(N * N) donde N es el numero de caracteres de la palabra. Cabe decir que este problema puede optimizarse, 
	de tal forma que mejorariamos el coste en espacio adicional.
*/


int min_trim_calls(std::string word) {
	int N = word.length();
	std::vector<std::vector<int>> llamadas(N + 1, std::vector<int>(N + 1, 0));

	for (int i = 1; i <= N; i++) {
		llamadas[i][i] = 1;
	}

	for (int d = 1; d <= N - 1; d++) {
		for (int i = 1; i <= N - d; i++) {
			int j = i + d;
			int k1 = 0, k2 = 0;
			int result;

			//calculo de k1
			while (word[k1 + i] == word[i]) k1++;
			//calculo de k2
			while (word[j - k2] == word[j]) k2++;

			if (word[i] == word[j]) {
				llamadas[i][j] = 1 + llamadas[i + k1][j - k2];
			}
			else {
				llamadas[i][j] = std::min(llamadas[i + k1][j] + 1, llamadas[i][j - k2] + 1);
			}
		}
	}
	return llamadas[1][N - 1]; //En este caso N vale un caracter mas, por lo que llamadas [1][N] es el numero de trims contando con el vacio, por eso N - 1.
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string word;
	std::cin >> word;

    if (! std::cin)
        return false;
	word = ' ' + word;

	std::cout << min_trim_calls(word) << "\n";
    
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