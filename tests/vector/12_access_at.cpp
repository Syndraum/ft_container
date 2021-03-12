#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  try
  {
    myvector.at(-1);
  }
  catch(const std::out_of_range& e)
  {
    std::cerr << "out_of_range" << '\n';
  }
  

  return 0;
}