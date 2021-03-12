#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  vector<std::string> myvector_str;
  sum = 0;
  myvector_str.push_back ("TEST");
  myvector_str.push_back ("bnfjbjkwf");

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}