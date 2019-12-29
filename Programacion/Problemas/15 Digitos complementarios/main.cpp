#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 					Si (left+1==right) v (left==right)
 *
 * 			T(n/10) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

struct solution {
	long int number;
	long int tenPower;
};

solution resolver(const long int& number, const long int& tenPower) {

	if(number < 10)

		return { (9 - number) * tenPower , tenPower };

	else {

		solution s = resolver( number / 10 , tenPower * 10 );

		return { s.number + tenPower * (9 - (number % 10)) , s.tenPower };

	}

}

solution resolver(const long int& number) {

	if(number < 10)

		return { number , 1 };

	else {

		solution s = resolver( number / 10 );

		return { (number % 10) * ( s.tenPower * 10 ) + s.number , s.tenPower * 10 };

	}

}

void resuelveCaso() {

	long int number;
	std::cin >> number;

	solution complementary = resolver(number,1);

	solution complementaryReverse = resolver(complementary.number);

	std::cout << complementary.number << " " << complementaryReverse.number * (complementary.tenPower / complementaryReverse.tenPower) << std::endl;

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
