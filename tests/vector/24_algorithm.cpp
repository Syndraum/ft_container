#include "test_utils.hpp"

using namespace NAMESPACE;

template <typename T>
void	print(T x) {
	std::cout << x << " ";
}

int main()
{
	vector<int> myvector;

	for (size_t i = 0; i < 25; i++)
		myvector.push_back(i * i);

	vector<int>::iterator it = std::find(myvector.begin(), myvector.begin() + 15, 4);
	if (it != myvector.end())
		std::cout << "find : " << *it << std::endl;
	else
		std::cout << "not find" << std::endl;
	std::cout << "for_each : ";
	std::for_each(myvector.begin(), myvector.end(), print<int>);
	std::cout << "\n";

	std::cout << "copy : ";
	vector<int> copy_vector(myvector.size());
	std::copy(myvector.begin(), myvector.end(), copy_vector.begin());

	std::for_each(copy_vector.begin(), copy_vector.end(), print<int>);
	std::cout << "\n";

	std::fill (myvector.begin(),myvector.begin()+4,5);   // myvector: 5 5 5 5 0 0 0 0
	std::fill (myvector.begin()+3,myvector.end()-2,8);   // myvector: 5 5 5 8 8 8 0 0

	std::cout << "myvector contains:";
	for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	std::sort (myvector.begin(), myvector.begin()+4);

	std::cout << "sort : ";
	std::for_each(myvector.begin(), myvector.end(), print<int>);
	std::cout << "\n";

  return 0;
}