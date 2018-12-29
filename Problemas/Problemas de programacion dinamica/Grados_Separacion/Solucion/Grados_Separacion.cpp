//Alejandro Cabezas Garriguez
//TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Matriz.h"
#include <algorithm>
#include <unordered_map>

/*
	El problema consiste en encontrar el grado de separacion de una red determinada,
	que consiste en el maximo grado de la red entre 2 personas cualesquiera. El grado de separacion
	entre 2 personas esta definido en el problema. Debemos encontrar los grados de separacion entre todos
	los pares de personas y escoger el que tenga mayor. Por tanto, debemos explorar todo el arbol de soluciones.
	Usaremos programacion dinamica para optimizar el proceso.
	Si nos fijamos, basicamente lo que nos dan es un grafo en el que los vertices son las personas
	y un vertice conecta con otro si son amigos. El coste de las aristas es 1, puesto que es el grado
	de separacion que comparten. Por tanto las relaciones son simplemente las aristas, que expresaremos
	en una matriz de adyacencia. Por tanto, para sacar todos los grados de separacion usaremos estas ecuaciones
	recursivas:
		- Llamamos G(i, j) a la matriz de adyacencia del grafo que vale:
			- 0 si i == j
			- coste si hay arista de i a j
			- INFINITO si no hay arista de i a j

		- Llamamos Ck(i, j) como el coste minimo para ir de la persona i a la j, usando como amigos intermedios
		los que esten entre 1 y k
			- La recurrencia será: Ck(i, j) = min(Ck-1(i, j), Ck-1(i, k) + Ck-1(k, j)).

		- Como vemos, resolveremos este problema mediante el algoritmo de floyd, el cual tiene una complejidad
		en tiempo de O(N * N * N) donde N es el numero de personas de la red y en espacio adicional O(1).

	- Por ultimo, como la matriz de adyacencia trabaja con numeros (es decir, no se espera que los vertices sean nombres),
	necesitamos un mecanismo lo mas eficiente posible para transformar los nombres en identificadores para la matriz de adyacencia,
	es por ello que usamos un hashmap cuya clave es el nombre y su valor el entero que asociaremos a la matriz.

*/

const int INF = 1000000000;

void Floyd(Matriz<int> const &G, Matriz<int> &C, Matriz<int> &camino){
	int n = G.numfils() - 1;
	C = G;
	camino = Matriz<int>(n + 1, n + 1, 0);
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				int temp = C[i][k] + C[k][j];
				if (temp < C[i][j]){
					C[i][j] = temp;
					camino[i][j] = k;
				}
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, R;
	std::cin >> N >> R;
    if (! std::cin)
        return false;

	std::unordered_map<std::string, int> amigos;

	Matriz<int> grafo(N + 1, N + 1, INF);
	for (int i = 1; i <= N; i++){
		grafo[i][i] = 0;
	}

	int values = 1;
	std::string nombre1, nombre2;
	for (int i = 0; i < R; i++){
		std::cin >> nombre1 >> nombre2;
		auto find1 = amigos.find(nombre1);
		auto find2 = amigos.find(nombre2);
		if (find1 == amigos.end()){ //No esta aun en el hashmap
			amigos[nombre1] = values;
			values++;
		}
		if (find2 == amigos.end()){
			amigos[nombre2] = values;
			values++;
		}
		//Añadimos la relacion en ambos sentidos
		grafo[amigos[nombre1]][amigos[nombre2]] = 1;
		grafo[amigos[nombre2]][amigos[nombre1]] = 1;
	}

	Matriz<int> C(0, 0); Matriz<int> camino(0, 0);
	Floyd(grafo, C, camino);
	int max = 0;
	//Analizamos la matriz que obtenemos, buscando el grado maximo que el algoritmo de Floyd nos ha proporcionado
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			max = std::max(max, C[i][j]);
		}
	}

	if (max != INF) std::cout << max << "\n"; 
	else std::cout << "DESCONECTADA\n"; //Quiere decir que la red no esta del todo conectada, hay algun par de amigos que no pueden conectarse entre ellos.
    
    
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