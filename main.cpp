#include "list.hpp"
#include "vector.hpp"
#include <iostream>

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
}