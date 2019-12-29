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
 * 			c 				(left+1==right)
 *
 * 			2 * T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

using players = std::vector<std::string>;

struct solution {
	int round;
	int totalMatches;
	bool somebodyCame;
};

solution resolver(const players& p, const int& rounds, const int& left, const int& right) {

	if(left+1==right)

		return {
			1 ,
			p[left].compare("NP") != 0 && p[right].compare("NP") != 0 ,
			p[left].compare("NP") != 0 || p[right].compare("NP") != 0
		};

	else {

		int middle = (left+right) / 2;

		solution leftMatch = resolver(p,rounds,left,middle);

		solution rightMatch = resolver(p,rounds,middle+1,right);

		if(leftMatch.round + 1 <= rounds)

			return {
				leftMatch.round + 1 ,
				leftMatch.totalMatches + rightMatch.totalMatches +
				(leftMatch.somebodyCame && rightMatch.somebodyCame) ,
				leftMatch.somebodyCame || rightMatch.somebodyCame
			};

		else

			return {
				leftMatch.round + 1 ,
				leftMatch.totalMatches + rightMatch.totalMatches ,
				leftMatch.somebodyCame || rightMatch.somebodyCame
			};

	}

}

bool resuelveCaso() {

	int size, rounds;
	std::cin >> size >> rounds;

	if(!std::cin)

		return false;

	players p(size);

	for(std::string& s : p)

		std::cin >> s;

	std::cout << resolver(p,rounds,0,p.size()-1).totalMatches << std::endl;

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
