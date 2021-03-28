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
	mymap['b'] = 0;
	mymap.print();
	std::cout << "d : " << mymap['d'] << "\n";

	ft::map<char, int>::iterator cit = mymap.begin();
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
		std::cout << "[" << it->first << "] : " << it->second << "\n";
	for (size_t i = 1; i < mymap.size(); i++)
		cit++;
	
	for (ft::map<char, int>::iterator it = cit; it != mymap.end(); it--)
		std::cout << "[" << it->first << "] : " << it->second << "\n";

	for (ft::map<char, int>::reverse_iterator rit = mymap.rbegin(); rit != mymap.rend(); rit++)
	std::cout << "[" << rit->first << "] : " << rit->second << "\n";

	ft::map<char, int> mysupermap;
	// ft::pair<char, int> pa('a', 100);
	mysupermap.insert(ft::pair<char, int>('a', 100));
	for (ft::map<char, int>::iterator it = mysupermap.begin(); it != mysupermap.end(); it--)
		std::cout << "[" << it->first << "] : " << it->second << "\n";
	mysupermap.insert(ft::pair<char, int>('a', 200));

	return 0;
}