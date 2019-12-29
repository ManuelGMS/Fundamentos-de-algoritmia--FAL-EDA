#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(n * log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			    Si (s.cLeft == s.cRight) v (s.fLeft == s.fRight) v (s.fLeft+1 == s.fRight)
 *
 * 			2 * T(n/2) + n 	En cualquier otro caso.
 *
 * 		}
 *
 */

using iV = std::vector<int>;

struct solution {
	iV spaceShips;
	int changes;
};

solution resolver(const iV& spaceShips, const int& left, const int& right) {

	if(left==right)

		return { { spaceShips[left] } , 0 };

	else if(left+1==right)

		if(spaceShips[left] < spaceShips[right])

			return { { spaceShips[left] , spaceShips[right] } , 0 };

		else

			return { { spaceShips[right] , spaceShips[left] } , 1 };

	else {

		int changes = 0;

		int i = 0, j = 0;

		int middle = (left+right) / 2;

		solution l = resolver(spaceShips,left,middle);

		solution r = resolver(spaceShips,middle+1,right);

		iV reordererSpaceShips(l.spaceShips.size()+r.spaceShips.size());

		while(i < l.spaceShips.size() || j < r.spaceShips.size()) {

			if(i < l.spaceShips.size() && j < r.spaceShips.size())

				if(l.spaceShips[i] < r.spaceShips[j])

					reordererSpaceShips[i + j] = l.spaceShips[i++];

				else {

					changes += (l.spaceShips.size() - i);

					reordererSpaceShips[i + j] = r.spaceShips[j++];

				}

			else if(i < l.spaceShips.size())

				reordererSpaceShips[i + j] = l.spaceShips[i++];

			else

				reordererSpaceShips[i + j] = r.spaceShips[j++];

		}

		return { reordererSpaceShips , l.changes + r.changes + changes };

	}

}

bool resuelveCaso() {

	int size;
	std::cin >> size;

	if(!std::cin)

		return false;

	iV spaceShips(size);

	for(int& i : spaceShips)

		std::cin >> i;

	std::cout << resolver(spaceShips,0,spaceShips.size()-1).changes << std::endl;

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
