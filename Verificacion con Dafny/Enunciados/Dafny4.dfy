// Implementar un metodo que resuelva el problema 37 del juez.
// Probar que es correcto respecto a la especificacion

method problema3 (a : array<int>, p : int) returns (b : bool)
requires a != null && a.Length > 0
requires 0 <= p < a.Length
ensures b == forall u, w :: 0 <= u <= p < w < a.Length ==> a[u] < a[w]
{
	// calculo del maximo de la parte izquierda
	// Inicializacion
	var max := ...

	// Bucle
	while (...) 
	invariant ...
	invariant ...
	invariant ...
	{
		// Instrucciones del bucle
		
		
	}
	// probar que la variable max tiene el maximo de la parte izquierda
	assert forall k :: 0 <= k <= p ==> max >= a[k];
	assert max in a[..p+1];
	// Bucle para comprobar que el maximo de la parte izquierda es menos que 
	// todos los valores de la derecha
	while (...) 
	invariant ...
	invariant ...
	{
		// Instrucciones del bucle
	}
	// Posibles instrucciones de finalizacion


}



// Implementar un metodo que cuente el numero de valores de un vector que son mayores 
// que todos los valores a su derecha

// Definir un predicado que sea cierto todos los valores a la derecha de la posicion i
// son menores que el valor de la posicion i
predicate esMirador(s:seq<int>,i:int)
requires 0<=i<|s|
{ forall k::i<k<|s| ==> s[i]>=s[k]}

// definir una funcion que cuente el numero de miradores de una secuencia
function CountMiradores(s:seq<int>,i : int):nat
requires 0<=i<|s| && |s| > 0
decreases |s|-i
{
	if (i == |s| - 1) then 1
	else if (i < |s| - 1 && esMirador(s,i)) then 1 + CountMiradores(s,i+1)
	else CountMiradores(s,i+1)
}

// Implementar un metodo que cuente el numero de miradores de un vector
method numMiradores(v:array<int>) returns (n:int)
requires v!=null && v.Length>0
ensures n==CountMiradores(v[..],0)
{
	// Inicializar variables
	var ...
	
	// Bucle
	while (...)
	invariant ...
	{
		// Cuerpo del bucle
		
		
	}
}


// Implementar un metodo que elimine los valores iguales a x de un vector v
// Debe resolverse con complejidad lineal
// tam :  numero de elemento diferentes de x en el vector v de entrada. 
// El vector modificado debe tener estos elementos en las tam primeras posiciones
// Se probará primero que el valor x no aparece en las tam primeras posiciones
// Despues escribir otra postcondicion que indique que los tam primeros valores del 
// vector modificado estan en el vector original
method eliminar (v : array<int>, x : int) returns (tam : int)
requires ...
ensures ...
modifies v
{
	// Inicializar las variables
	
	//bucle
	while (...) 
	invariant ...
	{
		//Cuerpo del bucle
		
	}

}




// Implementar un metodo que calcule el n-esimo numero de Jacobsthal
// Funcion que define los numeros de Jacobsthal
function Jacob (n : int) : int
requires n >= 0
ensures n < 2 ==> Jacob(n) == n
ensures n >= 2 ==> Jacob(n) == Jacob(n-1) + 2 * Jacob(n-2)
{
	if (n < 2) then n
	else Jacob(n-1) + 2 * Jacob(n-2)
}

// Implementar el metodo
method Jacobsthal (n : int) returns (j : int)
requires ...
ensures ...
{
	// Resolver los casos n == 0 y n == 1


	// Inicializar las variables para el caso > 2
	var ...

	// Bucle para realizar el calculo
	while (...)
	invariant ...
	{
		// Cuerpo del bucle
		
		
	} 
}


