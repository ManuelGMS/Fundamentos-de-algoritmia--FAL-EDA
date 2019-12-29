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

const int MAS_INFINITO = std::numeric_limits<int>::max();

bool resolver(const iVector& v, const int& posicion) {

	// Cogemos un maximo posible del vector.
	int mayor = v[0];

	/*
		Si p es la ultima posicion del vector, habría que
		sacar el minimo de la nada (un conjunto vacio), el
		cual esta establecido como infinito.
	*/
	int menor = MAS_INFINITO;

	// Recorrido en O(n)
	for(int i = 0 ; i < v.size() ; ++i)

		if(i <= posicion)

			mayor = std::max(mayor,v[i]); // CTE

		else

			menor = std::min(menor,v[i]); // CTE

	return mayor < menor;

}

void resuelveCaso() {

	int elementos, posicion;
	std::cin >> elementos >> posicion;

	iVector numeros(elementos);

	for(int& i : numeros)

		std::cin >> i;

	std::cout << ((resolver(numeros,posicion))? "SI" : "NO") << std::endl;

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
