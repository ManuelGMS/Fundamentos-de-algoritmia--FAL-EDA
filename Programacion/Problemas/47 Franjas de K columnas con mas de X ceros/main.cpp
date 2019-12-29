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

void contarCerosYcomprobarColumna(const matrix& matriz, const int& columna, const int& ceros, iVector& contadorDeColumna, int& columnasCorrectasEnFranja) {

	for(int fila = 0 ; fila < matriz.size() ; ++fila)

		if(matriz[fila][columna] == 0)

			++contadorDeColumna[columna];

		if(contadorDeColumna[columna] >= ceros)

			++columnasCorrectasEnFranja;

}

void comprobarLaFranja(const int& columnasCorrectasEnFranja, const int& numeroColumnas, int& totalFranjas) {

	if(columnasCorrectasEnFranja >= numeroColumnas)

		++totalFranjas;

}

void resolver(const matrix& matriz, const int& franja, const int& numeroColumnas, const int& ceros) {

	// Recorrido lineal O(n)

	int columna;
	int totalFranjas = 0;
	int columnasCorrectasEnFranja = 0;
	iVector contadorDeColumna(matriz[0].size());

	for(columna = 0 ; columna < franja ; ++columna)

		contarCerosYcomprobarColumna(matriz,columna,ceros,contadorDeColumna,columnasCorrectasEnFranja);

	comprobarLaFranja(columnasCorrectasEnFranja,numeroColumnas,totalFranjas);

	for(; columna < matriz[0].size() ; ++columna) {

		if(contadorDeColumna[columna-franja] >= ceros)

			--columnasCorrectasEnFranja;

		contarCerosYcomprobarColumna(matriz,columna,ceros,contadorDeColumna,columnasCorrectasEnFranja);

		comprobarLaFranja(columnasCorrectasEnFranja,numeroColumnas,totalFranjas);

	}

	std::cout << totalFranjas << std::endl;

}

bool resuelveCaso() {

	int filas, columnas, franja, numeroColumnas, ceros;
	std::cin >> filas >> columnas >> franja >> numeroColumnas >> ceros;

	if(!std::cin)

		return false;

	matrix matriz(filas,iVector(columnas));

	for(iVector& v : matriz)

		for(int& e : v)

			std::cin >> e;

	resolver(matriz, franja, numeroColumnas, ceros);

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
