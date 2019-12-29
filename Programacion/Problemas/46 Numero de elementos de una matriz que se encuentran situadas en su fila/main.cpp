#include <vector>
#include <fstream>
#include <iostream>

/*
 * E24: Manuel Guerrero Moñús.
 *
 * Complejiad: O(n).
 *
 */

using iVector = std::vector<int>;

using matrix = std::vector<iVector>;

void resolver(const matrix& matriz) {

	int elementos = 0;

	// Recorrido lineal O(n)
	for(int fila = 0 ; fila < matriz.size() ; ++fila) {

		for(int columna = 0 ; columna < matriz[0].size() ; ++columna) {

			if(fila == matriz[fila][columna])

				++elementos;

		}

	}

	std::cout << elementos << std::endl;

}

bool resuelveCaso() {

	int filas, columnas;
	std::cin >> filas >> columnas;


	if(!std::cin)

		return false;

	matrix matriz(filas,iVector(columnas));

	for(iVector& v : matriz)

		for(int& e : v)

			std::cin >> e;

	resolver(matriz);

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
