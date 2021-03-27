#include "list.hpp"
#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <string>

template <class T>
void	print(ft::list<T>& lst)
{
	for (typename ft::list<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';
}

int main(){
	ft::map<char, int> mymap;

	mymap['c'] = 42;
	mymap['a'] = 3;
	mymap['f'] = 1;
	mymap.print();
	return 0;
}