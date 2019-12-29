// E24 - Manuel Guerrero Moñús

// Intercambiar el valor de dos posiciones de un vector.
// Escribe las precondiciones mas debiles de cada una de las instrucciones del codigo

method swap (v:array<int>, i:int, j:int)
requires 0<=i<v.Length && 0<=j<v.Length && i != j
ensures v[i] == old(v[j]) && v[j] == old(v[i])
modifies v
{

	assert v[j] == old(v[j]) && v[i] == old(v[i]); // Queda asi verificado que el programa hace lo que dice
	v[i]:=v[i]-v[j]; // pmd(v[j] == old(v[j]) && v[i] + v[j] == old(v[i])) CON v[i]-v[j] PARA v[i] ENTONCES v[j] == old(v[j]) && v[i] == old(v[i])
	assert v[j] == old(v[j]) && v[i] + v[j] == old(v[i]);
	v[j]:=v[i]+v[j]; // pmd(v[j]-v[i] == old(v[j]) && v[j] ==old(v[i])) CON (v[i]+v[j]) PARA v[j] ENTONCES v[j] == old(v[j]) && v[i]+v[j] == old(v[i])
	assert v[j]-v[i] == old(v[j]) && v[j] ==old(v[i]);
	v[i]:=v[j]-v[i]; // pmd(v[i] == old(v[j]) && v[j] == old(v[i])) CON (v[j]-v[i]) PARA v[i] ENTONCES v[j]-v[i] == old(v[j]) && v[j] == old(v[i])
  assert v[i] == old(v[j]) && v[j] == old(v[i]); // Post-Condición que queremos asegurar.

}

// Implementar un metodo que calcule el n-esimo numero de la sucesion de fibonacci
// Definicion de la funcion de Fibonacci para usarla en la especificacion
function Fib (n : int) : int
requires n >= 0
{ 
  if (n < 2) then n 
  else Fib(n -2) + Fib(n -1) 
}

// Metodo que calcula el n-esimo termino de la sucesion
method Fibonacci (n : int) returns (f : int)
requires n >= 0
ensures f == Fib(n)
{
	// Resolver el problema para los casos n == 0 y n == 1 antes de entrar en el bucle
	if (n == 0) { f := 0; }
	else if (n == 1) { f := 1; }
	else {
	
	// Inicializar las variables
	f := 1; // Primer anterior de la sucesion de fibonacci.
  var a := 0; // Segundo anterior de la sucession de fibonacci.
  var i := 1; // Iterador para el control del bucle.

	// Bucle con invariante y funcion cota
	while (i < n)
	invariant (1 <= i <= n) && (a == Fib(i - 1)) && (f == Fib(i))
	decreases (n - i)
	{
			// Cuerpo del bucle
      a, f := f, a + f; // Asignacion paralela: El nuevo a es el viejo f y el nuevo f es la suma de los viejos a y f.
      i := i + 1;
		}
    
	}

}

/// Implementar un metodo que dado un vector devuelva en otro vector los valores acumulados
// Se acumulan los valores de derecha a izquierda. El elemento de la posicion cero del 
// nuevo vector es la suma del vector original completo y el ultimo elemento del nuevo vector
// coincide con el valor del ultimo elemento del vector original
// Escribir el invariante para probar la correccion del bucle (invariant)
// Dar una funcion cota del bucle (decreases) y comprobar que Dafny realiza la prueba con ella.
function suma (s : seq<int>) : int
ensures s==[] ==> suma(s) == 0;
ensures s!=[] ==> suma(s) == s[0] + suma(s[1..])
{
  if(s == []) then 0
  else s[0] + suma(s[1..])
}

// Realizar un bucle que recorre el vector de derecha a izquierda
// Comenzar con el calculo de w[v.Length-1]
method acumulado (v : array<int>) returns (w : array<int>)
requires v.Length > 0
ensures w.Length == v.Length
ensures forall k :: 0 <= k < v.Length ==> w[k] == suma(v[k..])
{
	
  // Reserva memoria para el vector
  w := new int[v.Length];
    
  // Inicializacion de las variables
  var i := v.Length - 1;
  w[w.Length-1] := v[v.Length-1];
  
	// Bucle que recorre el vector de derecha a izquierda
  while (i != 0)
	invariant (0 <= i < v.Length)
	invariant forall k :: 0 <= i <= k < v.Length ==> (w[k] == suma(v[k..]))
  decreases i
	{
    w[i-1] := w[i] + v[i-1];
    i := i - 1;
	}
  
}

// Implementar un metodo que cuente el numero de posiciones de un vector que son
// mayores que todas las posiciones que tienen a su izquierda. 
// Por ejemplo, el vector: 8 5 6 10 12 4 7 5 14 7, tiene como picos el 8, 10, 12, 14

// Definir un predicado que sea cierto si la posicion i del vector tiene un pico.
predicate espico(s : seq<int> , i : int)
requires 0 <= i < |s|
ensures espico(s,i) == forall k :: 0 <= k < i ==> (s[k] <= s[i])
{
  forall k :: 0 <= k < i ==> (s[i] >= s[k])
}

// funcion que cuenta el numero de picos de una secuencia
function CountPicos(s : seq<int> , i : int) : nat 
requires 0 <= i < |s| && |s| > 0
ensures i == 0 ==> CountPicos(s,i) == 1
ensures i > 0 && espico(s,i) ==> CountPicos(s,i) == 1 + CountPicos(s,i-1)
ensures i > 0 && !espico(s,i) ==> CountPicos(s,i) == CountPicos(s,i-1)
{
  if(i == 0) then 1
  else if(espico(s,i)) then 1 + CountPicos(s,i-1)
  else CountPicos(s,i-1)
}

// metodo que cuenta el numero de picos de un vector
method numPicos(v:array<int>) returns (n:int) 
requires v.Length > 0
ensures n == CountPicos(v[..],v.Length-1)
{
	
  // Inicializacion de las variables
	n := 1;
  var i := 1; 
  var posicionPico := 0; 

	// Bucle con invariante funcion cota
	while (i < v.Length)
  invariant (1 <= i <= v.Length) && (0 <= posicionPico < i)
  invariant forall k :: 0 <= k < i ==> (v[k] <= v[posicionPico])
  invariant n == CountPicos(v[..],i-1)
  decreases v.Length - i
	{
    // Cuerpo del bucle
		if (v[i] >= v[posicionPico])
    {
      posicionPico := i;
      n := n + 1;
    }
    i := i + 1;
	}
   
}

