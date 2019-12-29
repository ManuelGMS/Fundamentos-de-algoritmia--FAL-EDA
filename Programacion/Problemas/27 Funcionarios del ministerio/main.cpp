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

using bTupla = std::vector<bool>;

using matriz = std::vector<iTupla>;

struct nodo {
	const int& k;
	bTupla& marcas;
	int& totalHoras;
	int& mejorSolucion;
	matriz& funcionario;
};

void resolver(struct nodo& n) {

	for(int tarea = 0 ; tarea < n.funcionario.size() ; ++tarea) {

		n.totalHoras += n.funcionario[n.k][tarea];

		if(!n.marcas[tarea]) { // esValida()

			n.marcas[tarea] = true;

			if(n.funcionario.size() - 1 == n.k) { // esSolucion()

				if(n.totalHoras < n.mejorSolucion) // esSolucionValida()

					n.mejorSolucion = n.totalHoras;

			} else {

				nodo siguiente = { n.k + 1 , n.marcas , n.totalHoras , n.mejorSolucion , n.funcionario };

				resolver(siguiente);

			}

			n.marcas[tarea] = false;

		}

		n.totalHoras -= n.funcionario[n.k][tarea];

	}

}

bool resuelveCaso() {

	int numFuncionariosTrabajos;
	std::cin >> numFuncionariosTrabajos;

	if(numFuncionariosTrabajos == 0)

		return false;

	int totalHoras = 0;

	int mejorSolucion = 0;

	matriz funcionario(numFuncionariosTrabajos);

	bTupla marcas(numFuncionariosTrabajos,false);

	for(int i = 0 ; i < funcionario.size() ; ++i) {

		iTupla tiempoTarea(numFuncionariosTrabajos);

		for(int j = 0 ; j < funcionario.size() ; ++j) {

			std::cin >> tiempoTarea[j];

			if(i == j)

				mejorSolucion += tiempoTarea[j];

		}

		funcionario[i] = tiempoTarea;

	}

	nodo primero = { 0 , marcas , totalHoras , mejorSolucion , funcionario };

	resolver(primero);

	std::cout << mejorSolucion << std::endl;

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
