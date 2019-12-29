// Intercambio del valor de dos posiciones de un vector
// Version correcta

method swap (v : array<int>, i : int, j : int) 
requires 
ensures 
modifies v
{
	var aux := v[i];
	v[i] := v[j];
	v[j] := aux;
}

// Funcion que comprueba que todos los elementos de un vector son pares
predicate par (n : int)
requires 
{          }

method verificaPar (v : array<int>) returns (b : bool) 
requires  
ensures 
{
	var i := 0;
	while (i < v.Length && v[i]%2 == 0) 
	invariant 0 <= i <= v.Length
	invariant forall w :: 0 <= w < i ==> par(v[w])
	{
		i := i + 1;
	}
	b := i == v.Length;
}

// Funcion que calcula el valor maximo de un vector
method maximo (v : array<int>) returns (m : int)
requires 
ensures 
{
	var i := 1;
	m := v[0];
	while (i < v.Length) 
	invariant 0 <= i <= v.Length
	invariant forall k :: 0 <= k < i ==> m >= v[k]
	invariant m in v[..i]
	decreases v.Length - i
	{
		if (m < v[i]) {m := v[i];}
		i := i+1;
	}
}


