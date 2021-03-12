#include "utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector(100);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";

  vector<std::string> myvector_str(4);

  std::cout << "size: " << myvector_str.size() << "\n";
  std::cout << "max_size: " << myvector_str.max_size() << "\n";
  return 0;
}