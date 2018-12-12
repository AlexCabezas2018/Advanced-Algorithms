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
	int N = word.size() - 1;

	std::vector<std::vector<int>> matriz(N + 1, std::vector<int>(N + 1, 0));

	for (int i = 1; i <= N - 1; i++){
		matriz[i][i] = 1;
	}

	for (int d = 1; d <= N - 1; d++) {
		for (int i = 1; i <= N - d; i++) {
			int j = i + d;
			if (word[i] == word[j]) {
				matriz[i][j] = 2 + matriz[i + 1][j - 1];
			}
			else {
				matriz[i][j] = std::max(matriz[i + 1][j], matriz[i][j - 1]);
			}
		}
	}

	int longMaxPalindromo = matriz[1][N];
	std::string cadena(longMaxPalindromo + 1, ' ');

	int iPorig = 1;
	int jPorig = N;
	int iCadena = 1;
	int jCadena = longMaxPalindromo;

	while (longMaxPalindromo > 0){
		if (word[iPorig] == word[jPorig]){
			cadena[iCadena] = word[iPorig];
			cadena[jCadena] = word[jPorig];
			iCadena++; iPorig++;
			jCadena--; jPorig--;
			longMaxPalindromo -= 2;
		}
		else if (longMaxPalindromo == 1){
			cadena[iCadena] = word[jPorig];
			longMaxPalindromo--;
		}
		else if (word[iPorig] != word[jPorig]){
			if (matriz[iPorig][jPorig - 1] > matriz[iPorig + 1][jPorig]){
				jPorig--;
			}
			else iPorig++;
		}
	}
	
	return cadena.substr(1, cadena.size() - 1);

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string word;
	std::cin >> word;

    if (! std::cin)
        return false;

	std::string sol;
	if (word.size() == 1){
		std::cout << word << "\n";
	}
	else {
		word = " " + word;
		sol = patindromo(word);
		std::cout << sol << "\n";
	}


    
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