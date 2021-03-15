#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int>::size_type sz;

  vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << std::boolalpha << (sz <= bar.capacity()) << '\n';
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
  }

  try
  {
	bar.reserve(bar.max_size() * 2);
  }
  catch(std::length_error& e)
  {
	  std::cout << "Exception !\n" << e.what();
  }
  return 0;
}