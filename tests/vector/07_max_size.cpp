#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  vector<int> myvector(100);
  std::vector<int> cmp(100);

  std::cout << "size: " << myvector.size() << "\n";
  if (myvector.max_size() > (cmp.max_size() - 1000) && myvector.max_size() < (cmp.max_size() + 1000))
    std::cout << "max size : OK" << std::endl;
  else
    std::cout << "max size : KO" << std::endl;
//   std::cout << "max_size: " << myvector.max_size() << "\n";

  vector<std::string> myvector_str(4);
  std::vector<std::string> cmp_str(4);

  std::cout << "size: " << myvector_str.size() << "\n";
  if (myvector_str.max_size() > (cmp_str.max_size() - 1000) && myvector_str.max_size() < (cmp_str.max_size() + 1000))
    std::cout << "max size : OK" << std::endl;
  else
    std::cout << "max size : KO" << std::endl;
//   std::cout << "max_size: " << myvector_str.max_size() << "\n";
  return 0;
}