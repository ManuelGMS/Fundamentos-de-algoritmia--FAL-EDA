#include <fstream>
#include <iostream>

/*
 * Complejidad: O(log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si (b = 0) v (b = 1)
 *
 * 			T(n) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

size_t resolver(const size_t& a, const size_t& b) {

	switch(b) {

		case 0: return 0;

		case 1: return a;

		default: return resolver(2*a,b/2) + a * (b%2!=0);

	}

}

bool resuelveCaso() {

	size_t a, b;
	std::cin >> a >> b;

	if(!std::cin)

		return false;

	std::cout << resolver(a,b) << std::endl;

	return true;

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int cases;
	std::cin >> cases;

	for( ; cases > 0 ; --cases )

		resuelveCaso();

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
