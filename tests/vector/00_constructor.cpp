#include "test_utils.hpp"

using namespace NAMESPACE;

int	main()
{
	// constructors used in the same order as described above:
	vector<int> first;                                // empty vector of ints
	vector<int> second (4,100);                       // four ints with value 100
	vector<int> third (second.begin(), second.end());  // iterating through second
	vector<int> fourth (third);

	std::cout << std::endl;
	for (unsigned i=0; i<second.size(); i++)
    	std::cout << ' ' << second.at(i);

	std::cout << std::endl;
	for (unsigned i=0; i<third.size(); i++)
    	std::cout << ' ' << third[i];

	//the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	
	return 0;
}