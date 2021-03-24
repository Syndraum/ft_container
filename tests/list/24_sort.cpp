#include "test_utils.hpp"

using namespace NAMESPACE;

#include <cctype>

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int main ()
{
  list<std::string> mylist;
  list<std::string>::iterator sit;
  mylist.push_back ("one");
  mylist.push_back ("two");
  mylist.push_back ("Three");

	list<int> myList;
	list<int>::iterator it;
	myList.push_front(1);
	myList.push_front(3);
	myList.push_front(42);
	myList.push_back(5);
	myList.push_back(767);
	myList.push_back(12);

  myList.sort();
  mylist.sort();

	std::cout << "mylist contains:";
  for (sit=mylist.begin(); sit!=mylist.end(); ++sit)
    std::cout << ' ' << *sit;
  std::cout << '\n';

  std::cout << "myList contains:";
  for (it=myList.begin(); it!=myList.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  mylist.sort(compare_nocase);

  std::cout << "mylist contains:";
  for (sit=mylist.begin(); sit!=mylist.end(); ++sit)
    std::cout << ' ' << *sit;
  std::cout << '\n';

  return 0;
}