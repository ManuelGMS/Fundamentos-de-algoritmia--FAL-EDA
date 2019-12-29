#include <vector>
#include <fstream>
#include <iostream>

/*
 * Complejidad: O(log(n))
 *
 * Coste:
 *
 * 		T(n) = {
 *
 * 			c 			Si (left+1==right) v (left==right)
 *
 * 			T(n/2) + c 	En cualquier otro caso.
 *
 * 		}
 *
 */

int binarySearchLeft(const std::vector<int>& data, const int& search, const int& left, const int& right) {

	if(left == right)

		return (data[left] == search)? left : data.size();

	else if(left+1 == right)

		if(data[left] == search)

			return left;

		else if(data[right] == search)

			return right;

		else

			return data.size();

	else {

		int middle = (right + left) / 2;

		if(search <= data[middle])

			return binarySearchLeft(data,search,left,middle);

		else

			return binarySearchLeft(data,search,middle+1,right);

	}

}

int binarySearchRight(const std::vector<int>& data, const int& search, const int& left, const int& right) {

	if(left == right)

		return (data[left] == search)? left : data.size();

	else if(left+1 == right)

		if(data[right] == search)

			return right;

		else if(data[left] == search)

			return left;

		else

			return data.size();

	else {

		int middle = (right + left) / 2;

		if(search >= data[middle])

			return binarySearchRight(data,search,middle,right);

		else

			return binarySearchRight(data,search,left,middle-1);

	}

}

bool resuelveCaso() {

	int size;
	int search;

	std::cin >> size >> search;

	if(!std::cin)

		return false;

	std::vector<int> data(size);

	for(int& i : data)

		std::cin >> i;

	size_t left = binarySearchLeft(data,search,0,data.size()-1);

	if(left == data.size())

		std::cout << "NO EXISTE" << std::endl;

	else {

		size_t right = binarySearchRight(data,search,0,data.size()-1);

		if(left == right)

			std::cout << left << std::endl;

		else

			std::cout << left << " " << right << std::endl;

	}

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
