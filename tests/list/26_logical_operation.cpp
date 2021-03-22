#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
	int	tab[] = {10, 20, 30};
  list<int> a(10, 20);
  list<int> b(tab, tab+2);
  list<int> c(tab, tab + 3);

  if (a==b) std::cout << "a and b are equal\n";
  if (a==c) std::cout << "a and c are equal\n";
  if (b!=c) std::cout << "b and c are not equal\n";
//   if (b<c) std::cout << "b is less than c\n";
//   if (c>b) std::cout << "c is greater than b\n";
//   if (a<=b) std::cout << "a is less than or equal to b\n";
//   if (a>=b) std::cout << "a is greater than or equal to b\n";

  return 0;
}