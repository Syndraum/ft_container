#include "test_utils.hpp"

using namespace NAMESPACE;

int main()
{
	vector<int> myvector(10);

	for (size_t i = 0; i < myvector.size(); i++){
		myvector[i] = i * i;
	}
	
	vector<int>::const_iterator cit = myvector.begin();
	std::cout << *cit << std::endl;
	vector<int>::const_iterator cit_copy(cit);
	std::cout << *cit_copy << std::endl;


	std::cout << std::boolalpha << (cit == cit_copy) << std::endl;
	std::cout << std::boolalpha << (cit != cit_copy) << std::endl;

	vector<int>::const_iterator cit2 = cit + 3;
	std::cout << *cit2 << std::endl;

	std::cout << "it + 3 : " << *(cit2 + 3) << std::endl;
	std::cout << "2 + it : "<< *(2 + cit2) << std::endl;
	std::cout << "it - 2 : " << *(cit2 - 2) << std::endl;
	std::cout << "it - it_copy : " << cit2 - cit_copy << std::endl;

	std::cout << std::boolalpha << (cit <= cit_copy) << std::endl;
	std::cout << std::boolalpha << (cit >= cit_copy) << std::endl;
	std::cout << std::boolalpha << (cit < cit_copy) << std::endl;
	std::cout << std::boolalpha << (cit > cit_copy) << std::endl;

	for (size_t i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << std::endl;
	}

	return (0);
}