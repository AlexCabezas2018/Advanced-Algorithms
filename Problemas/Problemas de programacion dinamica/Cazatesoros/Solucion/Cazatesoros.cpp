// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/*
    Ël problema consiste en encontrar la combinacion que satisfaga el conseguir la mayor cantidad
    de oro podible, teniendo como restriccion la cantidad de oxigeno que dispone y otras más contadas
    en el problema.
    
    Por tanto, resolveremos el problema con programaion dinamica, reduciendo asi considerablemente
    el coste de la operacion (en lugar de optar por la recursividad).

    Llamaremos tesoros(i, j) a la maxima cantidad de oro que puede recogerse teniendo i cofres
    y disponiendo de una cantidad j de oxigeno. Por tanto, las ecuaciones resursivas son:

    tesoros(i, j) = tesoros(i - 1, j) si 3 + profundidad(cofre[i]) > j
    tesoros(i, j) = max(tesoros(i - 1, j), tesoros(i - 1, j - 3 * profundidad(cofre[i]) + oro(cofre[i]))) en caso contrario.

    El coste de la operacion que obtiene la maxima cantidad de oro es del orden de O(n*M) donde n son el numero
    de cofres y M la cantidad de segundos disponibles.

    El coste de la operacion que recupera la solucion es del orden de O(n) donde n está explicado más arriba.

*/


const int INF = 1000000000;

struct Cofre {
    int profundidad;
    int oro;

    Cofre(int p, int o): profundidad(p), oro(o) {};
    Cofre(): profundidad(0), oro(0) {};
};

int max_oro(std::vector<std::vector<int>> &matriz, const std::vector<Cofre> &cofres, const int S) {
	int N = cofres.size() - 1;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= S; j++){
            if(3 * cofres[i].profundidad > j){
                matriz[i][j] = matriz[i - 1][j];
            }
            else{
                matriz[i][j] = std::max(matriz[i - 1][j], 
                matriz[i - 1][j - 3 * cofres[i].profundidad] + cofres[i].oro);
            }
        }
    }
    return matriz[N][S];
}

std::vector<bool> recuperar_sol(const std::vector<std::vector<int>> &matriz, const int S, const std::vector<Cofre> &cofres, int &cualesQ){
	std::vector<bool> cuales(matriz.size(), false);
	int resto = S;

	for (int i = matriz.size() - 1; i >= 1; i--){
		if (matriz[i][resto] == matriz[i - 1][resto]) cuales[i] = false;
		else{
			cuales[i] = true;
			cualesQ++;
			resto = resto -  3 * cofres[i].profundidad;
		}
	}

	return cuales;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int segundos;
    std::cin >> segundos;
    
    if (! std::cin)
        return false;

    int N;
    std::cin >> N;
    std::vector<Cofre> cofres(N + 1);

    for(int i = 1; i <= N; i++) {
        int p, o;
        std::cin >> p >> o;
		cofres[i] = Cofre(p, o);
    }

    std::vector<std::vector<int>> matriz(N + 1, std::vector<int>(segundos + 1, 0));
    //casos base
    for(int i = 0; i <= N; i++){
        matriz[i][0] = 0;
    }

    for(int j = 1; j <= segundos; j++){
        matriz[0][j] = 0;
    }

	std::vector<bool> cofresRec;
	int cuales = 0;
    std::cout << max_oro(matriz, cofres, segundos) << "\n";
	cofresRec = recuperar_sol(matriz, segundos, cofres, cuales);
	std::cout << cuales << "\n";
	if (cuales){
		for (int i = 1; i < cofresRec.size(); i++){
			if (cofresRec[i]){
				std::cout << cofres[i].profundidad << " " << cofres[i].oro << "\n";
			}
		}
	}
	std::cout << "----\n";

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