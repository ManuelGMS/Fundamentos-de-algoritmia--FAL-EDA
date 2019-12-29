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

enum color { azul , rojo , verde };

struct contadores {
	int rojasUsadas;
	int verdesUsadas;
	int azulesUsadas;
	int solucionesDiferentes;
};

struct informacion {
	int altura;
	int maxRojas;
	int maxVerdes;
	int maxAzules;
};

struct nodo {
	const int& k;
	struct contadores& contadores;
	std::vector<color>& construccion;
	const struct informacion& informacion;
};

bool esValida(struct nodo& n) {

	if(n.construccion[n.k] == verde && n.construccion[n.k-1] == verde) // Dos verdes seguidas.

		return false;

	if(n.contadores.verdesUsadas > n.contadores.azulesUsadas) // Hay mas fichas verdes que azules.

		return false;

	if(n.contadores.azulesUsadas > n.informacion.maxAzules) // Hemos empleado mas fichas azules de las que tenemos.

		return false;

	if(n.contadores.rojasUsadas > n.informacion.maxRojas) // Hemos empleado mas fichas rojas de las que tenemos.

		return false;

	if(n.contadores.verdesUsadas > n.informacion.maxVerdes) // Hemos empleado mas fichas verdes de las que tenemos.

		return false;

	return true;

}

void tratarSolucion(struct nodo& n) {

	for(const color& c : n.construccion)

		switch(c) {
			case rojo: std::cout << "rojo "; break;
			case azul: std::cout << "azul "; break;
			case verde: std::cout << "verde "; break;
		}

	std::cout << std::endl;

	++n.contadores.solucionesDiferentes;

}

bool esSolucionPrometedora(struct nodo& n) {

	// Si el total de bloques de color rojo que puedo usar ha sido igualado o superado por las fichas verdes y azules seleccionadas.
	if(n.informacion.maxRojas <= n.contadores.verdesUsadas + n.contadores.azulesUsadas)

		return false;

	return true;

}

void resolver(struct nodo& n) {

	for(int c = azul ; c <= verde ; ++c) {

		n.construccion[n.k] = (color) c;

		switch(n.construccion[n.k]) {
			case rojo: ++n.contadores.rojasUsadas; break;
			case azul: ++n.contadores.azulesUsadas; break;
			case verde: ++n.contadores.verdesUsadas; break;
		}

		if(esValida(n)) {

			if(n.informacion.altura - 1 == n.k) { // esSolucion()

				if(n.contadores.rojasUsadas > n.contadores.azulesUsadas + n.contadores.verdesUsadas) // esSolucionValida()

					tratarSolucion(n);

			} else {

				nodo siguiente = {n.k+1,n.contadores,n.construccion,n.informacion};

				if(esSolucionPrometedora(siguiente))

					resolver(siguiente);

			}

		}

		switch(n.construccion[n.k]) {
			case rojo: --n.contadores.rojasUsadas; break;
			case azul: --n.contadores.azulesUsadas; break;
			case verde: --n.contadores.verdesUsadas; break;
		}

	}

}

bool resuelveCaso() {

	informacion informacion;

	std::cin >> informacion.altura >> informacion.maxAzules >> informacion.maxRojas >> informacion.maxVerdes;

	if(informacion.altura == 0 && informacion.maxAzules == 0 && informacion.maxRojas == 0 && informacion.maxVerdes == 0)

		return false;

	// El primer piso ya está en rojo asi que empezamos en el piso 1 (k=1) en lugar del 0 (k=0).
	std::vector<color> construccion(informacion.altura);
	construccion[0] = rojo;

	contadores contadores = {1,0,0,0};

	nodo primero = { 1 , contadores , construccion , informacion };

	// Si nos piden una torre mas alta que las fichas que tenemos.
	if(informacion.altura > informacion.maxAzules + informacion.maxRojas + informacion.maxVerdes)

		std::cout << "SIN SOLUCION" << std::endl;

	else {

		resolver(primero);

		std::cout << ( (primero.contadores.solucionesDiferentes == 0)? "SIN SOLUCION\n" : "" ) ;

	}

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
