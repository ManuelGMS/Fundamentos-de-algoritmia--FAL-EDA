#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(n)
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si (n == 0)
 *
 * 			T(n-1) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using ulli = unsigned long long int;

ulli fibonacci(const ulli& n, const ulli& a, const ulli& b) {

	return (n == 0)? b : fibonacci(n-1,b,a+b);

}

bool resuelveCaso() {

	int n;
	std::cin >> n;

	if(!std::cin)

		return false;

	if(n == 0)

		std::cout << "0" << std::endl;

	else if(n == 1)

		std::cout << "1" << std::endl;

	else

		std::cout << fibonacci(n-1,0,1) << std::endl;

	return true;

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	while(resuelveCaso());

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);		// getchar();
	#endif

	return 0;

}
