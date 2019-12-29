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
 * 			c 			Si esSolucion()
 *
 * 			T(n-1) * n 	En el peor de los otros casos.
 *
 * 		}
 *
 */

using iTupla = std::vector<int>;

using iMatriz = std::vector<iTupla>;

using sTupla = std::vector<std::string>;

struct nodo {
	const int& k;
	iTupla& solucion;
	sTupla& tipoJuguete;
	int& totalSoluciones;
	iTupla& disponiblesJuguete;
	const int& minimaSatisfaccion;
	iTupla& satisfaccionChiquillo;
	iMatriz& satisfaccionChiquilloJuguete;
};

bool esValida(struct nodo& n) {

	// Si el niño recive dos juguetes del mismo tipo.
	if(n.k % 2 == 1 && n.tipoJuguete[n.solucion[n.k-1]].compare(n.tipoJuguete[n.solucion[n.k]]) == 0)

		return false;

	// Si ya habíamos seleccionado todos los jugetes de ese tipo.
	if(n.disponiblesJuguete[n.solucion[n.k]] == -1)

		return false;

	// Si el chiquillo actual no es satisfecho con los regalos asignados.
	if(n.k % 2 == 1 && n.satisfaccionChiquillo[n.k/2] < n.minimaSatisfaccion)

		return false;

	/*

		El identificador del primer juguete debe ser estrictamente menor que el
		del segundo, si no puede haber repeticiones del tipo:

		Seleccionar (0,1) es igual que seleccionar (1,0)
		Seleccionar (0,2) es igual que seleccionar (2,0)
		Seleccionar (1,3) es igual que seleccionar (3,1)

		Si los identificadores son iguales entonces los juguetes son del mismo tipo
		y ya tenemos otra poda que lo controla.

	*/
	if(n.k % 2 == 1 && n.solucion[n.k-1] > n.solucion[n.k])

		return false;

	return true;

}

void tratarSolucion(struct nodo& n) {

	++n.totalSoluciones;

	for(int& i : n.solucion)

		std::cout << i << " ";

	std::cout << std::endl;

}

void resolver(struct nodo& n) {

	for(int juguete = 0 ; juguete < n.disponiblesJuguete.size() ; ++juguete) {

		--n.disponiblesJuguete[juguete];

		n.solucion[n.k] = juguete;

		n.satisfaccionChiquillo[n.k/2] += n.satisfaccionChiquilloJuguete[n.k/2][juguete];

		if(esValida(n)) {

			if(n.solucion.size() - 1 == n.k) { // esSolucion

				tratarSolucion(n);

			} else {

				nodo siguiente = {
					n.k + 1 ,
					n.solucion ,
					n.tipoJuguete ,
					n.totalSoluciones ,
					n.disponiblesJuguete ,
					n.minimaSatisfaccion ,
					n.satisfaccionChiquillo ,
					n.satisfaccionChiquilloJuguete
				};

				resolver(siguiente);

			}

		}

		++n.disponiblesJuguete[juguete];

		n.satisfaccionChiquillo[n.k/2] -= n.satisfaccionChiquilloJuguete[n.k/2][juguete];

	}

}

bool resuelveCaso() {

	int numeroDeChiquillos;
	int juguetesDiferentes;
	int minimaSatisfaccion;

	std::cin >> juguetesDiferentes >> numeroDeChiquillos >> minimaSatisfaccion;

	if(!std::cin)

		return false;

	int totalSoluciones = 0;

	iTupla disponiblesJuguete(juguetesDiferentes);

	for(int& i : disponiblesJuguete)

		std::cin >> i;

	sTupla tipoJuguete(juguetesDiferentes);

	for(std::string& i : tipoJuguete)

		std::cin >> i;

	iMatriz satisfaccionChiquilloJuguete(numeroDeChiquillos,iTupla(juguetesDiferentes));

	for(iTupla& c : satisfaccionChiquilloJuguete)

		for(int& j : c)

			std::cin >> j;

	iTupla solucion(2 * numeroDeChiquillos);

	iTupla satisfaccionChiquillo(numeroDeChiquillos);

	nodo primero = {
		0 ,
		solucion ,
		tipoJuguete ,
		totalSoluciones ,
		disponiblesJuguete ,
		minimaSatisfaccion ,
		satisfaccionChiquillo ,
		satisfaccionChiquilloJuguete
	};

	resolver(primero);

	if(totalSoluciones == 0)

		std::cout << "SIN SOLUCION" << std::endl;

	std::cout << std::endl;

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
