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

	int unos = 0;
	int ceros = 0;
	int posicion = -1;

	// Recorrido lineal O(n)
	for(int i = 0 ; i < datos.size(); ++i) {

		if(datos[i] == 0)

			++ceros;

		else if(datos[i] == 1)

			++unos;

		if(ceros == unos)

			posicion = i;

	}

	return posicion;

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
