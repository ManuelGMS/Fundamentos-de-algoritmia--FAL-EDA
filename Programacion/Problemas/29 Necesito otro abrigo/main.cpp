#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(n!)
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			esSolucion() ^ esSolucionValida()
 *
 * 			T(n-1) * n 	En el peor de los otros casos.
 *
 * 		}
 *
 */

using iVector = std::vector<int>;

struct nodo {
	const int& k;
	iVector& abrigoDia;
	iVector& abrigoUsado;
	int& abrigoMasUsado;
	int& totalSoluciones;
	const iVector& abrigoSoporta;
	const iVector& precipitacionDia;
};

bool esValida(struct nodo& n) {

	// Si el abrigo que  uso hoy es el mismo que el de ayer.
	if(n.k > 0 && n.abrigoDia[n.k-1] == n.abrigoDia[n.k])

		return false;

	// Si el abrigo no soporta la precipitacion de hoy.
	if(n.abrigoSoporta[n.abrigoDia[n.k]] < n.precipitacionDia[n.k])

		return false;

	// Si el abrigo mas usado supera en dos o mas a un tercio de los dias transcurridos.
	if(n.abrigoUsado[n.abrigoMasUsado] - (n.k/3) > 2)

		return false;

	return true;

}

void resolver(struct nodo& n) {

	int abrigoMasUsado = n.abrigoMasUsado;

	for(int abrigo = 0 ; abrigo < n.abrigoSoporta.size() ; ++abrigo) {

		n.abrigoDia[n.k] = abrigo;

		++n.abrigoUsado[abrigo];

		if(n.abrigoUsado[abrigo] > n.abrigoUsado[n.abrigoMasUsado])

			n.abrigoMasUsado = abrigo;

		if(esValida(n)) {

			if(n.k == n.precipitacionDia.size() - 1) { // esSolucion()

				if(n.abrigoDia[0] != n.abrigoDia[n.k]) // esSolucionValida()

					++n.totalSoluciones;

			} else {

				nodo siguiente = { n.k + 1 , n.abrigoDia , n.abrigoUsado , n.abrigoMasUsado , n.totalSoluciones , n.abrigoSoporta , n.precipitacionDia };

				resolver(siguiente);

			}

		}

		--n.abrigoUsado[abrigo];

		n.abrigoMasUsado = abrigoMasUsado;

	}

}

bool resuelveCaso() {

	int dias, abrigos;
	std::cin >> dias >> abrigos;

	if(dias == 0 && abrigos == 0)

		return false;

	iVector precipitacionDia(dias);

	for (int i = 0 ; i < dias; ++i)

		std::cin >> precipitacionDia[i];

	iVector abrigoSoporta(abrigos);

	for (int i = 0 ; i < abrigos; ++i)

		std::cin >> abrigoSoporta[i];

	iVector abrigoDia(dias);

	int abrigoMasUsado = 0;

	int totalSoluciones = 0;

	iVector abrigoUsado(abrigos);

	nodo primero = { 0 , abrigoDia , abrigoUsado , abrigoMasUsado , totalSoluciones , abrigoSoporta , precipitacionDia };

	resolver(primero);

	if(totalSoluciones == 0)

		std::cout << "Lo puedes comprar" << std::endl;

	else

		std::cout << totalSoluciones << std::endl;

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
