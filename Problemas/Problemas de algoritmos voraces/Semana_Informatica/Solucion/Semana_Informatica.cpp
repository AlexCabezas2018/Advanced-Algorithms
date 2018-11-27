// Alejandro Cabezas Garriguez
// TAIS26


//TODO aun no terminado

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>

struct Evento {
    int beg;
    int end;

    Evento(int b, int e): beg(b), end(e) {};
};

bool operator<(const Evento &t1, const Evento &t2){
    return t1.beg < t2.beg;
}

// función que resuelve el problema
int resolver(const std::vector<Evento> &datos) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> friendsQueue;

    int sol = 0;
    int porDondeVoyYo = datos[0].end;
    int i = 1;
    while(i < datos.size()){
        if(datos[i].beg >= porDondeVoyYo){
            porDondeVoyYo = datos[i].end;
        }
        else if((porDondeVoyYo > datos[i].beg && porDondeVoyYo < datos[i].end)){ //necesito un amigo
            if(friendsQueue.empty()){
                sol++;
                friendsQueue.push(datos[i].end);
            }
            else if(friendsQueue.top() <= datos[i].beg){
                friendsQueue.pop();
                friendsQueue.push(datos[i].end);
            }
            else{ //El amigo que antes ha acabado aun no ha acabado para atender la conferencia.
                sol++;
                friendsQueue.push(datos[i].end);
            }
        }
        i++;
    }

    return sol;
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    std::cin >> N;
    
    if (!N)
        return false;
    
    std::vector<Evento> datos;

    for(int i = 0; i < N; i++){
        int b, e;
        std::cin >> b >> e;
        datos.push_back({b, e});
    }
    
    std::sort(datos.begin(), datos.end());

    std::cout << resolver(datos) << "\n";
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