// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

/*
	El problema nos pide que encontremos el palindromo mas largo dada una cadena. Como no podemos encontrar una estrategia
	voraz que nos ayude a resolver el problema, necesitamos explorar todas las soluciones posibles. Decidimo aplicar entonces programacion
	dinamica.

	Determinamos una funcion patindromo(i , j) que indica la longitud maxima del palindromo de la subcadena de la palabra principal que va desde
	i hasta j.

	Por tanto, tenemos: 
		patindromo(i, j) = 2 + patindromo(i + 1, j - 1) si p[i] == p[j] es decir, escgemos esos dos caracteres y se los sumamos a la longitud del palindromo interno
		patindromo(i, j) = max(patindromo(i + 1, j), patindromo(i, j - 1)) si p[i] != p[j] Quiere decir que la subcadena que consideramos no es un palindromo, deberemos
		considerar los casos en el que, o bien me quedo con una letra, o bien con otra, y quedarme con el maximo de los dos.

	Los casos base seria:
		patindromo(i, 0) = 0
		patindrom(0, j) = 0 Ambos son palindromos, pero es la cadena vacia, de tamaño 0

		patindromo(i, j) = 1 si i == j un caracter es palidromo de si mismo, y tiene como longitud 1

	La llamada incial seria patindromo(1, palabra.size())

	Dicho esto, resolveremos el problema creando una matriz de resultados, y explorando dicha matriz por diagonales
	El coste de la resolucion del por problema es O(N * N + longMaxPalndromo) donde N es el tamaño de la matriz
	y longMaxPalidromo es la longitud del palindromo máximo
	El coste en espacio adicional seria o(N * N + longMaxPalindromo) puesto que tenemos que crear la matriz, y ademas la necesitamos para
	recuperar la solucion. Tambien se crea un string vacio del tamaño de longMaxPalindromo, que es el que devolvemos.
*/


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
     //system("PAUSE");
     #endif
    
    return 0;
}