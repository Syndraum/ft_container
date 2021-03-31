#include "list.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
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

	ft::vector<int> mylist;
	mylist.push_back(1);
	mylist.push_back(42);
	mylist.push_back(3);
	mylist.push_back(0);
	mylist.push_back(-6);

	for (ft::vector<int>::reverse_iterator it = mylist.rbegin(); it != mylist.rend(); it++)
		std::cout << *it << " ";
	std::cout << '\n';

	ft::stack<int> mystack;
	std::cout << "size : " << mystack.size() << "\n";

	// for (ft::vector<int>::const_reverse_iterator cit = mylist.rbegin(); cit != mylist.rend(); cit++)
	// 	std::cout << *cit << " ";
	// std::cout << '\n';

	// ft::map<char, int> const const_map(mymap);

	
	// ft::map<char, int>::iterator it = mymap.begin();
	// ft::map<char, int>::btree_type *node = it.getNode();
	// std::cout << "value : " << node->value->first << "\n";

	// ft::map<char, int>::btree_type const *const_node = it.getNode();
	// std::cout << "value : " << const_node->value->first << "\n";
	// ft::map<char, int>::iterator cit(mymap.begin());
	// std::cout << "value : " << cit->first << "\n";

	return 0;
}