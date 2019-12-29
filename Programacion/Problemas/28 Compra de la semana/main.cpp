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

using iTupla = std::vector<int>;

using iMatriz = std::vector<iTupla>;

const int MAS_INFINITO = std::numeric_limits<int>::max();

struct nodo {
	const int& k;
	int& solucionMejor;
	int& solucionActual;
	iTupla& comprasEnSupermercado;
	const iTupla& minimosAcumulados;
	const iMatriz& supermercadoPrecio;
};

void resolver(struct nodo& n) {

	for(int supermercado = 0 ; supermercado < n.supermercadoPrecio.size() ; ++supermercado) {

		++n.comprasEnSupermercado[supermercado];

		n.solucionActual += n.supermercadoPrecio[supermercado][n.k];

		if(n.comprasEnSupermercado[supermercado] <= 3) { // esValida()

			if(n.k == n.supermercadoPrecio[0].size() - 1) { // esSolucion()

				if(n.solucionActual < n.solucionMejor) { // esSolucionMejor()

					n.solucionMejor = n.solucionActual;

				}

			} else {

				if(n.solucionActual + n.minimosAcumulados[n.k+1] < n.solucionMejor) { // esSolucionPrometedora()

					nodo siguiente = { n.k + 1 , n.solucionMejor , n.solucionActual , n.comprasEnSupermercado , n.minimosAcumulados , n.supermercadoPrecio };

					resolver(siguiente);

				}

			}

		}

		--n.comprasEnSupermercado[supermercado];

		n.solucionActual -= n.supermercadoPrecio[supermercado][n.k];

	}

}

void resuelveCaso() {

	int supermercados, productos;
	std::cin >> supermercados >> productos;

	int solucionActual = 0;
	int solucionMejor = MAS_INFINITO;
	iTupla comprasEnSupermercado(supermercados);
	iTupla minimosAcumulados(productos,MAS_INFINITO);
	iMatriz supermercadoPrecio(supermercados,iTupla(productos));

	for(int i = 0 ; i < supermercados ; ++i)

		for(int j = 0 ; j < productos ; ++j) {

			std::cin >> supermercadoPrecio[i][j];

			if(j > 0)

				minimosAcumulados[j] = std::min(minimosAcumulados[j],supermercadoPrecio[i][j]);

		}

	for(int i = productos - 2 ; i > -1 ; --i)

		minimosAcumulados[i] += minimosAcumulados[i+1];

	nodo primero = { 0 , solucionMejor , solucionActual , comprasEnSupermercado , minimosAcumulados , supermercadoPrecio };

	resolver(primero);

	if(solucionMejor == MAS_INFINITO)

		std::cout << "Sin solucion factible" << std::endl;

	else

		std::cout << solucionMejor << std::endl;

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
