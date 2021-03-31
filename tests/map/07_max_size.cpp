#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  int i;
  map<int,int> mymap;
  std::map<int,int> cmp;

  if (mymap.max_size()>1000)
  {
    for (i=0; i<1000; i++) mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else std::cout << "The map could not hold 1000 elements.\n";

  if (mymap.max_size() > (cmp.max_size() - 1000) && mymap.max_size() < (cmp.max_size() + 1000))
    std::cout << "max size : OK" << std::endl;
  else
    std::cout << "max size : KO" << std::endl;
  

  return 0;
}