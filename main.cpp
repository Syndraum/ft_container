#include "list.hpp"
#include "vector.hpp"
#include <iostream>
#include <string>

int main(){
	ft::vector<int> list;
	list.push_back(9);
	list.push_back(2);
	list.push_back(3);
	list.push_back(5);
	list.push_back(1);
	list.push_back(0);
	list.push_back(6);
	list.push_back(7);
	list.push_back(42);
	list.print();
	list.assign(3, 3);
	list.print();
	list.resize(2);
	list.print();
	list.resize(6);
	list.print();

	ft::vector< std::string > list_str(5, "test");
	list_str.print();
	list_str.push_back("bonjour");
	list_str.resize(9);
	list_str.print();
	list_str.assign(3, "none");
	list_str.print();
	list_str.resize(1);
	list_str.print();
	list_str.reserve(3);
	list_str.print();
	list_str.reserve(17);
	list_str.print();

	list.pop_back();
	list.print();
	const int &test = list.back();
	std::cout << list.front() << ", " << test << std::endl;
	list.clear();
	list.print();
	ft::vector<int> list_cpy(4, 5);
	list.swap(list_cpy);
	list.print();
	ft::swap(list_cpy, list);
	list.print();
	ft::swap(list_cpy, list);
	ft::vector<int>::iterator it = list.begin();

	std::cout << std::boolalpha << "!= " << (list != list_cpy) << std::endl;
	std::cout << std::boolalpha << "== " << (list == list) << std::endl;
	std::cout << "empty ? " << list.empty() << std::endl;
	std::cout << "begin : " << *it << std::endl;
	std::cout << "== " << (it == list.begin()) << std::endl;
	int i = 0;
	for (ft::vector<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << i << " : " << *it << std::endl;
		i++;
	}
	
}