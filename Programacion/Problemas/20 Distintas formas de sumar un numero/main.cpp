#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(2^n)
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 				(i == v.size())
 *
 * 			2 * T(n-1) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using row = std::vector<int>;

using matrix = std::vector<row>;

/*
int sumas(const row& v, const int& number, const int& total, const int& i) {

	if(i == v.size())

		return 0;

	else

		return (total + v[i] == number) + sumas(v,number,total+v[i],i+1) + sumas(v,number,total,i+1);

}
*/

int sumas(matrix& m, const row& v, const int& number, const int& total, const int& i) {

	if(i == v.size() || total > number)

		return 0;

	else if(m[i][total] != -1)

		return m[i][total];

	else {

		m[i][total] = (total + v[i] == number) + sumas(m,v,number,total+v[i],i+1) + sumas(m,v,number,total,i+1);

		return m[i][total];

	}

}

bool resuelveCaso() {

	int size, number;
	std::cin >> size >> number;

	if(!std::cin)

		return false;

	row v(size);

	matrix m(size,row(number+1,-1));

	for(int& i : v)

		std::cin >> i;

	std::cout << sumas(m,v,number,0,0) << std::endl;

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
