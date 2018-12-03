// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct Varilla {
    int longitud;
    int precio;

    Varilla(int l, int p): longitud(l), precio(p) {};
    Varilla(): longitud(0), precio(0) {};
};


/*
	Te ofrecen un conjunto de varillas y, a partir de eso, resolvemos las 4 preguntas que nos proponen.
	Aplicaremos estrategias dinámicas para resolverlos.

	Cada operacion es O(L * N) donde L y N estan explicados en cada función. Por tanto, y sabiendo que L y N son las mismas variables en todas las funciones,
	El coste de la operacion total es O(4(N * L))
*/

bool esPosible(std::vector<Varilla> const &vars, const int N, const int L) { //Coste: O(N * L) donde N son el numero de varillas, L la longitud a alcanzar
	/*
		varillas(i, j) = varillas(i - 1, j) si j < logitud(varilla[i])
		varillas(i, j) = varillas(i - 1, j - longitud(varilla[i]) || varillas(i - 1, j) en otro caso
	*/


	std::vector<int> vector(L + 1, false);
	vector[0] = true;

    for(int i = 0; i < vars.size(); i++){
        for(int j = L; j >= 1; j--){
			if(j >= vars[i].longitud) vector[j] = vector[j] || vector[j - vars[i].longitud];
        }
    }

    return vector[L];
}

int posibles_maneras(std::vector<Varilla> const &vars, const int N, const int L){ //Coste: O(N * L) donde N son el numero de varillas, L la longitud a alcanzar
	/*
		varillas(i, j) = varillas(i - 1, j) si j < logitud(varilla[i])
		varillas(i, j) = varillas(i - 1, j - longitud(varilla[i])) + varillas(i - 1, j) en otro caso
	*/


	std::vector<int> vector(L + 1, 0);
	vector[0] = 1;

    for(int i = 0; i < vars.size(); i++){
        for(int j = L; j >= 1; j--){
			if (vars[i].longitud <= j) vector[j] = vector[j] + vector[j - vars[i].longitud];
        }
    }

    return vector[L];
}

int minimo_varillas(std::vector<Varilla> const &vars, const int N, const int L) { //Coste: O(N * L) donde N son el numero de varillas, L la longitud a alcanzar
	/*
	varillas(i, j) = varillas(i - 1, j) si j < logitud(varilla[i])
	varillas(i, j) = min(varillas(i - 1, j - longitud(varilla[i]), varillas(i - 1, j) + 1) en otro caso
	*/

	const int INF = 1000000000;
	std::vector<int> vector(L + 1, INF);
	vector[0] = 0;

	for (int i = 0; i < vars.size(); i++) {
		for (int j = L; j >= 1; j--) {
			if(vars[i].longitud <= j) vector[j] = std::min(vector[j], 
				vector[j - vars[i].longitud] + 1);
		} 
	}

	return vector[L];
}

int minimo_coste(std::vector<Varilla> const &vars, const int N, const int L) { //Coste: O(N * L) donde N son el numero de varillas, L la longitud a alcanzar
	/*
	varillas(i, j) = varillas(i - 1, j) si j < logitud(varilla[i])
	varillas(i, j) = min(varillas(i - 1, j - longitud(varilla[i]), varillas(i - 1, j) + precio(varilla[i]) en otro caso
	*/

	const int INF = 1000000000;
	std::vector<int> vector(L + 1, INF);
	vector[0] = 0;

	for (int i = 0; i < vars.size(); i++) {
		for (int j = L; j >= 1; j--) {
			if (vars[i].longitud <= j) vector[j] = std::min(vector[j], 
				vector[j - vars[i].longitud] + vars[i].precio);
		}
	}

	return vector[L];
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, L;
    std::cin >> N >> L;

    if (! std::cin)
        return false;

    std::vector<Varilla> varillas;
    for(int i = 0; i < N; i++){
        int l, p;
        std::cin >> l >> p;
        varillas.push_back({l, p});
    }

    if(esPosible(varillas, N, L)){
        std::cout << "SI ";
        std::cout << posibles_maneras(varillas, N, L) << " ";
		std::cout << minimo_varillas(varillas, N, L) << " ";
		std::cout << minimo_coste(varillas, N, L) << "\n";
    } 

    else std::cout << "NO\n";
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