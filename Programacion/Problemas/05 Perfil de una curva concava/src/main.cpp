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
 * 			c 			Si ( (left+1=right) v (left=right) )
 *
 * 			T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

int resolver(const std::vector<int>& data, const int& left, const int& right) {

	if( (left+1==right) || (left==right) )

			return std::min(data[left],data[right]);

	else {

		int middle = (right+left) / 2;

		if(data[middle-1] < data[middle])

			return resolver(data,0,middle);

		else

			return resolver(data,middle,right);

	}

}

bool resuelveCaso() {

	int size;
	std::cin >> size;

	if(!std::cin)

		return false;

	std::vector<int> data(size);

	for( ; size > 0 ; --size)

		std::cin >> data[data.size()-size];

	std::cout << resolver(data,0,data.size()-1) << std::endl;

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
