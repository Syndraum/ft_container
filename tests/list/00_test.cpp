#include "test_utils.hpp"

using namespace NAMESPACE;

template < typename T>
void print_list(list<T> & myList) {
	std::cout << "front : " << myList.front() << "\tback : " << myList.back() << "\tsize : " << myList.size() << "\n";
	for (typename list<T>::iterator it = myList.begin(); it != myList.end() ; it++)
			std::cout << *it << " | ";
	std::cout << "\n";
}

int main() {
	list<int> myList;
	myList.push_front(1);
	myList.push_front(3);
	myList.push_front(42);
	myList.pop_front();
	myList.push_back(5);
	myList.push_back(767);
	myList.pop_back();
	myList.resize(20, 42);
	myList.resize(2, 42);

	// list<int> copyList;
	// copyList = myList;
	// list<int>::const_iterator cit = myList.begin();
	// std::cout << *cit << std::endl;
	// list<int>::const_iterator it = myList.begin();
	// std::cout << "data : " << *it << std::endl;
	// std::cout << "previous : " << it.getNode()->previous << std::endl;
	for (list<int>::const_iterator it = myList.begin(); it != myList.end() ; it++)
		std::cout << *it << std::endl;

	return 0;
}