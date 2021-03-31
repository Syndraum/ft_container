#include "test_utils.hpp"

using namespace NAMESPACE;

template <typename T>
void	print(T x) {
	std::cout << x << " ";
}

template <typename Iterator>
void	advance(Iterator &it, std::ptrdiff_t n){
	if (n >= 0){
		for (ptrdiff_t i = 0; i < n; i++)
			++it;
	}
	else{
		for (ptrdiff_t i = 0; i > n; i--)
			--it;
	}
}

int main()
{
	list<int> mylist;

	for (size_t i = 0; i < 25; i++)
		mylist.push_back(i * i);

	list<int>::iterator nit = mylist.begin();
	advance(nit, 15);
	list<int>::iterator it = std::find(mylist.begin(), nit, 4);
	if (it != mylist.end())
		std::cout << "find : " << *it << std::endl;
	else
		std::cout << "not find" << std::endl;
	std::cout << "for_each : ";
	std::for_each(mylist.begin(), mylist.end(), print<int>);
	std::cout << "\n";

	std::cout << "copy : ";
	list<int> copy_list(mylist.size());
	std::copy(mylist.begin(), mylist.end(), copy_list.begin());

	std::for_each(copy_list.begin(), copy_list.end(), print<int>);
	std::cout << "\n";

	nit = mylist.begin();
	advance(nit, 4);
	std::fill (mylist.begin(),nit,5);   // mylist: 5 5 5 5 0 0 0 0
	it = mylist.begin();
	advance(nit, 3);
	nit = mylist.end();
	advance(nit, -2);
	std::fill (it,nit,8);   // mylist: 5 5 5 8 8 8 0 0

	std::cout << "mylist contains:";
	for (list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	// std::sort (mylist.begin(), mylist.begin()+4);

	std::cout << "sort : ";
	std::for_each(mylist.begin(), mylist.end(), print<int>);
	std::cout << "\n";
	return 0;
}
