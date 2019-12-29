#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(a * b)
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 							(b == 0) v (a == b)
 *
 * 			T(a-1,b-1) + T(a-1,b) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using row = std::vector<int>;

using matrix = std::vector<row>;

int combinatorio(matrix& m, const int& a, const int& b) {

	if(b == 0 || a == b) {

		m[a][b] = 1;

		return 1;

	} else {

		m[a][b] = (m[a-1][b-1] != -1)? m[a-1][b-1] : combinatorio(m,a-1,b-1);

		m[a][b] += (m[a-1][b] != -1)? m[a-1][b] : combinatorio(m,a-1,b);

		return m[a][b];

	}

}

bool resuelveCaso() {

	int a, b;
	std::cin >> a >> b;

	if(!std::cin)

		return false;

	matrix m(a+1,row(b+1,-1));

	std::cout << combinatorio(m,a,b) << std::endl;

	return true;

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	while(resuelveCaso());

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
