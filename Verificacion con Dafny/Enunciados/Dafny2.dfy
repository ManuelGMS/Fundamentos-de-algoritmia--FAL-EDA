// Busqueda de un elemento en un vector
// x elemento a buscar
// b indica si el elemento existe
method busquedaSecuencial (v : array<int>, x : int) returns (b : bool) 
requires ...
ensures ...
{
	var i := 0; 
	while (i < v.Length && v[i] != x) 
		invariant 0 <= i <= v.Length
		invariant forall k :: 0 <= k < i ==> v[k] != x
		decreases v.Length - i
		{
			 i := i + 1;
		}
		b := (i < v.Length);
}


// Busqueda de un elemento en un vector
// x elemento a buscar
// b indica si el elemento existe
// p es la posicion del elemento si existe, sino el valor puede ser cualquiera
method busquedaSecuencial (v : array<int>, x : int) returns (b : bool, p : int) 
requires ... 
ensures ...
{
	p := 0; b := false;
	while (p < v.Length && v[p] != x) 
		invariant 0 <= p <= v.Length
		invariant forall k :: 0 <= k < p ==> v[k] != x
		decreases v.Length - p
		{
			 p := p + 1;
		}
		b := (p < v.Length);
}

// Comprobar si un vector esta ordenado
method  ordenado (v : array<int>) returns (b : bool)
requires ...
ensures ...
{
	var i := 0; b := true;
	while (i < v.Length - 1 && b) 
	invariant v.Length == 0 || 0 <= i < v.Length
	invariant b == forall x :: 0 <= x  < i < v.Length ==> v[x] <= v[..][x+1]
	decreases v.Length - i
	{
		if (v[i] > v[i+1]) { b := false;}
		i := i+1;
	}
}

// Dados dos vectores a y b con el mismo numero de elementos encontrar 
// la primera posicion en que los elementos no son iguales. 
// Si todos los elementos son iguales se devolvera el numero de elementos
method primeroDistinto (a : array<int>, b : array<int>) returns (r : int)
requires ...
ensures ...
{
	r := 0;
	while (r < a.Length && a[r] == b[r]) 
		invariant 0 <= r <= a.Length 
		invariant forall x :: 0 <= x < r ==> b[x] == a[x]
		decreases  b.Length - r 
		{
			r:= r+1;
		}
} 

