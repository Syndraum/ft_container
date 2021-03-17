#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int>			test(3, 3);
  vector<vector<int> >	BOB(5, test);
  std::cout << BOB.size() << std::endl;
  vector<vector<int> >	MIKE(BOB);

  return 0;
}