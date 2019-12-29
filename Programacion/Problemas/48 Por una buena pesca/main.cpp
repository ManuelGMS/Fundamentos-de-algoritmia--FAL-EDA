#include <vector>
#include <fstream>
#include <iostream>

/*
 * E24: Manuel Guerrero Moñús.
 *
 * Complejiad:
 *
 * 		O(4n) --> En tiempo.
 * 		O(2n) --> En espacio.
 *
 * Nota:
 *
 * 		La matriz final contiene las sumas de todas las areas posibles de P x P elementos.
 *
 */

using iVector = std::vector<int>;

using matrix = std::vector<iVector>;

void resolver(matrix& matriz, const int& p) {

	matrix auxiliar = matriz;
	int maximo = matriz[0][0];

	//********************************************************************

	for(int columna = 0 ; columna < matriz[0].size() ; ++columna)

		for(int fila = 1 ; fila < p ; ++fila)

			auxiliar[fila][columna] += auxiliar[fila-1][columna];

	for(int columna = 0 ; columna < matriz[0].size() ; ++columna)

		for(int fila = p ; fila < matriz.size() ; ++fila) {

			auxiliar[fila][columna] -= matriz[fila-p][columna];

			auxiliar[fila][columna] += auxiliar[fila-1][columna];

		}

	//********************************************************************

	matriz = auxiliar;

	//********************************************************************

	for(int fila = p - 1 ; fila < matriz.size() ; ++fila)

		for(int columna = 1 ; columna < p ; ++columna) {

			matriz[fila][columna] += matriz[fila][columna-1];

			if(matriz[fila][columna] > maximo)

				maximo = matriz[fila][columna];

		}

	for(int fila = p - 1 ; fila < matriz.size() ; ++fila)

		for(int columna = p ; columna < matriz[0].size() ; ++columna) {

			matriz[fila][columna] -= auxiliar[fila][columna-p];

			matriz[fila][columna] += matriz[fila][columna-1];

			if(matriz[fila][columna] > maximo)

				maximo = matriz[fila][columna];

		}

	//********************************************************************

	std::cout << maximo << std::endl;

}

bool resuelveCaso() {

	int p, dimension;
	std::cin >> dimension >> p;

	if(!std::cin)

		return false;

	matrix matriz(dimension,iVector(dimension));

	for(iVector& v : matriz)

		for(int& e : v)

			std::cin >> e;

	resolver(matriz, p);

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
