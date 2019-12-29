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
 * 			c 				Si (left==right) v (left+1==right)
 *
 * 			2 * T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using row = std::vector<int>;

int resolver(const row& v, const int& left, const int& right) {

	if(left==right)

		return (v[left] % 2 == 0);

	else if(left+1==right)

		return (v[left] % 2 == 0) + (v[right] % 2 == 0);

	else {

		int middle = (right+left) / 2;

		int l = resolver(v,left,middle);

		int r = resolver(v,middle+1,right);

		return ( l != -1 && r != -1 && std::abs(l-r) <= 2 )? (l+r) : -1 ;

	}

}

bool resuelveCaso() {

	int size;
	std::cin >> size;

	if(size == 0)

		return false;

	row v(size);

	for(int& i : v)

		std::cin >> i;

	std::cout << ( (resolver(v,0,v.size()-1) != -1)? "SI" : "NO" ) << std::endl;

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
