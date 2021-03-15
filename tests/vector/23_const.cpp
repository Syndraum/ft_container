#include "utils.hpp"

using namespace NAMESPACE;

int main()
{
	vector<int> myvector(2, 100);
	return (0);
	
	vector<int>::const_iterator cit = myvector.begin();
	std::cout << *cit << std::endl;
	
}