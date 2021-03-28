#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

//   while (!mymap.empty())
//   {
//     std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
//     mymap.erase(mymap.begin());
//   }

  return 0;
}