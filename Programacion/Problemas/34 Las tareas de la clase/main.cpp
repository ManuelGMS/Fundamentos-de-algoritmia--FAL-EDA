#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

// E24: Manuel Guerrero Moñús.

using iVector = std::vector<int>;

using bVector = std::vector<bool>;

using matrix = std::vector<iVector>;

struct informacion {
	int maximoTareas;
	matrix alumnoPreferencia;
};

struct solucion {
	int preferenciaMejor;
	iVector tareaRealizadaPorAlumnoMejor;
};

struct marcas {
	int preferencia;
	iVector totalTareasDelAlumno;
	iVector tareaRealizadaPorAlumno;
};

void tratarSolucion(const struct solucion& s) {

	for(const int& i : s.tareaRealizadaPorAlumnoMejor)

		std::cout << i << " ";

	std::cout << std::endl;

}

bool esValida(const int& k, const struct informacion& i, const struct marcas& m) {

	// Consultamos si el alumno sobrepasa el maximo de tareas que puede hacer.
	if(m.totalTareasDelAlumno[m.tareaRealizadaPorAlumno[k]] > i.maximoTareas)

		return false;

	/*
		En los niveles pares se tienen los niños titulares de una actividad, y en los
		impares se pregunta por el niño que hace de suplente si el titular no esta.
		Aqui preguntamos si una vez elegido el titular se ha vuelto ha seleccionar
		al mismo niño con el fin de evitarlo, ya que en caso de faltar este nadie
		realizaria la actividad.
	*/
	if(k % 2 == 1 && m.tareaRealizadaPorAlumno[k-1] == m.tareaRealizadaPorAlumno[k])

		return false;

	return true;

}

void resolver(const int& k, const struct informacion& i, struct marcas& m, struct solucion& s) {

	for(int alumno = 0 ; alumno < i.alumnoPreferencia.size() ; ++alumno) {

		++m.totalTareasDelAlumno[alumno];

		m.tareaRealizadaPorAlumno[k] = alumno;

		m.preferencia += i.alumnoPreferencia[alumno][k/2];

		if(esValida(k,i,m)) {

			if(k == m.tareaRealizadaPorAlumno.size() - 1) { // esSolucion()

				if(m.preferencia > s.preferenciaMejor) { // esSolucionMejor()

					s.preferenciaMejor = m.preferencia;

					s.tareaRealizadaPorAlumnoMejor = m.tareaRealizadaPorAlumno;

					// tratarSolucion(s); // Para depuracion.

				}

			} else resolver(k+1,i,m,s);

		}

		--m.totalTareasDelAlumno[alumno];

		m.preferencia -= i.alumnoPreferencia[alumno][k/2];

	}

}

bool resuelveCaso() {

	int tareas, alumnos, maximoTareas;
	std::cin >> tareas >> alumnos >> maximoTareas;

	if(tareas == 0 && alumnos == 0 && maximoTareas == 0)

		return false;

	matrix alumnoPreferencia(alumnos,iVector(tareas));

	for(iVector& alumno : alumnoPreferencia)

		for(int& preferencia : alumno)

			std::cin >> preferencia;

	int preferenciaMejor = 0;
	iVector totalTareasDelAlumno(alumnos);
	iVector tareaRealizadaPorAlumno(tareas*2);
	iVector tareaRealizadaPorAlumnoMejor(tareas*2);

	struct informacion i = { maximoTareas , alumnoPreferencia };

	struct solucion s = { preferenciaMejor , tareaRealizadaPorAlumnoMejor };

	struct marcas m = { 0 , totalTareasDelAlumno , tareaRealizadaPorAlumno };

	resolver(0,i,m,s);

	std::cout << s.preferenciaMejor << std::endl;

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
