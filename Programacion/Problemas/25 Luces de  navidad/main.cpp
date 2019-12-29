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

struct informacion {
	int consumoMaximo;
	int longitudCable;
	int coloresDiferentes;
	std::vector<int> consumoBombilla;
};

struct nodo {
	const int& k;
	int& totalConsumido;
	int& totalSoluciones;
	std::vector<int>& vecesUsada;
	std::vector<int>& tiraDeLuces;
	const struct informacion& informacion;
};

bool esValida(struct nodo& n) {

	// La ficha seleccionada no puede ser igual que las dos anteriores.
	if(n.k > 1 && n.tiraDeLuces[n.k-1] == n.tiraDeLuces[n.k] && n.tiraDeLuces[n.k-2] == n.tiraDeLuces[n.k])

		return false;

	// La suma de las luces de un color (todos) no puede superar en mas de una unidad la suma de las luces del resto de colores.

	// O(n)

	bool okey = true;

	for(int i = 0 ; i < n.vecesUsada.size() && okey ; ++i)

		if(n.vecesUsada[i] - ((n.k+1)-n.vecesUsada[i]) > 1)

			okey = false;

	if(!okey)

		return false;

	// Si las luces escogidas para la tira superan el maximo consumo permitido.
	if(n.totalConsumido > n.informacion.consumoMaximo)

		return false;

	return true;

}

void tratarSolucion(struct nodo& n) {

	/*
	for(int& i : n.tiraDeLuces)

		std::cout << i << " ";

	std::cout << std::endl;
	*/

	++n.totalSoluciones;

}

bool esSolucionPrometedora(struct nodo& n) {

	// if(n.totalConsumido + menor * (n.solucion. - (n.k+1)) > n.informacion.consumoMaximo)

		// return false;

	return true;

}

void resolver(struct nodo& n) {

	for(int color = 0 ; color < n.informacion.coloresDiferentes ; ++color) {

		n.tiraDeLuces[n.k] = color;

		++n.vecesUsada[color];

		n.totalConsumido += n.informacion.consumoBombilla[color];

		if(esValida(n)) {

			if(n.informacion.longitudCable - 1 == n.k) // esSolucion()

				tratarSolucion(n);

			else {

				nodo siguiente = { n.k+1 , n.totalConsumido , n.totalSoluciones , n.vecesUsada , n.tiraDeLuces , n.informacion };

				// if(esSolucionPrometedora(n))

				resolver(siguiente);

			}

		}

		--n.vecesUsada[color];

		n.totalConsumido -= n.informacion.consumoBombilla[color];

	}

}

bool resuelveCaso() {

	informacion informacion;

	std::cin >> informacion.longitudCable >> informacion.coloresDiferentes >> informacion.consumoMaximo;

	if(!std::cin)

		return false;

	int totalConsumido = 0;

	int totalSoluciones = 0;

	std::vector<int> tiraDeLuces(informacion.longitudCable);

	std::vector<int> vecesUsada(informacion.coloresDiferentes);

	std::vector<int> consumoBombilla(informacion.coloresDiferentes);

	for(int& i : consumoBombilla)

		std::cin >> i;

	nodo primero = { 0 , totalConsumido , totalSoluciones , vecesUsada , tiraDeLuces , { informacion.consumoMaximo , informacion.longitudCable , informacion.coloresDiferentes , consumoBombilla } };

	resolver(primero);

	std::cout << primero.totalSoluciones << std::endl;

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
