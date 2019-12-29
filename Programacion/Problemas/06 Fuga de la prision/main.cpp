#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O( n * log(n) )
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si ( (left+1=right)
 *
 * 			T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

char resolver(const std::vector<char>& data, const int& left, const int& right) {

	if(left+1==right)

		return data[left] + 1;

	else {

		int middle = (right+left) / 2;

		if( (data[left] - left) != (data[middle] - middle) )

			return resolver(data,left,middle);

		else

			return resolver(data,middle,right);

	}

}

void resuelveCaso() {

	char last;
	char first;

	std::cin >> first >> last;

	std::vector<char> data(last-first);

	for(int i = 0 ; i < data.size() ; ++i)

		std::cin >> data[i];

	if(data[0] != first)

		std::cout << first << std::endl;

	else if(data[data.size()-1] != last)

		std::cout << last << std::endl;

	else

		std::cout << resolver(data,0,data.size()-1) << std::endl;

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int cases;
	std::cin >> cases;

	for( ; cases > 0 ; --cases)

		resuelveCaso();

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
