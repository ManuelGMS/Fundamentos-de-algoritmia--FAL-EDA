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

void resolver(const iVector& edificios, const int& alturaNave) {

	int final = 0;
	int inicio = 0;
	int finalMejor = -1;
	int inicioMejor = 0;

	// Recorrido O(n)
	for(int edificio = 0 ; edificio < edificios.size() ; ++edificio) {

		if(alturaNave < edificios[edificio]) {

			if(inicio == -1) {

				final = edificio;
				inicio = edificio;

			} else {

				final = edificio;

			}

			if(final - inicio > finalMejor - inicioMejor) {

				finalMejor = final;
				inicioMejor = inicio;

			}

		} else {

			final = -1;
			inicio = -1;

		}

	}

	std::cout << inicioMejor << " " << finalMejor << std::endl;

}

void resuelveCaso() {

	int edificios, alturaNave;
	std::cin >> edificios >> alturaNave;

	iVector edificio(edificios);

	for(int& e : edificio)

		std::cin >> e;

	resolver(edificio,alturaNave);

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
