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
 * 			c 			    (pi != 0 && pd != 0)
 *
 * 			2 * T(n/2) + c 	En el peor de los otros casos.
 *
 * 		}
 *
 */

bool estaBalanceado(int& peso) {

	int pi, di, pd, dd;
	std::cin >> pi >> di >> pd >> dd;

	if(pi != 0 && pd != 0) {

		peso = (pi + pd);

		return (pi * di == pd * dd);

	} else {

		int pesoDerecha = pd;
		int pesoIzquierda = pi;
		bool equilibrated = true;

		if(pi == 0) {

			equilibrated &= estaBalanceado(peso);

			pesoIzquierda = peso;

		}

		if(pd == 0) {

			equilibrated &= estaBalanceado(peso);

			pesoDerecha = peso;

		}

		peso = (pesoIzquierda + pesoDerecha);

		return equilibrated && (pesoIzquierda * di == pesoDerecha * dd);

	}

}

void resuelveCaso() {

	int peso = 0;

	std::cout << ( (estaBalanceado(peso))? "SI" : "NO" ) << std::endl;

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
