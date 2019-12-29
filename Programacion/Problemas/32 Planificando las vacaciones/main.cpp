#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

using iVector = std::vector<int>;

using bVector = std::vector<bool>;

using matrix = std::vector<iVector>;

const int MAS_INFINITO = std::numeric_limits<int>::max();

struct informacion {
	int presupuesto;
	int diaTemporadaBaja;
	int viajeHotelOptimista;
	matrix costeOrigenDestino;
	iVector preciosTemporadaAlta;
	iVector preciosTemporadaBaja;
};

struct solucion {
	int precioMejor;
	iVector recorridoMejor;
};

struct marcas {
	int precioActual;
	iVector recorrido;
	bVector ciudadVisitada;
};


bool esValida(const int& k, const struct informacion& i, const struct marcas& m) {

	// Comprobamos si no nos hemos pasado de  presupuesto.
	if(m.precioActual > i.presupuesto)

		return false;

	// Comprobamos si ya hemos pasado por esta ciudad.
	if(m.ciudadVisitada[m.recorrido[k]])

		return false;

	return true;

}

void tratarSolucion(const struct solucion& s) {

	std::cout << s.precioMejor << std::endl;

	for(const int& i : s.recorridoMejor)

		std::cout << i << " ";

	std::cout << std::endl;

}

void resolver(const int& k, const struct informacion& i, struct marcas& m, struct solucion& s) {

	for(int ciudadDestino = 1 ; ciudadDestino < m.ciudadVisitada.size() ; ++ciudadDestino) {

		m.recorrido[k] = ciudadDestino;

		m.precioActual += i.costeOrigenDestino[m.recorrido[k-1]][ciudadDestino];
		m.precioActual += (k >= i.diaTemporadaBaja)? i.preciosTemporadaBaja[ciudadDestino] : i.preciosTemporadaAlta[ciudadDestino];

		if(esValida(k,i,m)) {

			m.ciudadVisitada[ciudadDestino] = true;

			// esSolucion() --> Si ya hemos pasado por todas las ciudades y solo queda regresar a casa.
			if(k == m.ciudadVisitada.size() - 1) {

				// esSolucionValida() --> Si el billete de vuelta entra en el presupuesto.
				if(m.precioActual + i.costeOrigenDestino[m.recorrido[k]][m.recorrido[0]] <= i.presupuesto) {

					// // esSolucionMejor() --> Si nos sale mas rentable que una solucion anterior
					if(m.precioActual + i.costeOrigenDestino[m.recorrido[k]][m.recorrido[0]] < s.precioMejor) {

						s.recorridoMejor = m.recorrido;

						s.precioMejor = m.precioActual + i.costeOrigenDestino[m.recorrido[k]][m.recorrido[0]];

						// tratarSolucion(s); // Para depuracion

					}

				}

			} else {

				// Estimacion optimista simple, le sumamos al costo actual el producto de las ciudades que faltan por el minimo coste.
				if(m.precioActual + i.viajeHotelOptimista * (m.ciudadVisitada.size()-(k+1)) < s.precioMejor)

					resolver(k+1,i,m,s);

			}

			m.ciudadVisitada[ciudadDestino] = false;

		}

		m.precioActual -= i.costeOrigenDestino[m.recorrido[k-1]][ciudadDestino];
		m.precioActual -= (k >= i.diaTemporadaBaja)? i.preciosTemporadaBaja[ciudadDestino] : i.preciosTemporadaAlta[ciudadDestino];

	}

}

bool resuelveCaso() {

	int ciudades, diaTemporadaBaja, presupuesto;
	std::cin >> ciudades >> diaTemporadaBaja >> presupuesto;

	if(ciudades == 0 && diaTemporadaBaja == 0 && presupuesto == 0)

		return false;

	int viajeHotelOptimista = 0;

	int hotelMasBarato = MAS_INFINITO;

	int viajeMasBarato = MAS_INFINITO;

	bVector ciudadVisitada(ciudades+1);

	iVector preciosTemporadaAlta(ciudades+1);

	iVector preciosTemporadaBaja(ciudades+1);

	for(int i = 1 ; i < preciosTemporadaAlta.size() ; ++i)

		std::cin >> preciosTemporadaAlta[i];

	for(int i = 1 ; i < preciosTemporadaBaja.size() ; ++i) {

		std::cin >> preciosTemporadaBaja[i];

		hotelMasBarato = std::min(hotelMasBarato,preciosTemporadaBaja[i]);

	}

	matrix costeOrigenDestino(ciudades+1,iVector(ciudades+1));

	for(int origen = 0 ; origen < costeOrigenDestino.size() ; ++origen)

		for(int destino = 0 ; destino < costeOrigenDestino[0].size() ; ++destino) {

			std::cin >> costeOrigenDestino[origen][destino];

			costeOrigenDestino[destino][origen] = costeOrigenDestino[origen][destino];

			if(origen != destino)

				viajeMasBarato = std::min(viajeMasBarato,costeOrigenDestino[origen][destino]);

		}

	viajeHotelOptimista = hotelMasBarato + viajeMasBarato;

	int precioActual = 0;

	iVector recorrido(ciudades+1);

	int precioMejor = MAS_INFINITO;

	iVector recorridoMejor(ciudades+1);

	struct solucion s = { precioMejor , recorridoMejor };

	struct marcas m = { precioActual , recorrido , ciudadVisitada };

	struct informacion i = { presupuesto , diaTemporadaBaja , viajeHotelOptimista , costeOrigenDestino , preciosTemporadaAlta , preciosTemporadaBaja };

	// El recorrido antes de la VA sabemos que es recorrido = { 0 , ... } , es decir, comienza en cero (en el pais de origen o punto de partida).
	resolver(1,i,m,s);

	if(s.precioMejor == MAS_INFINITO)

		std::cout << "No puedes ir";

	else

		std::cout << s.precioMejor;

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
