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

using ulli = unsigned long long int;

ulli resolver(const ulli& number) {

	if(number < 10)

		return ( number % 2 != 0 )? number : 0;

	else {

		ulli result = resolver(number/10);

		return ( ((number % 10) % 2) != 0 )? (result * 10 + (number % 10)) : result;

	}

}

bool resuelveCaso() {

	ulli number;
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

	while(resuelveCaso());

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
