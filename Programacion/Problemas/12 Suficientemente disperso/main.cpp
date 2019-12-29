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
 * 			c 				Si (left+1==right) v (left==right)
 *
 * 			2 * T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

bool resolver(const std::vector<int>& data, const int& difference, const int& left, const int& right) {

	if(left==right)

		return true;

	else if(left+1==right) {

		return (std::max(data[left],data[right]) - std::min(data[left],data[right])) >= difference;

	} else {

		int middle = (right + left) / 2;

		bool l = resolver(data,difference,left,middle);
		bool r = resolver(data,difference,middle+1,right);

		return l && r && ((std::max(data[left],data[right]) - std::min(data[left],data[right])) >= difference);

	}

}

bool resuelveCaso() {

	int size;
	int difference;

	std::cin >> size >> difference;

	if(!std::cin)

		return false;

	std::vector<int> data(size);

	for(int& i : data)

		std::cin >> i;

	std::cout << ((resolver(data,difference,0,data.size()-1))? "SI" : "NO") << std::endl;

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
