#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

/*
 * E24: Manuel Guerrero Moñús.
 *
 * Complejidad: O(2^n)
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 				esSolucionMejor()
 *
 * 			2 * T(n-1) + c	En el peor de los otros casos.
 *
 * 		}
 *
 */

using iVector = std::vector<int>;

using bVector = std::vector<bool>;

using matrix = std::vector<iVector>;

struct informacion {
	int presupuesto;
	iVector precios;
	iVector superficieOcupada;
};

struct solucion {
	int superficieMejor;
	bVector seleccionMejor;
};

struct marcas {
	int costeActual;
	int superficieActual;
	bVector seleccionActual;
};

void resolver(const int& k, const struct informacion& i, struct marcas& m, struct solucion& s) {

	// Si lo cojo.
	m.seleccionActual[k] = true;
	m.costeActual += i.precios[k];
	m.superficieActual += i.superficieOcupada[k];

	if(m.costeActual <= i.presupuesto) { // esValida()

		if(k == s.seleccionMejor.size() - 1) { // esSolucion()

			if(s.superficieMejor < m.superficieActual) { // esSolucionMejor()

				s.seleccionMejor = m.seleccionActual;

				s.superficieMejor = m.superficieActual;

			}

		} else resolver(k+1,i,m,s);

	}

	// Si no lo cojo.
	m.seleccionActual[k] = false;
	m.costeActual -= i.precios[k];
	m.superficieActual -= i.superficieOcupada[k];

	if(k == s.seleccionMejor.size() - 1) { // esSolucion()

		if(s.superficieMejor < m.superficieActual) { // esSolucionMejor()

			s.seleccionMejor = m.seleccionActual;

			s.superficieMejor = m.superficieActual;

		}

	} else resolver(k+1,i,m,s);

}

bool resuelveCaso() {

	int objetos, presupuesto;
	std::cin >> objetos >> presupuesto;

	if(!std::cin)

		return false;

	iVector precios(objetos);

	for(int& p : precios)

		std::cin >> p;

	iVector superficieOcupada(objetos);

	for(int& s : superficieOcupada)

		std::cin >> s;

	int costeActual = 0;
	int superficieMejor = 0;
	int superficieActual = 0;
	bVector seleccionMejor(objetos);
	bVector seleccionActual(objetos);

	solucion s = { superficieMejor , seleccionMejor };

	informacion i = { presupuesto , precios , superficieOcupada };

	marcas m = { costeActual , superficieActual , seleccionActual };

	resolver(0,i,m,s);

	std::cout << s.superficieMejor << std::endl;

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
