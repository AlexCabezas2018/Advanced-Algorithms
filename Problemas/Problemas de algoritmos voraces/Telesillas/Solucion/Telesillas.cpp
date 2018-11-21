// Alejandro Cabezas Garriguez
// TAIS26


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


/*
    El problema consiste en encontrar el numero minimo de viajes necesarios para transportar a los turistas
    en el telesilla. Nos dan sus pesos y el peso maximo que puede aguantar el telesilla por viaje.
    Si nos fijamos, basta con ordenar los pesos de menor a mayor, y emparejar siempre el mas ligero
    con el mas pesado (de los no analizados). Si esa suma es menor o igual que el peso maximo, los empare
    jamos y encontramos una nueva pareja de ligero-pesado. Sin embargo, si nos pasamos, entonces es que
    el mas pesado no puede emparejarse con otro, asi que obligatoriamente debemos realizar un viaje
    con un solo pasajero (el mas pesado). Es por ello que pasamos a observar al siguiente menos pesado
    para continuar emparejando. El algoritmo parará cuando la variable que guarda la persona pesada sea menor
    estricto que la variable que lleva la persona ligera. Es estricto porque si ambas variables valen lo mismo
    debemos gastar un viaje en enviar al ultimo pasajero.
    En esencia, el algoritmo, aun llevando 2 indices, analiza cada elemento una unica vez, por lo que el algoritmo
    es de coste O(N) con N siendo el numero de turistas. Además, el vector de pesos debe estar ordenado, lo cual
    tiene un coste de O(N log N).
*/


// función que resuelve el problema
int resolver(std::vector<int> &weigths, int maxWeigth) {
    int ret = 0; //numero de viajes minimo.
    int weigthPerTravel = 0;
    int i = 0;
    int j = weigths.size() - 1;

    while(i <= j){
        weigthPerTravel = weigths[i] + weigths[j];
        if(weigthPerTravel <= maxWeigth){
            ret++; i++; j--;
        }
        else{
            ret++;
            j--;
        }
    }

    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numberUsers, maxWeigth;
    std::cin >> maxWeigth >> numberUsers;

    if (! std::cin)
        return false;
    
    std::vector<int> weights;
    for(int i = 0; i < numberUsers; i++){
        int weight;
        std::cin >> weight;
        weights.push_back(weight);
    }

    std::sort(weights.begin(), weights.end());

    std::cout << resolver(weights, maxWeigth) << "\n";
    
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