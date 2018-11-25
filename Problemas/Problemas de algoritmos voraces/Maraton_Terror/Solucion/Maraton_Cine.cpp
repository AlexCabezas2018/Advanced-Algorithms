// Alejandro Cabezas Garriguez
// TAIS26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <functional>

struct Film {
    int begin;
    int end;
     
    Film(int b, int e): begin(b), end(e) {};
    Film(): begin(0), end(0) {};
};

bool operator>(const Film &f1, const Film &f2){
    return (f1.end > f2.end) || (f1.end == f2.end && f1.begin > f2.begin); //la peli mas corta
}

// función que resuelve el problema
int resolver(std::priority_queue<Film, std::vector<Film>, std::greater<Film>> &films) {
    int ret = 1;
    int timeSpent = films.top().end;
    while(!films.empty()){
        if(films.top().begin >= timeSpent){
            ret++;
            timeSpent = films.top().end;
        }
        films.pop();
    }
    return ret;
}

int readHour(std::istream &input){
    int hour, minutes;
    char colon;
    std::cin >> hour >> colon >> minutes;
    return (hour * 60) + minutes;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int filmsNumber;
    std::cin >> filmsNumber;

    if (!filmsNumber)
        return false;
    
    std::priority_queue<Film, std::vector<Film>, std::greater<Film>> films;

    for(int i = 0; i < filmsNumber; i++){
        int time = readHour(std::cin), value;
        std::cin >> value;
        films.push({time, time + value + 10});
    }

    std::cout << resolver(films) << "\n";
    
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
    // system("PAUSE");
     #endif
    
    return 0;
}