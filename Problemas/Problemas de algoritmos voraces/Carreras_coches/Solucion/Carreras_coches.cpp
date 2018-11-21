// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <vector>

/*
	El problema consiste en encontrar el numero maximo de coches que pueden correr. Para ello, necesitas ponerles pilas (dos exactamente)
	y la suma de los voltajes de dichas pilas (datos que nos ofrece el problema) tiene que ser >= que un voltaje minimo V.
	Para ello, almacenamos los voltajes de las pilas en un vector, el cual ordenaremos de menor a mayor y comenzaremos a analizarlo.
	Para asegurarnos que estamos obteniendo el numero maximo de coches, lo que hacemos es sumar el dato menor (situado al principio del
	vector) con el ultimo (el mayor). Si esa suma no satisface que sea mayor o igual que V, sumamos el dato mayor con el siguiente al menor.
	Si hemos encontrado una combinacion de pilas que satiface la restriccion, entonces hemos encontrado, hasta el momento, el numero maximo de 
	coches que pueden correr (con los datos analizados). Como esas pilas ya corresponden a un coche, probamos con el siguiente menor y con el anterior
	al mayor. El analisis termina cuando, la variable que supuestamente es la mayor del vector es menor o igual al supuesto menor del vector (es decir,
	si los indices se cruzan).

	El coste del algoritmo es el siguiente. Aunque trabajemos sobre 2 indices, en realidad estamos observando cada elemento una y solo una vez, por lo que
	deducimos que el coste final es O(N) donde N es el numero de pilas. Este seria el coste del algoritmo que resuelve el problema. Previamente ordenamos el vector,
	con un coste O(N log(N)) donde N es numero de pilas. Si incluimos esto en nuestro algoritmo, el coste ascenderia a O(max(N log(N) + N)). 

*/


// función que resuelve el problema
int resolver(const std::vector<int> &voltages, int minV) {
	int ret = 0;
	int i = 0, j = voltages.size() - 1;
	while (i < j) {
		int volt = voltages[i] + voltages[j];
		if (volt >= minV) {
			ret++;
			i++;
			j--;
		}
		else i++;
	}

	return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int N, V;
	std::cin >> N >> V;

	std::vector<int>voltages;

	for (int i = 0; i < N; i++) {
		int value;
		std::cin >> value;
		voltages.push_back(value);
	}
	std::sort(voltages.begin(), voltages.end());
    
	std::cout << resolver(voltages, V) << "\n";
    // escribir sol
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}