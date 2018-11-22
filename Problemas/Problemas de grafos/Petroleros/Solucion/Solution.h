#include "ConjuntosDisjuntos.h"
#include <vector>
#include <string>
#include <algorithm>

//Direcciones posibles
const std::vector<std::pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 },{ 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };

class Solution {
using Map = std::vector<std::string>;

public:
	Solution(const Map &m, int f, int c) : F(f), C(c), set(f * c), 
		marked(f, std::vector<bool>(c, false)), tamMax(0), map(m) {
		for (int i = 0; i < F; i++){
			for (int j = 0; j < C; j++){
				if (!marked[i][j] && m[i][j] == '#'){
					//Encontramos nueva mancha
					int tamNuevaMancha = 0;
					dfs(map, i, j, tamNuevaMancha);
					tamMax = std::max(tamMax, tamNuevaMancha);
				}
			}
		}
	}

	//Actualiza el tamaño en funcion de la nueva mancha.
	void actualiza(int i, int j){
		map[i][j] = '#';
		marked[i][j] = true;
		bool unidos = true;
		int posicion = i * C + j;
		for (auto dir : dirs){
			int ni = i + dir.first;
			int nj = j + dir.second;
			if (correcta(ni, nj) && marked[ni][nj] && map[ni][nj] == '#'){
				unidos = false;
				int aUnir = ni * C + nj;
				set.unir(posicion, aUnir);
				tamMax = std::max(tamMax, set.tam(aUnir));
			}
		}
		if (unidos){
			tamMax = std::max(tamMax, set.tam(posicion));
		}
	}

	int getSolution() { return tamMax; }

private:
	ConjuntosDisjuntos set;
	std::vector<std::vector<bool>> marked;
	Map map;
	int F, C;
	int tamMax;

	bool correcta(int i, int j){
		return i >= 0 && i < F && j >= 0 && j < C;
	}

	//Recorrido en profundidad.
	void dfs(const Map &map, int i, int j, int &tamMancha){
		marked[i][j] = true;
		tamMancha++;
		int posAUnir = i * C + j;
		for (auto dir : dirs){
			int ni = i + dir.first;
			int nj = j + dir.second;
			if (correcta(ni, nj) && !marked[ni][nj] && map[ni][nj] == '#'){
				int posx = ni * C + nj;
				set.unir(posAUnir, posx);
				dfs(map, ni, nj, tamMancha);
			}
		}
	}
};