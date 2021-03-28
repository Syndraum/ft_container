#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  map<char,int> mymap;
  mymap['a']=101;
  mymap['b']=202;
  mymap['c']=302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';

  return 0;
}