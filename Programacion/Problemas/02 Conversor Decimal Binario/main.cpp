#include <fstream>
#include <iostream>

/*
 * Complejidad: O(log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si (number < 2)
 *
 * 			T(n) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

std::string resolver(const int& number) {

	if(number < 2)

		return (number == 1)? "1" : "0";

	else

		return resolver(number/2) + char('0'+(number%2));

}

bool resuelveCaso() {

	int number;
	std::cin >> number;

	if(!std::cin)

		return false;

	std::cout << resolver(number) << std::endl;

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
