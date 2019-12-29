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

void resolver(const iVector& goles) {

	int inicio = -1;
	int finalMejor = 0;
	int inicioMejor = 0;
	int ultimoPartidoRacha = 0;
	int vecesIntervaloMejor = 0;

	for(int partido = 0 ; partido < goles.size() ; ++partido) {

		if(goles[partido] > 0) {

			if(partido - inicio >= finalMejor - inicioMejor) {

				if(partido - inicio > finalMejor - inicioMejor) {

					finalMejor = partido;
					inicioMejor = inicio;
					vecesIntervaloMejor = 1;

				} else

					++vecesIntervaloMejor;

				ultimoPartidoRacha = partido + 1;

			}

		} else

			inicio = partido;

	}

	std::cout << (finalMejor-inicioMejor);
	std::cout << " ";
	std::cout << vecesIntervaloMejor;
	std::cout << " ";
	std::cout << (goles.size()-ultimoPartidoRacha) << std::endl;

}

bool resuelveCaso() {

	int partidos;
	std::cin >> partidos;

	if(!std::cin)

		return false;

	iVector goles(partidos);

	for(int& g : goles)

		std::cin >> g;

	resolver(goles);

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
