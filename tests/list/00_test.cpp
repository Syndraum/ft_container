#include "test_utils.hpp"

using namespace NAMESPACE;

template < typename T>
void print_list(list<T> & myList) {
	std::cout << "front : " << myList.front() << "\tback : " << myList.back() << "\tsize : " << myList.size() << "\n";
	for (typename list<T>::iterator it = myList.begin(); it != myList.end() ; it++)
			std::cout << *it << " | ";
	std::cout << "\n";
}

template <class T>
void	print(list<list<T> >& lst)
{
	for (typename list<list<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename list<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void	print(list<T>& lst)
{
	for (typename list<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
	std::cout << '\n';
}

bool			comp2(int a, int b)
{
	return a < b;
}

int main() {
	list<int>		l;
	list<int>		l2;
	for (int i = 0; i < 30; ++i)
	{
		l.push_back(2147483647);
		l2.push_back(-2147483648);
	}
	l.sort();
	print(l);
	l2.sort(comp2);
	print(l2);
	l.merge(l2);
	print(l);
	// l.unique();
	// print(l);
	// l.reverse();
	// print(l);
	std::cout << std::endl;

	// list<int> copyList;
	// copyList = myList;
	// list<int>::const_iterator cit = myList.begin();
	// std::cout << *cit << std::endl;
	// list<int>::const_iterator it = myList.begin();
	// std::cout << "data : " << *it << std::endl;
	// std::cout << "previous : " << it.getNode()->previous << std::endl;
	// for (list<int>::const_iterator it = myList.begin(); it != myList.end() ; it++)
	// 	std::cout << *it << std::endl;

	return 0;
}