// Alejandro Cabezas Garriguez
// TAIS26

/*
    El problema consiste en encontrar el numero maximo de batallas que el equipo aliado va
    a ganar, conociendo el numero de tropas de cada pelotón de cada equipo.
    La estrategia consiste en comprobar si el peloton minimo de nuestro equipo
    supera o iguala el minimo del equipo enemigo. Si no es así, probamos con el siguiente, así hasta.
    o buen no tener mas pelotones que analizar.
    El coste de ordenar ambos vectores es O(NlogN) donde N es el numero de pelotones.
    El coste del algoritmo que resuelve el problema es iterar en los dos pelotones, 
    , analizamos como maximo cada elemento una vez, luego el coste final es O(N) donde
    N esta explicado mas arriba.

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


// función que resuelve el problema
int resolver(const std::vector<int> &our, const std::vector<int> &enemy) {
    int ret = 0;
    int i = 0, j = 0;
    while(i < our.size() && j < enemy.size()){
        if(our[i] >= enemy[j]){
            ret++; i++; j++;
        }
        else i++;
    }
    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int soldiersNumber;
    std::cin >> soldiersNumber;

    if (! std::cin)
        return false;

    std::vector<int> our;
    std::vector<int> enemy;

    for(int i = 0; i < soldiersNumber; i++){
        int value;
        std::cin >> value;
        enemy.push_back(value);
    }

    for(int i = 0; i < soldiersNumber; i++){
        int value;
        std::cin >> value;
        our.push_back(value);
    }

    std::sort(enemy.begin(), enemy.end());
    std::sort(our.begin(), our.end());

    std::cout << resolver(our, enemy) << "\n";
    
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