#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  int myints[]= {17,89,7,14};
  list<int> mylist (myints,myints+4);

  mylist.remove(89);

  std::cout << "mylist contains:";
  for (list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}