#include "test_utils.hpp"

using namespace NAMESPACE;

template < typename T>
void print_list(list<T> & list) {
	std::cout << "front : " << list.front() << "\tback : " << list.back() << "\tsize : " << list.size() << "\n";
}

int main() {
	list<int> myList;
	myList.push_front(3);
	print_list(myList);
	myList.push_front(42);
	print_list(myList);
	myList.push_front(5);
	print_list(myList);
	myList.pop_front();
	myList.push_back(7);
	myList.push_back(767);
	myList.push_back(0);
	print_list(myList);
	myList.pop_back();
	print_list(myList);
	myList.resize(20, 42);
	print_list(myList);
	myList.resize(2, 42);
	print_list(myList);

	list<int> myFillList(4, 67);
	print_list(myFillList);

	for (list<int>::iterator it = myList.begin(); it != myList.end() ; it++)
	{
		std::cout << *it << std::endl;
	}

	list<int>::iterator it = myList.begin();
	it++;
	it--;
	std::cout << *it << std::endl;
	for (list<int>::reverse_iterator rit = myList.rbegin(); rit != myList.rend() ; rit++)
	{
		std::cout << *rit << std::endl;
	}
	

	return 0;
}