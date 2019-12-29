#include <algorithm>
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

void resolver(iVector& v) {

	int pares = 0;
	int posicionDeImpar = -1;

	// Recorrido en O(n)
	for(int i = 0 ; i < v.size() ; ++i) {

		pares += (v[i] % 2 == 0);

		if(v[i] % 2 == 1 && posicionDeImpar == -1)

			posicionDeImpar = i;

		if(posicionDeImpar != -1 && v[i] % 2 == 0) {

			std::swap(v[posicionDeImpar],v[i]); // O(3c) --> CTE

			++posicionDeImpar;

		}

	}

	v.resize(pares); // O(Impares) --> O(n)

}

void resuelveCaso() {

	int elementos;
	std::cin >> elementos;
	iVector numeros(elementos);

	for(int& i : numeros)

		std::cin >> i;

	resolver(numeros);

	for(int& i : numeros)

		std::cout << i << " ";

	std::cout << std::endl;

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
