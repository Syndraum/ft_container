#include "test_utils.hpp"

using namespace NAMESPACE;

// template < typename T>
// void print_list(list<T> & list) {
// 	std::cout << "front : " << list.front() << "\tback : " << list.back() << "\tsize : " << list.size() << "\n";
// }

template < typename T>
void print_list(list<T> & myList) {
	std::cout << "front : " << myList.front() << "\tback : " << myList.back() << "\tsize : " << myList.size() << "\n";
	for (typename list<T>::iterator it = myList.begin(); it != myList.end() ; it++)
			std::cout << *it << " | ";
	std::cout << "\n";
}

bool single_digit (const int& value) { return (value<10); }

int main() {
	list<int> myList;
	myList.push_front(1);
	print_list(myList);
	myList.push_front(3);
	print_list(myList);
	myList.push_front(42);
	print_list(myList);
	myList.pop_front();
	myList.push_back(5);
	print_list(myList);
	
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

	print_list(myList);

	for (list<int>::reverse_iterator rit = myList.rbegin(); rit != myList.rend() ; rit++)
		std::cout << *rit << std::endl;
	
	std::cout << "Iterator LIst :\n";
	list<int> itList(myList.begin(), myList.end());
	print_list(itList);

	itList.assign(2, 42);
	print_list(itList);
	itList.assign(5, 20);
	print_list(itList);
	itList.assign(myFillList.begin(), myFillList.end());
	print_list(itList);

	list<int>::iterator retIt = itList.insert(itList.begin(), 42);
	print_list(itList);
	std::cout << *retIt << std::endl;

	itList.insert(++itList.begin(), 4, 0);
	print_list(itList);

	itList.insert(++itList.begin(), 5);
	print_list(itList);

	retIt = itList.erase(itList.begin());
	print_list(itList);
	std::cout << *retIt << std::endl;

	retIt = itList.erase(itList.begin(), --itList.end());
	print_list(itList);
	std::cout << *retIt << std::endl;

	itList.swap(myFillList);
	print_list(itList);
	print_list(myFillList);

	list<int>::iterator	it = itList.begin();
	it++;

	// itList.splice(it, myList, myList.begin(), myList.end());
	// itList.splice(it, myList);
	// itList.splzice(it, myList, (myList.begin())++ );
	print_list(itList);
	print_list(myList);

	itList.remove(67);
	print_list(itList);

	int myints[]= {15,36,7,17,20,39,4,1};
	list<int> mylist (myints,myints+8);
	mylist.remove_if (single_digit);
	print_list(mylist);

	int myints2[]= {1,1,1,17,20,39,4,4,1};
	list<int> mylist2 (myints2,myints2+9);
	mylist2.unique();
	print_list(mylist2);

	// list<int> copyList;
	// copyList = myList;
	// list<int>::const_iterator cit = myList.begin();
	// std::cout << *cit << std::endl;
	// for (list<int>::iterator it = copyList.begin(); it != copyList.end() ; it++)
	// 	std::cout << *it << std::endl;

	return 0;
}