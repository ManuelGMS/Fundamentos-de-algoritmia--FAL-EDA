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
 * 			2 * T(n/2) + 2c 	En cualquier otro caso.
 *
 * 		}
 *
 */

struct solution {
	int min;
	int max;
	bool okey;
};

solution resolver(const std::vector<int>& data, const int& left, const int& right) {

	if(left==right)

		return { data[left] , data[left] , true };

	else if(left+1==right)

		return {
			std::min(data[left],data[right]) ,
			std::max(data[left],data[right]) ,
			data[right] >= data[left]
		};

	else {

		int middle = (right+left) / 2;

		solution l = resolver(data,left,middle);

		solution r = resolver(data,middle+1,right);

		return {
			std::min(l.min,r.min) ,
			std::max(l.max,r.max) ,
			l.okey && r.okey && r.max >= l.max && l.min <= r.min
		};

	}

}

bool resuelveCaso() {

	int read;

	std::cin >> read;

	if(read == 0)

		return false;

	std::vector<int> data;

	data.push_back(read);

	std::cin >> read;

	while(read != 0) {

		data.push_back(read);

		std::cin >> read;

	}

	std::cout << ((resolver(data,0,data.size()-1).okey)? "SI" : "NO") << std::endl;

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
