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
 * 			c 			Si (left+1=right) v (left=right)
 *
 * 			T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

int resolver(const std::vector<int>& data, const int& left, const int& right, const int& song) {

	if( (left+1==right) || (left==right) ) {

		if(std::abs(data[left] - left - song) == 0)

			return data[left];

		else if(std::abs(data[right] - right - song) == 0)

			return data[right];

		else

			return -1;

	} else {

		int middle = (right+left) / 2;

		int evaluateLeft = std::abs(data[middle-1] - (middle-1) - song);

		int evaluateRight = std::abs(data[middle+1] - (middle+1) - song);

		if(evaluateLeft < evaluateRight)

			return resolver(data,left,middle,song);

		else

			return resolver(data,middle,right,song);

	}

}

void resuelveCaso() {

	int size;
	int song;

	std::cin >> size >> song;

	std::vector<int> data(size);

	for(int& i : data)

		std::cin >> i;

	int solution = resolver(data,0,data.size()-1,song);

	if(solution == -1)

		std::cout << "NO";

	else

		std::cout << solution;

	std::cout << std::endl;

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
