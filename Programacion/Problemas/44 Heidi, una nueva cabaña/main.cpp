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

void resolver(const iVector& datos, const int& valoresIguales) {

	int longitud = 0;
	int totalLlanos = 0;
	iVector posicionLlano;
	int longitudMaxima = 0;
	int maximo = datos[datos.size()-1];

	// Recorrido lineal O(n)
	for(int i = datos.size() - 1 ; i > -1  ; --i) {

		if(datos[i] >= maximo) {

			if(datos[i] > maximo) {

				longitud = 1;
				maximo = datos[i];

			} else {

				++longitud;

				if(longitud >= valoresIguales) {

					if(longitud == valoresIguales) {

						++totalLlanos;

						posicionLlano.push_back(i+(longitud-1));

					}

					if(longitud > longitudMaxima)

						longitudMaxima = longitud;

				}

			}

		} else {

			longitud = 0;

		}

	}

	std::cout << longitudMaxima << " " << totalLlanos << " ";

	for(int& i : posicionLlano)

		std::cout << i << " ";

	std::cout << std::endl;

}

bool resuelveCaso() {

	int elementos, valoresIguales;
	std::cin >> elementos >> valoresIguales;

	if(!std::cin)

		return false;

	iVector datos(elementos);

	for(int& e : datos)

		std::cin >> e;

	resolver(datos,valoresIguales);

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
