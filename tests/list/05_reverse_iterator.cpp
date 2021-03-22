#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> mylist;
  for (int i=1; i<=5; ++i) mylist.push_back(i);

  std::cout << "mylist backwards:";
  for (list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';

  return 0;
}