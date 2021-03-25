#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> first (3,100);   // three ints with a value of 100
  list<int> second (5,200);  // five ints with a value of 200
  list<int> empty;

  first.swap(second);

  std::cout << "first contains:";
  for (list<int>::iterator it=first.begin(); it!=first.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "second contains:";
  for (list<int>::iterator it=second.begin(); it!=second.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  first.swap(empty);
  std::cout << "NIQUE" << std::endl;
  first.swap(empty);

  std::cout << "first contains:";
  for (list<int>::iterator it=first.begin(); it!=first.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "empty contains:";
  for (list<int>::iterator it=empty.begin(); it!=empty.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}