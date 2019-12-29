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

using bVector = std::vector<bool>;

using matrix = std::vector<iVector>;

const int MENOS_INFINITO = std::numeric_limits<int>::min();

struct nodo {
	const int& k;
	matrix& papelActor;
	int& presupuestoMejor;
	bVector& actorOcupado;
	const int& puntuacion;
	int& presupuestoActual;
	const iVector& salarios;
	int& puntuacionDelReparto;
	int& puntuacionMejorReparto;
	const int& presupuestoTotal;
	iVector& actorAsignadoAlPapel;
	const iVector& maximosAcumulados;
	iVector& actorAsignadoAlPapelMejor;
};

bool esValida(struct nodo& n) {

	// Si el actor ya esta ocupado.
	if(n.actorOcupado[n.actorAsignadoAlPapel[n.k]])

		return false;

	// La peli sesale de presupuesto.
	if(n.presupuestoActual > n.presupuestoTotal)

		return false;

	// El actor no supera la nota minima para actuar.
	if(n.papelActor[n.k][n.actorAsignadoAlPapel[n.k]] < n.puntuacion)

		return false;

	return true;

}

void tratarSolucion(struct nodo& n) {

	std::cout << n.puntuacionMejorReparto << " " << n.presupuestoActual <<std::endl;

	for(int papel = 0 ; papel < n.actorAsignadoAlPapel.size() ; ++papel)

		std::cout << papel << " " << n.actorAsignadoAlPapel[papel] << std::endl;

}

void resolver(struct nodo& n) {

	for(int actor = 0 ; actor < n.salarios.size() ; ++actor) {

		n.actorAsignadoAlPapel[n.k] = actor;

		n.presupuestoActual += n.salarios[actor];

		n.puntuacionDelReparto += n.papelActor[n.k][actor];

		if(esValida(n)) {

			n.actorOcupado[actor] = true;

			if(n.k == n.actorAsignadoAlPapel.size() -1) { // esSolucion()

				if(n.puntuacionDelReparto > n.puntuacionMejorReparto) { // esSolucionMejor()

					n.presupuestoMejor = n.presupuestoActual;

					n.puntuacionMejorReparto = n.puntuacionDelReparto;

					n.actorAsignadoAlPapelMejor = n.actorAsignadoAlPapel;

					// tratarSolucion(n); // Para depuracion

				}

			} else {

				if(n.puntuacionDelReparto + n.maximosAcumulados[n.k+1] > n.puntuacionMejorReparto) {

					nodo siguiente = {
						n.k + 1 ,
						n.papelActor,
						n.presupuestoMejor,
						n.actorOcupado,
						n.puntuacion,
						n.presupuestoActual,
						n.salarios,
						n.puntuacionDelReparto,
						n.puntuacionMejorReparto,
						n.presupuestoTotal,
						n.actorAsignadoAlPapel,
						n.maximosAcumulados,
						n.actorAsignadoAlPapelMejor,
					};

					resolver(siguiente);

				}

			}

			n.actorOcupado[actor] = false;

		}

		n.presupuestoActual -= n.salarios[actor];

		n.puntuacionDelReparto -= n.papelActor[n.k][actor];

	}

}

bool resuelveCaso() {

	int papeles, actores, presupuesto, puntuacion;
	std::cin >> papeles >> actores >> presupuesto >> puntuacion;

	if(papeles == 0 && actores == 0 && presupuesto == 0 && puntuacion == 0)

		return false;

	iVector salarios(actores);

	for(int& i : salarios)

		std::cin >> i;

	iVector maximosAcumulados(papeles);

	matrix papelActor(papeles,iVector(actores));

	for(int papel = 0 ; papel < papeles ; ++papel)

		for(int actor = 0 ; actor < actores ; ++actor) {

			std::cin >> papelActor[papel][actor];

			maximosAcumulados[papel] = std::max(maximosAcumulados[papel],papelActor[papel][actor]);

		}

	for(int papel = maximosAcumulados.size() - 2 ; papel > -1 ; --papel)

		maximosAcumulados[papel] += maximosAcumulados[papel+1];

	int presupuestoMejor = 0;

	int presupuestoActual = 0;

	int puntuacionDelReparto = 0;

	bVector actorOcupado(actores);

	iVector actorAsignadoAlPapel(papeles);

	iVector actorAsignadoAlPapelMejor(papeles);

	int puntuacionMejorReparto = MENOS_INFINITO;

	nodo primero = {
		0,
		papelActor,
		presupuestoMejor,
		actorOcupado,
		puntuacion,
		presupuestoActual,
		salarios,
		puntuacionDelReparto,
		puntuacionMejorReparto,
		presupuesto,
		actorAsignadoAlPapel,
		maximosAcumulados,
		actorAsignadoAlPapelMejor
	};

	resolver(primero);

	if(puntuacionMejorReparto == MENOS_INFINITO)

		std::cout << "0" << " " << "0" << std::endl;

	else {

		std::cout << puntuacionMejorReparto << " " << presupuestoMejor <<std::endl;

		for(int papel = 0 ; papel < actorAsignadoAlPapelMejor.size() ; ++papel)

			std::cout << papel << " " << actorAsignadoAlPapelMejor[papel] << std::endl;

	}

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
