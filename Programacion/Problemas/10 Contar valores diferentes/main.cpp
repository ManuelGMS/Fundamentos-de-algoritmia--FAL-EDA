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
 * 			c 				Si (left+1==right) v (left==right) v (data[left]==data[right])
 *
 * 			2 * T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

int resolver(const std::vector<int>& data, const int& left, const int& right) {

	if( (left+1==right) || (left==right) || (data[left]==data[right]) ) {

		if(data[left]==data[right] || left == right)

			return 1;

		else

			return (data[left] == data[right])? 1 : 2;

	} else {

		int middle = (right+left) / 2;

		return resolver(data,left,middle) + resolver(data,middle+1,right) - (data[middle] == data[middle+1]);

	}

}

bool resuelveCaso() {

	int size;

	std::cin >> size;

	if(size == 0)

		return false;

	std::vector<int> data(size);

	for(int& i : data)

		std::cin >> i;

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
