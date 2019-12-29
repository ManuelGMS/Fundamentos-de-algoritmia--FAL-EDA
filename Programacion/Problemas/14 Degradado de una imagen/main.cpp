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
 * 			c 					Si (left+1==right) v (left==right)
 *
 * 			2 * T(n/2) + 2c 	En cualquier otro caso.
 *
 * 		}
 *
 */

struct solution {
	bool okey;
	int totally;
};

using tuple = std::vector<int>;

using matrix = std::vector<tuple>;

solution resolver(const tuple& data, const int& left, const int& right) {

	if(left==right)

		return { true , data[left] };

	else if(left+1==right)

		return { data[left] < data[right] , data[left] + data[right] };

	else {

		int middle = (right+left) / 2;

		solution l = resolver(data,left,middle);

		solution r = resolver(data,middle+1,right);

		return {
			l.okey && r.okey && l.totally < r.totally,
			l.totally + r.totally
		};

	}

}

bool resuelveCaso() {

	int rows, columns;

	std::cin >> rows >> columns;

	if(!std::cin)

		return false;

	bool isDegraded = true;

	matrix m(rows,tuple(columns));

	for(tuple& t : m)

		for(int& v : t)

			std::cin >> v;

	for(int i = 0 ; i < m.size() && isDegraded ; ++i)

		isDegraded = resolver(m[i],0,m[i].size()-1).okey;

	std::cout << ((isDegraded)? "SI" : "NO") << std::endl;

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
