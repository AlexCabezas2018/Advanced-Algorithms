#include <vector>
#include <string>

using Mapa = std::vector<std::string>;

// --- Coste de la solucion --- //
// --- O() --- //

class Solution {
public:
	Solution(const Mapa &map) : F(map.size()), C(map[0].size()), marked(map.size(), std::vector<bool>(map[0].size(), false)), numOvBlancas(0) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!marked[i][j] && map[i][j] == '.') {
					numOvBlancas++;
					dfs(map, i, j);
				}
			}
		}
		numOvBlancas--;
	}

	int getSolution() { return numOvBlancas; }

private:
	std::vector<std::vector<bool>> marked;
	int F, C;
	int numOvBlancas;
	const std::vector<std::pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1} };

	bool correcta(int i, int j) {
		return (i >= 0 && i < F && j >= 0 && j < C);
	}

	void dfs(const Mapa &m, int i, int j) {
		marked[i][j] = true;

		for (auto dir : dirs) {
			int ni = i + dir.first;
			int nj = j + dir.second;

			if (correcta(ni, nj) && !marked[ni][nj] && m[ni][nj] == '.') {
				dfs(m, ni, nj);
			}

		}
	}
};