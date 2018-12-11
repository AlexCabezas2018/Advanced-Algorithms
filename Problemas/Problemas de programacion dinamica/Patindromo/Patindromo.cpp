// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

// función que resuelve el problema
std::string patindromo(const std::string &word) {
	int N = word.size();

	std::vector<std::vector<int>> matriz(N + 1, std::vector<int>(N + 1, 0));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int k = N - j;
			if (word[i - 1] == word[k]) {
				matriz[i][j] = 1 + matriz[i - 1][j - 1];
			}
			else {
				matriz[i][j] = std::max(matriz[i - 1][j], matriz[i][j - 1]);
			}
		}
	}

	std::cout << matriz[N][N] << "\n";

	std::cout << "\n";


	return " ";

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string word;
	std::cin >> word;

    if (! std::cin)
        return false;

	patindromo(word);


    
	//std::cout << patindromo(word) << "\n";
    
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