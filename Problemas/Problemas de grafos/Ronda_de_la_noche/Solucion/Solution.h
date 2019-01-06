#include <vector>
#include <queue>

/*El problema consiste en encontrar la distancia del camino mas corto para ir desde el principio hasta el final del
jardin, sin ser detectado por ningun sensor, el cual tiene un ranto de 0 a 9 hacia las casillas de arriba, abajo, izquierda y derechaç
Lo que haremos sera leer el tablero y una vez leido, asignar la señal correspondiente a cada sensor, puesto que al fin y al cabo, los sensores
actuan como muros, pero no podemos asignarle el caracter de muro porque si lo hacemos, entonces no podriamos diferenciarlo de un muro, y eso podria
conllevar problemas. Una vez leido el tablero y modificado lo tenemos grosso modo es un grafo, en el que los vertices son las casillas y un
vertice esta conectado por otro si es vecino suyo (sin contar las diagonales). Por ser un grafo implicito, podemos aplicar las tecnicas aprendidas,
en este caso usaremos una busqueda en anchura. Este nos devuelve todas las distancias minimas desde un punto dado (el nuestro es el que marca el caracter
E) y lo unico que debemos hacer es devolver la distancia hasta llegar al final (en nuetro mapa esta representado como una P). Si este ditancia es
0, quiere decir que no hay camino.

El coste que tiene este algoritmo en tiempo será O(V + E), puesto que recorremos todos los vertices y aristas. V es el numero de vertices
y E es el numero de aristas.*/

using Mapa = std::vector<std::vector<char>>;

class Solution {
public:
	Solution(const Mapa &mapa, std::pair<int, int> &inicio, const std::pair<int, int> &fin) : marked(mapa.size(), std::vector<bool>(mapa[0].size(), false)),
		distTo(mapa.size() ,std::vector<int>(mapa[0].size(), 0)), solution(0) {
		if (mapa[inicio.first][inicio.second] == 'E'){ //Al reescribir el tablero para asignarle la señal a los sensores, es posible que se sobreescriba la señal a la entrada.
			bfs(mapa, inicio.first, inicio.second);		//Queriendo decir eso que la entrada está ya vigilada por un sensor, lo cual hace que sea imposible cruzar el jardin
			solution = distTo[fin.first][fin.second];
		}
	}

	int getSolution() {
		return solution;
	}

private:
	std::vector<std::vector<bool>> marked;
	std::vector<std::vector<int>> distTo;
	int solution;

	void bfs(const Mapa &mapa, int i, int j){
		std::queue<std::pair<int, int>> q;
		std::vector<std::pair<int, int>> direcciones = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		distTo[i][j] = 0;
		marked[i][j] = true;
		q.push({ i, j });
		while (!q.empty()){
			auto p = q.front(); q.pop();
			for (auto dir : direcciones){
				int ni = p.first + dir.first;
				int nj = p.second + dir.second;
				bool ok = ni >= 0 && ni < mapa.size() && nj >= 0 && nj < mapa[0].size();
				if (ok && !marked[ni][nj] && mapa[ni][nj] != 'S' && mapa[ni][nj] != '#'){
					distTo[ni][nj] = distTo[p.first][p.second] + 1;
					marked[ni][nj] = true;
					q.push({ ni, nj });
				}
			}
		}
	}
};