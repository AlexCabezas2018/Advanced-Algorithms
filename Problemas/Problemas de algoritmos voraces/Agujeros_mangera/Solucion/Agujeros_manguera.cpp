// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


/*
	Este problema consiste en encontrar el numero minimo de parches que se necesitan para cubrir todos los agujeros de una manguera. El problema
	especifica que todos los parches tienen la misma longitud y, ademas, nos comenta que un parche de una longitud L puede tapar los agujeros que esten
	a una distancia L desde donde se coloca el parche. Asi pues, lo que tenemos que hacer es, al encontrar un agujero, poner un parche y ver hasta donde
	cubre este. Si el siguiente punto donde hay un agujero ya está cubierto, pues sencillamente es que no necesitamos poner otro parche.

	-Asi pues, el algoritmo lo unico que hace es mirar por todos los agujeros de la manguera. Las operaciones que realiza dentro son de O(1)
	por lo que podemos suponer que el coste del algoritmo que resuelve el problema es del orden O(N) donde N es el numero de agujeros
	de la mamnguera.

*/


// función que resuelve el problema
int resolver(const std::vector<int> &holes, int length) {
	int ret = 0; //cantidad de parches.
	int watched = 0;
	for (int i = 0; i < holes.size(); i++) {
		//holes[i] es el punto donde se encuentra el agujero.
		if (watched < holes[i]) { //Esto quiere decir que el agujero no está cubierto.
			ret++;
			watched = holes[i] + length;
		}
		//else {} quiere decir que si que esta cubierto, por lo que no nos preocupamos por el, no necesita un parche nuevo.
		
	}
	return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int N, L;
	std::cin >> N >> L;

    if (! std::cin)
        return false;
    
	std::vector<int> holes;
	for (int i = 0; i < N; i++) {
		int value;
		std::cin >> value;
		holes.push_back(value);
	}

	std::cout << resolver(holes, L) << "\n";

    
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