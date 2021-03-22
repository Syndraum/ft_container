#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> mylist(100);

  std::cout << "size: " << mylist.size() << "\n";
  std::cout << "max_size: " << mylist.max_size() << "\n";

  list<std::string> mylist_str(4);

  std::cout << "size: " << mylist_str.size() << "\n";
  std::cout << "max_size: " << mylist_str.max_size() << "\n";

  return 0;
}