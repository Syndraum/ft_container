#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  int myints[] = {75,23,65,42,13};
  list<int> mylist (myints,myints+5);

  std::cout << "mylist contains:";
  for (list<int>::iterator it=mylist.begin() ; it != mylist.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}