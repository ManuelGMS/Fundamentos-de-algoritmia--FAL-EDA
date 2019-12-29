#include <limits>
#include <vector>
#include <fstream>
#include <iostream>

/*
 * E24: Manuel Guerrero Moñús.
 *
 * Complejiad: O(n).
 *
 */

using iVector = std::vector<int>;

enum piedrasPreciosas {diamante, rubi, esmeralda, zafiro, jade, piedrasPreciosasSize};

std::istream& operator >> (std::istream& entrada, piedrasPreciosas& p) {

	char num;
	entrada >>  num;

	switch (num) {
		case 'r': p = rubi; break;
		case 'j': p = jade; break;
		case 'z': p = zafiro; break;
		case 'd': p = diamante; break;
		case 'e': p = esmeralda; break;
	}

	return entrada;

}

void resolver(
		const std::vector<piedrasPreciosas>& secuenciaPiedras,
		const int& tamSecuencia, piedrasPreciosas tipo1,
		const int& numTipo1, piedrasPreciosas tipo2,
		const int& numTipo2
		) {

	int totalSecuencias = 0;
	std::vector<int> contadorDeTipo(piedrasPreciosasSize);

	// Recorrido O(n)

	for(int piedra = 0 ; piedra < tamSecuencia ; ++piedra)

		++contadorDeTipo[secuenciaPiedras[piedra]];

	if(contadorDeTipo[tipo1] >= numTipo1 && contadorDeTipo[tipo2] >= numTipo2)

		++totalSecuencias;

	for(int piedra = tamSecuencia ; piedra < secuenciaPiedras.size() ; ++piedra) {

		++contadorDeTipo[secuenciaPiedras[piedra]];

		--contadorDeTipo[secuenciaPiedras[piedra-tamSecuencia]];

		if(contadorDeTipo[tipo1] >= numTipo1 && contadorDeTipo[tipo2] >= numTipo2)

			++totalSecuencias;

	}

	std::cout << totalSecuencias << std::endl;

}

void resuelveCaso() {

	piedrasPreciosas tipo1, tipo2;
	int numPiedras, tamSecuencia, numTipo1, numTipo2;

	std::cin >> numPiedras >> tamSecuencia >> tipo1 >> numTipo1 >> tipo2 >> numTipo2;

	std::vector<piedrasPreciosas> secuenciaPiedras(numPiedras);

	for(piedrasPreciosas& p : secuenciaPiedras)

		std::cin >> p;

	resolver(secuenciaPiedras,tamSecuencia,tipo1,numTipo1,tipo2,numTipo2);

}

int main() {

	#ifndef DOMJUDGE
		std::ifstream in("EntradaEjemplo.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int casos;
	std::cin >> casos;

	for( ; casos > 0 ; --casos)

		resuelveCaso();

	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		// getchar();
	#endif

	return 0;

}
