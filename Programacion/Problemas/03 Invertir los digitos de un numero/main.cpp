#include <fstream>
#include <iostream>

/*
 * Complejidad: O(log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si (number < 10)
 *
 * 			T(n) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

struct sol {
	int numero;
	int pot;
};

sol resolver(const int& n) {

	if(n < 10)

		return { n , 10 };

	else {

		sol s = resolver(n/10);

		return { s.numero + (n % 10) * s.pot , s.pot * 10 };

	}

}

bool resuelveCaso() {

	int number;
	std::cin >> number;

	if(!std::cin)

		return false;

	std::cout << resolver(number).numero << std::endl;

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
