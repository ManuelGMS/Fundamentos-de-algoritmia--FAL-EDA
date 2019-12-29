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
 * 			c 			esSolucionValida()
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
	iTupla& minimosAcumulados;
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

				/*
					Si la solucion actual + lo mas optimista que vamos a tardar
					en hacer el resto de tareas es < que la solucion actual entonces continuamos.
				*/
				if(n.totalHoras + n.minimosAcumulados[n.k+1] < n.mejorSolucion) { // esSolucionPrometedora()

					nodo siguiente = { n.k + 1 , n.marcas , n.totalHoras , n.mejorSolucion , n.funcionario , n.minimosAcumulados };

					resolver(siguiente);

				}

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

	int tareaMejor = 0;

	int totalHoras = 0;

	int mejorSolucion = 0;

	bTupla marcas(numFuncionariosTrabajos,false);

	iTupla minimosAcumulados(numFuncionariosTrabajos);

	matriz funcionario(numFuncionariosTrabajos,iTupla(numFuncionariosTrabajos));

	for(int i = 0 ; i < funcionario.size() ; ++i)

		for(int j = 0 ; j < funcionario.size() ; ++j) {

			std::cin >> funcionario[i][j];

			if(i == j) // Cogemos la diagonal como solucion optima inicial.

				mejorSolucion += funcionario[i][i];

		}

	// De cada funcionario vamos a coger la tarea que mas rapido hace.

	for(int i = 0 ; i < funcionario.size() ; ++i) {

		tareaMejor = funcionario[i][0];

	    for(int j = 1 ; j < funcionario.size() ; ++j )

	    	tareaMejor = std::min(tareaMejor,funcionario[i][j]);

	    minimosAcumulados[i] = tareaMejor;

	}

	/*
		Acumulamos los tiempos de tardanza optimos de los empleados,
		de esta forma en la primera posicion tenemos el tiemo IDEAL
		que tardarian los funcionarios en hacer toadas las tareas,
		en la segunda posicion tendriamos el tiempo minimo que tardariamos
		en hacer todas las tareas menos una, en la siguiente el tiempo
		minimo en hacer todas las tareas menos dos y asi sucesivamente.
	*/

	for(int i = minimosAcumulados.size() - 2 ; i > -1 ; --i)

		minimosAcumulados[i] += minimosAcumulados[i+1];

	nodo primero = { 0 , marcas , totalHoras , mejorSolucion , funcionario , minimosAcumulados };

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
