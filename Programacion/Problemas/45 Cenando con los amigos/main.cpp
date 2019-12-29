#include <vector>
#include <fstream>
#include <iostream>

/*
 * E24: Manuel Guerrero Moñús.
 *
 * Complejiad: O(n).
 *
 */

using iPair = std::pair<int,int>;

using iVector = std::vector<int>;

void resolver(const iVector& datos) {

	int sumaMejor = 0;
	int sumaActual = 0;
	iPair intervaloMejor = { 0 , 0 };
	iPair intervaloActual = { 0 , 0 };

	// Recorrido lineal.
	for (int i = 0; i < datos.size(); ++i) {

		sumaActual += datos[i];

		if(sumaActual <= 0) {

			sumaActual = 0;

			intervaloActual.first = i + 1;

		} else {

			intervaloActual.second = i;

			if(sumaActual >= sumaMejor) {

				if(sumaActual > sumaMejor) {

					sumaMejor = sumaActual;

					intervaloMejor.second = i;

					intervaloMejor.first = intervaloActual.first;

				} else {

					if(intervaloActual.second - intervaloActual.first < intervaloMejor.second - intervaloMejor.first) {

						intervaloMejor.first = intervaloActual.first;

						intervaloMejor.second = intervaloActual.second;

					}

				}

			}

		}

	}

	std::cout << sumaMejor << " " << intervaloMejor.first << " " << ((intervaloMejor.second+1)-intervaloMejor.first) << std::endl;

}

bool resuelveCaso() {

	int elementos;
	std::cin >> elementos;


	if(!std::cin)

		return false;

	iVector datos(elementos);

	for(int& e : datos)

		std::cin >> e;

	resolver(datos);

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
