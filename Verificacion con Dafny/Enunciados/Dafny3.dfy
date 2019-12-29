// Intercambiar el valor de dos posiciones de un vector.
// Escribe las precondiciones mas debiles de cada una de las instrucciones del codigo

method swap (v:array<int>, i:int, j:int)
requires v != null
requires 0<=i<v.Length && 0<=j<v.Length && i != j
ensures v[i] == old(v[j]) && v[j] == old(v[i])
modifies v
{
	assert ...;
	v[i]:=v[i]-v[j];
	assert ...;
	v[j]:=v[i]+v[j];
	assert ...;
	v[i]:=v[j]-v[i];
	assert ...;
}


// Implementar un metodo que calcule el n-esimo numero de la sucesion de fibonacci
// Definicion de la funcion de Fibonacci para usarla en la especificacion
function Fib (n : int) : int
requires n >= 0
{ if (n < 2) then n else Fib(n -2) + Fib(n -1) }

// Metodo que calcula el n-esimo termino de la sucesion
method Fibonacci (n : int) returns (f : int)
requires ...
ensures ...
{
	// Resolver el problema para los casos n == 0 y n == 1 antes de entrar en el bucle
	if (n == 0) { f := 0; }
	else if (n == 1) {f := 1;}
	else {
	
		// Inicializar las variables
		var ...
		// Bucle con invariante y funcion cota
		while (...) 
		invariant ...
		decreases ...
		{
			// Cuerpo del bucle
			
			
		}
	}

}


// Implementar un metodo que dado un vector devuelva en otro vector los valores acumulados
// Se acumulan los valores de derecha a izquierda. El elemento de la posicion cero del 
// nuevo vector es la suma del vector original completo y el ultimo elemento del nuevo vector
// coincide con el valor del ultimo elemento del vector original
// Escribir el invariante para probar la correccion del bucle (invariant)
// Dar una funcion cota del bucle (decreases) y comprobar que Dafny realiza la prueba con ella.
function suma (s : seq<int>) : int
ensures s==[] ==> suma(s) == 0;
ensures s!=[] ==> suma(s) == s[0] + suma(s[1..])

// Realizar un bucle que recorre el vector de derecha a izquierda
// Comenzar con el calculo de w[v.Length-1]
method acumulado (v : array<int>) returns (w : array<int>)
requires v != null && v.Length > 0
ensures w != null && w.Length == v.Length
ensures forall k :: 0 <= k < v.Length ==> w[k] == suma(v[k..])
{
	w := new int[v.Length];  // Reserva memoria para el vector
	// Inicializacion de las variable
	var ...
	
	// Bucle que recorre el vector de derecha a izquierda
	while (...)
	invariant ...
	decreases ...
	{
	
	
	}
}


// Implementar un metodo que cuente el numero de posiciones de un vector que son
// mayores que todas las posiciones que tienen a su izquierda. 
// Por ejemplo, el vector: 8 5 6 10 12 4 7 5 14 7, tiene como picos el 8, 10, 12, 14

// Definir un predicado que sea cierto si la posicion i del vector tiene un pico
predicate espico(s:seq<int>,i:int)
requires...
ensures espico(s,i) == ...

// funcion que cuenta el numero de picos de una secuencia
function CountPicos(s:seq<int>,i:int):nat requires 0<=i<|s| && |s| > 0
ensures ...


// metodo que cuenta el numero de picos de un vector
method numPicos(v:array<int>) returns (n:int) 
requires v!=null && v.Length>0
ensures n==CountPicos(v[..],v.Length-1)
{
	// Inicializacion de las variables
	var ...

	// Bucle con invariante funcion cota
	while (...)
	invariant ... 
	decreases ...
	{
		// Cuerpo del bucle
		
	}
}

