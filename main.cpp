#include "list.hpp"
#include "vector.hpp"
#include <iostream>
#include <string>

int main(){
	ft::list<int> myList;
	myList.push_front(1);
	myList.push_front(3);
	myList.push_front(42);
	
	ft::list<int>::iterator it = myList.begin();
	ft::node<int> * node = it.getNode();
	std::cout << "data : " << node->data << std::endl;
	std::cout << "previous : " << node->previous << std::endl;

	node->data = 2;
	std::cout << "data : " << node->data << std::endl;
	std::cout << "previous : " << node->previous << std::endl;

	ft::node<const int> * cnode = reinterpret_cast<ft::node<const int> *>(&node);
	std::cout << "data : " << cnode->data << std::endl;
	std::cout << "previous : " << cnode->previous << std::endl;

	ft::list<int>::const_iterator cit = myList.begin();
	std::cout << "data : " << *cit << std::endl;
	std::cout << "previous : " << cit.getNode()->previous << std::endl;
}