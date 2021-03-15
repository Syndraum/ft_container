#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> foo (3);
  vector<int> bar (5);

  bar = foo;
  foo = vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}