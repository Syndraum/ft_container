#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector;
 
  myvector.push_back (0);
  myvector.push_back (42);
  myvector.push_back (50);
  myvector.push_back (9);
  myvector.push_back (2);
  myvector.push_back (3);
  myvector.push_back (5);
  myvector.push_back (1);
  myvector.push_back (0);
  myvector.push_back (6);
  myvector.push_back (7);
  myvector.push_back (42);


  for (unsigned i=0; i<12; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  vector<std::string> myvector_str;
 
  myvector_str.push_back ("test");
  myvector_str.push_back ("bonjour");
  myvector_str.push_back ("Reckt");

  for (unsigned i=0; i<12; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}