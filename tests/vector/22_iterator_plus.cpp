#include "utils.hpp"

using namespace NAMESPACE;

int main()
{
	vector<int> myvector (10);

	for (unsigned i=0; i<myvector.size(); i++)
		myvector[i] = i * 2;

	vector<int>::iterator it = myvector.begin();
	std::cout << *it << std::endl;
	vector<int>::iterator it_copy(it);
	std::cout << *it_copy << std::endl;

	std::cout << std::boolalpha << (it == it_copy) << std::endl;
	std::cout << std::boolalpha << (it != it_copy) << std::endl;

	std::cout << "++it : " << *(++it) << std::endl;
	std::cout << "it++ : " << *(it++) << std::endl;

	std::cout << "--it : " << *(--it) << std::endl;
	std::cout << "it-- : " << *(it--) << std::endl;

	it = it + 3;
	std::cout << "it + 3 : " << *(it + 3) << std::endl;
	std::cout << "2 + it : "<< *(2 + it) << std::endl;
	std::cout << "it - 2 : " << *(it - 2) << std::endl;
	std::cout << "it - it_copy : " << it - it_copy << std::endl;

	std::cout << std::boolalpha << (it <= it_copy) << std::endl;
	std::cout << std::boolalpha << (it >= it_copy) << std::endl;
	std::cout << std::boolalpha << (it < it_copy) << std::endl;
	std::cout << std::boolalpha << (it > it_copy) << std::endl;

	std::cout << "it += 3 : " << *(it += 3) << std::endl;
	std::cout << "it -= 2 : " << *(it -= 2) << std::endl;
	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	for (size_t i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << std::endl;
	}

	vector<std::string> myvector_str(10, "test");

	vector<std::string>::iterator its = myvector_str.begin();
	std::cout << its->size() << std::endl;
	vector<std::string>::iterator its_copy(its);
	std::cout << *its_copy << std::endl;

	std::cout << std::boolalpha << (its == its_copy) << std::endl;
	std::cout << std::boolalpha << (its != its_copy) << std::endl;

	std::cout << "++its : " << *(++its) << std::endl;
	std::cout << "its++ : " << *(its++) << std::endl;

	std::cout << "--its : " << *(--its) << std::endl;
	std::cout << "its-- : " << *(its--) << std::endl;

	its = its + 1;
	std::cout << "its + 3 : " << *(its + 2) << std::endl;
	// std::cout << *(2 + its) << std::endl;
	std::cout << "its - 2 : " << *(its - 2) << std::endl;
}