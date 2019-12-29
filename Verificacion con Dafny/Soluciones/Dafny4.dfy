// E24 - Manuel Guerrero Moñús

// Implementar un metodo que resuelva el problema 37 del juez.
// Probar que es correcto respecto a la especificacion

method problema3 (a : array<int>, p : int) returns (b : bool)
requires a.Length > 0
requires 0 <= p < a.Length
ensures b == forall u, w :: 0 <= u <= p < w < a.Length ==> a[u] < a[w]
{
	
  // Si esto se cumple P ==> Q directamente y no hay que hacer nada.
  if(p == a.Length - 1) {
    return true;
  }
  
	// Inicializacion
	var i := 0;
  var max := a[0];
  var min := a[p+1];

	// Bucle para obtener el mayor valor de la parte izquierda de la particion
	while (i <= p) 
	invariant 0 <= i <= p+1
	invariant forall k :: 0 <= k < i ==> max >= a[k]
  invariant max in a[..p+1]
  decreases p - i
	{
		// Instrucciones del bucle
		if(a[i] > max) {
      max := a[i];
    }
		i := i + 1;
	}
	
  // Probar que la variable max tiene el maximo de la parte izquierda
	assert forall k :: 0 <= k <= p ==> max >= a[k];
	assert max in a[..p+1];
	
  // Bucle para obtener el menor valor de la parte derecha de la particion
	while (i < a.Length) 
	invariant (p < i <= a.Length)
	invariant forall k :: p < k < i ==> min <= a[k]
  invariant min in a[(p+1)..]
  decreases (a.Length - i)
	{
		// Instrucciones del bucle
    if(a[i] <= min) {
      min := a[i];
    }
    i := i + 1;
  }
	
  // Probar que la variable min tiene el minimo de la parte derecha,
  assert forall k :: p < k < i ==> min <= a[k];
  assert min in a[(p+1)..];
  
  // Retornamos b y finaliza el programa.
  return (max < min);

}


// Implementar un metodo que cuente el numero de valores de un vector que son mayores que todos los valores a su derecha
// Definir un predicado que sea cierto todos los valores a la derecha de la posicion i son menores que el valor de la posicion i

predicate esMirador(s:seq<int>,i:int)
requires 0 <= i < |s|
{
  forall k :: i < k < |s| ==> s[k] <= s[i]
}

// Definir una funcion que cuente el numero de miradores de una secuencia
function CountMiradores(s:seq<int>,i : int):nat
requires 0 <= i < |s| && |s| > 0
decreases |s| - i
{
	if (i == |s| - 1) then 1
	else if (i < |s| - 1 && esMirador(s,i)) then 1 + CountMiradores(s,i+1)
	else CountMiradores(s,i+1)
}

// Implementar un metodo que cuente el numero de miradores de un vector
method numMiradores(v:array<int>) returns (n:int)
requires v.Length > 0
ensures n == CountMiradores(v[..],0)
{

  // Inicializar variables
	n := 1;
  var i := v.Length - 1;
	var maximo := v[v.Length-1];

	// Bucle
	while (i > 0)
	invariant 0 <= i < v.Length
    invariant maximo in v[i..]
  invariant 1 <= n <= (v.Length-i)
  invariant n == CountMiradores(v[..],i)
  invariant forall u :: i <= u < v.Length ==> maximo >= v[u]
  decreases i
  {
		if(v[i-1] >= maximo) {
      maximo := v[i-1];
      n := n + 1;
    }
    i := i - 1;
	}
  
  return n;
  
}


// Implementar un metodo que elimine los valores iguales a x de un vector v
// Debe resolverse con complejidad lineal

// tam :  numero de elemento diferentes de x en el vector v de entrada. 
// El vector modificado debe tener estos elementos en las tam primeras posiciones
// Se probará primero que el valor x no aparece en las tam primeras posiciones
// Despues escribir otra postcondicion que indique que los tam primeros valores del 
// vector modificado estan en el vector original
method eliminar(v : array<int> , x : int) returns (tam : int)
requires v.Length > 0
ensures 0 <= tam <= v.Length
ensures forall u :: 0 <= u < tam ==> v[u] != x
ensures forall w :: 0 <= w < tam ==> v[w] in old(v[..])
modifies v
{
  // Inicializar las variables
	var i := 0; // Iterador del bucle
  var p := 0; // La posicion p coincide con el numero de elementos distintos a x
  
	// Bucle
	while (i < v.Length) 
	invariant 0 <= i <= v.Length
  invariant 0 <= p <= i
  invariant forall k :: 0 <= k < p ==> v[k] != x
  invariant forall u :: 0 <= u < v.Length ==> v[u] in old(v[..])
  decreases v.Length - i
	{
		//Cuerpo del bucle
		if(v[i] != x) {
      v[p] , v[i] := v[i] , v[p];
      p := p + 1;
    }
    i := i + 1;
	}
  
  // Comprobaciones
  assert forall u :: 0 <= u < p ==> v[u] != x;
  assert forall u :: 0 <= u < p ==> v[u] in old(v[..]);
  
  // Final del programa
  return p;

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
requires n >= 0
ensures j == Jacob(n)
{
	
  // Resolver los casos n == 0 y n == 1
  if(n == 0) { j := 0; }
  else if(n == 1) { j := 1; }
  else {
    
    // Inicializar las variables para el caso > 2
	  j := 1;
    var i := 1;
    var anterior := 0;
   
	 // Bucle para realizar el calculo
	 while (i < n)
	 invariant (1 <= i <= n) && (anterior == Jacob(i-1)) && (j == Jacob(i))
   decreases (n - i)
	 {
		// Cuerpo del bucle
		anterior , j := j , j + 2 * anterior;
		i := i + 1;
	 } 
   
  }
  
}
