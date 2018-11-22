// Alejandro Cabezas Garriguez
// TAIS26

/*
    El problema consiste en encontrar el mayor numero de peliculas que la persona podrá visitar en un
    dia. Para ello contamos con las horas a las que empieza y acaba. Tambien sabemos que, despues de acabar
    la pelicula, deben trascurrir unos diez minutos que, segun el problema, es el tiempo que tarda la persona
    en cambiar de sala, comprar palomitas... 
    En esencia, debemos priorizar (ordenar) las peliculas que acaben antes y, para las que acaben a la misma hora, las que duren
    menos (es decir, las que empiecen antes tambien). Esta es la estrategia que usaremos.
    Para la implementacion, el problema es practicamente igual al anterior, el de "Primera linea de playa". Basta con elegir las
    peliculas por orden de entrada (puesto que la entrada ha sido previamente ordenada) y averiguar si la siguiente pelicula
    cumple con los requisistos que hemos impuestos (en este caso que no se solape y que ha pasado un tiempo minimo de 10 minutos entre
    peliculas).

    El coste de introduccion de los elementos en la cola de prioridad es del orden O(log N) donde N es el numero de peliculas.
    El coste del algoritmo que resuelve el problema consiste en una iteracion completa de todos los elementos de una cola de prio-
    ridad. Cada operacion de la cola es O(log N), y, como observamos todos los elementos, el coste total es O(N log N) con N explica-
    do anteriormente.
*/


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
        std::cin >> value; //Tiempo trascurrido (incio + value = final)
        films.push({time, time + value + 10}); //Añadimos 10 minutos mas porque nos dicen que tarda 10 minutos en cambiar de sala...
                                               //Esto lo interpretamos como que la pelicula "dura 10 minutos mas".
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