#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  vector<int> myints2 (100);
  std::cout << "1. size: " << myints2.size() << '\n';

  return 0;
}