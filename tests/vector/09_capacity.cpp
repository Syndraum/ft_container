#include "utils.hpp"

using namespace NAMESPACE;

int	main()
{
	vector<int> myvector (4);
	std::cout << std::boolalpha << (myvector.capacity() >= myvector.size()) << std::endl;

	vector<int> myvector2 (100);
	std::cout << std::boolalpha << (myvector2.capacity() >= myvector2.size()) << std::endl;

	return 0;
}