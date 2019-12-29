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

void resolver(const iVector& tren, const int& vagonesConsecutivos) {

	int botin = 0;
	int botinMejor = 0;
	int vagonMejor = 0;

	// Recorrido O(n)
	for (int vagon = 0 ; vagon < tren.size() ; ++vagon) {

		botin += tren[vagon];

		// Restamos el vagon que sale del rango consecutivo valido.
		if(vagon >= vagonesConsecutivos)

			botin -= tren[vagon-vagonesConsecutivos];

		// El mejor botin puede conseguirse con distintas secuencias de vagones.
		if(botin >= botinMejor) {

			botinMejor = botin;

			vagonMejor = vagon - (vagonesConsecutivos - 1);

		}

	}

	std::cout << vagonMejor << " " << botinMejor << std::endl;

}

void resuelveCaso() {

	int vagones, vagonesConsecutivos;
	std::cin >> vagones >> vagonesConsecutivos;

	iVector tren(vagones);

	for(int& vagon : tren)

		std::cin >> vagon;

	resolver(tren,vagonesConsecutivos);

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int casos;
	std::cin >> casos;

	for( ; casos > 0 ; --casos)

		resuelveCaso();

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
