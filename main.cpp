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
	std::cout << std::boolalpha << "!= " << (list != list_cpy) << std::endl;
	std::cout << std::boolalpha << "== " << (list == list) << std::endl;
	std::cout << "empty ? " << list.empty() << std::endl;

	ft::vector<int> list_inc;
	list_inc.push_back(1);
	list_inc.push_back(2);
	list_inc.push_back(3);
	list_inc.push_back(4);
	list_inc.push_back(5);
	list_inc.push_back(6);
	list_inc.push_back(7);
	list_inc.push_back(8);
	ft::vector<int>::iterator it = list_inc.begin();
	std::cout << "begin : " << *it << std::endl;
	std::cout << "== " << (it == list_inc.begin()) << std::endl;
	int i = 0;
	for (ft::vector<int>::iterator it = list_inc.begin(); it != list_inc.end(); it++)
	{
		std::cout << i << " : " << *it << std::endl;
		i++;
	}
	it = list_inc.begin();
	i = 2;
	std::cout << "begin + " << i <<" : " << it[i] << std::endl;
	*(it + i) = 42;
	std::cout << "begin + " << i <<" : " << it[i] << std::endl;
	std::cout << "begin + " << i - 1<<" : " << *((it + i) - 1) << std::endl;
	ft::vector<int>::iterator it2 = it + 2;
	std::cout << it - it2 << std::endl;
	it2 = list_inc.begin();
	it = it2 += 4;
	std::cout << "begin + " << 4 <<" : " << *it << std::endl;
	std::cout << "begin + " << 4 <<" : " << *it2 << std::endl;

}