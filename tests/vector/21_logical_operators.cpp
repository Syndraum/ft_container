#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> foo (3);   // three ints with a value of 100
  for (size_t i = 0; i < 3; i++)
    foo[i] = 100;
  
  vector<int> bar (2);   // two ints with a value of 200
  for (size_t i = 0; i < 2; i++)
    foo[i] = 200;

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

  return 0;
}