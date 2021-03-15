#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector(10);
  int sum (0);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}