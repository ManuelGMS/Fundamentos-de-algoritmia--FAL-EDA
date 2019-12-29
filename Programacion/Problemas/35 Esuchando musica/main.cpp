#include <vector>
#include <fstream>
#include <iostream>

// E24: Manuel Guerrero Moñús.

struct cancion {
	int duracion;
	int satisfaccion;
};

using iVector = std::vector<int>;

using bVector = std::vector<bool>;

using cVector = std::vector<cancion>;

struct informacion {
	int tiempoIda;
	cVector cancion;
	int tiempoVuelta;
	int totalCanciones;
};

struct solucion {
	int satisfaccionMejor;
	bVector cancionesParaViajeDeIdaMejor;
	bVector cancionesParaViajeDeVueltaMejor;
};

struct marcas {
	int satisfaccion;
	int duracionCancionesIda;
	int duracionCancionesVuelta;
	bVector cancionesParaViajeDeIda;
	bVector cancionesParaViajeDeVuelta;
};

void tratarSolucion(const struct informacion& i, const struct solucion& s) {

	std::cout << "Tiempo Ida: " << i.tiempoIda << " , Tiempo Vuelta: " << i.tiempoVuelta << std::endl;

	std::cout << "Canciones de Ida: ";

	for(int i = 0 ; i < s.cancionesParaViajeDeIdaMejor.size(); ++i)

		if(s.cancionesParaViajeDeIdaMejor[i] == true)

			std::cout << "Cancion: " << i << " ";

	std::cout << std::endl;

	std::cout << "Canciones de Vuelta: ";

	for(int i = 0 ; i < s.cancionesParaViajeDeVueltaMejor.size(); ++i)

		if(s.cancionesParaViajeDeVueltaMejor[i] == true)

			std::cout << "Cancion: " << i << " ";

	std::cout << std::endl;

}

void resolver(const int& k, const struct informacion& i, struct marcas& m, struct solucion& s) {

	// Si cojo la cancion para el viaje de ida.

	m.cancionesParaViajeDeIda[k] = true;
	m.satisfaccion += i.cancion[k].satisfaccion;
	m.duracionCancionesIda += i.cancion[k].duracion;

	if(m.duracionCancionesIda <= i.tiempoIda) { // esValida()

		if(k == i.totalCanciones - 1) { // esSolucion()

			if(m.duracionCancionesIda == i.tiempoIda && m.duracionCancionesVuelta == i.tiempoVuelta) { // esSolucionValida()

				if(m.satisfaccion > s.satisfaccionMejor) { // esSolucionMejor()

					s.satisfaccionMejor = m.satisfaccion;

					s.cancionesParaViajeDeIdaMejor = m.cancionesParaViajeDeIda;

					s.cancionesParaViajeDeVueltaMejor = m.cancionesParaViajeDeVuelta;

					// tratarSolucion(i,s); // Para depuracion

				}

			}

		} else resolver(k+1,i,m,s);

	}

	m.cancionesParaViajeDeIda[k] = false;
	m.satisfaccion -= i.cancion[k].satisfaccion;
	m.duracionCancionesIda -= i.cancion[k].duracion;

	// Si cojo la cancion para el viaje de vuelta.

	m.cancionesParaViajeDeVuelta[k] = true;
	m.satisfaccion += i.cancion[k].satisfaccion;
	m.duracionCancionesVuelta += i.cancion[k].duracion;

	if(m.duracionCancionesVuelta <= i.tiempoVuelta) { // esValida()

		if(k == i.totalCanciones - 1) { // esSolucion()

			if(m.duracionCancionesIda == i.tiempoIda && m.duracionCancionesVuelta == i.tiempoVuelta) { // esSolucionValida()

				if(m.satisfaccion > s.satisfaccionMejor) { // esSolucionMejor()

					s.satisfaccionMejor = m.satisfaccion;

					s.cancionesParaViajeDeIdaMejor = m.cancionesParaViajeDeIda;

					s.cancionesParaViajeDeVueltaMejor = m.cancionesParaViajeDeVuelta;

					// tratarSolucion(i,s); // Para depuracion

				}

			}

		} else resolver(k+1,i,m,s);

	}

	m.cancionesParaViajeDeVuelta[k] = false;
	m.satisfaccion -= i.cancion[k].satisfaccion;
	m.duracionCancionesVuelta -= i.cancion[k].duracion;

	// Si no cojo la cancion.

	if(k == i.totalCanciones - 1) { // esSolucion()

		if(m.duracionCancionesIda == i.tiempoIda && m.duracionCancionesVuelta == i.tiempoVuelta) { // esSolucionValida()

			if(m.satisfaccion > s.satisfaccionMejor) { // esSolucionMejor()

				s.satisfaccionMejor = m.satisfaccion;

				s.cancionesParaViajeDeIdaMejor = m.cancionesParaViajeDeIda;

				s.cancionesParaViajeDeVueltaMejor = m.cancionesParaViajeDeVuelta;

				// tratarSolucion(i,s); // Para depuracion

			}

		}

	} else resolver(k+1,i,m,s);

}

bool resuelveCaso() {

	int totalCanciones, tiempoIda, tiempoVuelta;
	std::cin >> totalCanciones >> tiempoIda >> tiempoVuelta;

	if(totalCanciones == 0 && tiempoIda == 0 && tiempoVuelta == 0)

		return false;

	cVector cancion(totalCanciones);

	for(auto& c : cancion)

		std::cin >> c.duracion >> c.satisfaccion;

	int satisfaccion = 0;
	int satisfaccionMejor = 0;
	int duracionCancionesIda = 0;
	int duracionCancionesVuelta = 0;
	bVector cancionesParaViajeDeIda(totalCanciones);
	bVector cancionesParaViajeDeVuelta(totalCanciones);

	struct solucion s = { satisfaccionMejor };

	struct informacion i = { tiempoIda, cancion, tiempoVuelta, totalCanciones };

	struct marcas m = { satisfaccion , duracionCancionesIda, duracionCancionesVuelta , cancionesParaViajeDeIda , cancionesParaViajeDeVuelta };

	resolver(0,i,m,s);

	if(s.satisfaccionMejor == 0)

		std::cout << "Imposible";

	else

		std::cout << s.satisfaccionMejor;

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
