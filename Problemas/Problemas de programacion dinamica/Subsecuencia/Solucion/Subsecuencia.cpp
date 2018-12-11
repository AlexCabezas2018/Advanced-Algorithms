// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*El problema consiste en encontrar la longitud de la subcadena más larga entre dos palabras dadas.
Como no encontramos una estrategia voraz que solucione el problema, deberemos explorar todas las soluciones.
Para ello, usaremos programacion dinamica.

definimos la operacion "subseq(i, j)" a la longitud de la subcadena mas larga entre las subcadenas s1 y s2.
S1 será la subcadena de la primera palabra que comparte los carateres posicionados desde 1, ... , i 
S2 será la subcadena de la segunda palabra que comparte los caracteres posicionados desde 1, ..., j

La llamada inicial será subseq(N, M) donde N y M son las longitudes de las palabras inciales.

La recursividad está definida de la siguiente manera:
    subseq(i, j) = max(subseq(i - 1, j), subseq(i, j - 1)) si p1[i] != p2[j] (si los caracteres de las palabras en esa posicion son distintos...)
        -Esto quiere decir que si los caracteres en esa posicion son distintos, la longitud máxima será el meximo de las longitudes resultates de las demás sucadenas (recursivamente)

    subseq(i, j) = 1 + subseq(i - 1, j - 1)
        -Si coinciden, entonces el maximo será el maximo de la siguiente subcadena más 1

El coste en tiempo del algoritmo que resuelve el problema consiste en un bucle for anidado, uno va hasta N y otro hasta M, por tanto, el coste total es O(M * N)
donde M, N está explicados anteriormente.

El coste en espacio es O(M * N) también.
Se puede optimizar en espacio.
*/


int max_suseq(std::string &word1, std::string &word2, const int N, const int M) {

	std::vector<std::vector<int>> matriz(N + 1, std::vector<int>(M + 1, 0));
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (word1[i - 1] != word2[j - 1]) {
				matriz[i][j] = std::max(matriz[i - 1][j], matriz[i][j - 1]);
			}
			else {
				matriz[i][j] = matriz[i - 1][j - 1] + 1;
			}
		}
	}

	return matriz[N][M];
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string word1, word2;
	std::cin >> word1 >> word2;

    if (! std::cin)
        return false;
	
	int N = word1.size();
	int M = word2.size();

	std::cout << max_suseq(word1, word2, N, M) << "\n";


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