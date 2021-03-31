#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> mylist(100);
  std::list<int> cmp;

  std::cout << "size: " << mylist.size() << "\n";
  if (mylist.max_size() > (cmp.max_size() - 1000) && mylist.max_size() < (cmp.max_size() + 1000))
    std::cout << "max size : OK" << std::endl;
  else
    std::cout << "max size : KO" << std::endl;

  list<std::string> mylist_str(4);
  std::list<std::string> cmp_str;

  std::cout << "size: " << mylist_str.size() << "\n";
  if (mylist_str.max_size() > (cmp_str.max_size() - 1000) && mylist_str.max_size() < (cmp_str.max_size() + 1000))
    std::cout << "max size : OK" << std::endl;
  else
    std::cout << "max size : KO" << std::endl;

  return 0;
}