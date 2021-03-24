#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> first (3);      // list of 3 zero-initialized ints
  list<int> second (5);     // list of 5 zero-initialized ints

  second = first;
  first = list<int>();

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}