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
 * 			c 			Si (s.cLeft == s.cRight) v (s.fLeft == s.fRight) v (s.fLeft+1 == s.fRight)
 *
 * 			T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using iV = std::vector<int>;

using iP = std::pair<int,int>;

struct state {
	iV complete;
	iV fault;
	int cLeft;
	int cRight;
	int fLeft;
	int fRight;
};

int resolver(const state& s) {

	if(s.cLeft == s.cRight) {

		return s.complete[s.cLeft];

	} else if(s.fLeft == s.fRight) {

		if(s.fault[s.fLeft] == s.complete[s.cLeft])

			return s.complete[s.cRight];

		else

			return s.complete[s.cLeft];

	} else if(s.fLeft+1 == s.fRight) {

		if(s.complete[s.cLeft] != s.fault[s.fLeft])

			return s.complete[s.cLeft];

		else if(s.complete[s.cRight] != s.fault[s.fRight])

			return s.complete[s.cRight];

		else

			return s.complete[s.cLeft+1];

	} else {

		int cMiddle = (s.cLeft+s.cRight) / 2;

		if(s.fault[cMiddle] == s.complete[cMiddle])

			return resolver({s.complete,s.fault,cMiddle,s.cRight,cMiddle,s.fRight});

		else

			return resolver({s.complete,s.fault,s.cLeft,cMiddle,s.fLeft,cMiddle});

	}

}

void resuelveCaso() {

	int size;
	std::cin >> size;

	iV complete(size), fault(size-1);

	for(int& i : complete)

		std::cin >> i;

	for(int& i : fault)

		std::cin >> i;

	std::cout << resolver({complete,fault,0,complete.size()-1,0,fault.size()-1}) << std::endl;

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
