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

int resolver(const iVector& datos) {

	int veces = 0;
	int sumatoria = 0;
	int maximo = datos[0];

	// Recorrido lineal O(n)
	for(int i = 0 ; i < datos.size(); ++i) {

		if(datos[i] >= maximo) {

			if(datos[i] > maximo) {

				veces = 1;

				maximo = datos[i];

			} else {

				++veces;

			}

		}

		sumatoria += datos[i];

	}

	return sumatoria - (maximo * veces);

}

void resuelveCaso() {

	int elementos;
	std::cin >> elementos;

	iVector datos(elementos);

	for(int& e : datos)

		std::cin >> e;

	std::cout << resolver(datos) << std::endl;

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
