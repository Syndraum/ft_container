#include "test_utils.hpp"

using namespace NAMESPACE;

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int main ()
{
  list<double> first, second;

  first.push_back (3.1);
  first.push_back (2.2);
  first.push_back (2.9);

  second.push_back (3.7);
  second.push_back (7.1);
  second.push_back (1.4);

  first.sort();
  second.sort();

	std::cout << "first contains:";
  for (list<double>::iterator it=first.begin(); it!=first.end(); ++it){
    std::cout << ' ' << *it;
  }
  std::cout << '\n';
  std::cout << "seconde contains:";
  for (list<double>::iterator it=second.begin(); it!=second.end(); ++it){
    std::cout << ' ' << *it;
  }
  std::cout << '\n';

  first.merge(second);

  // (second is now empty)

  second.push_back (2.1);

  first.merge(second,mycomparison);

  std::cout << "first contains:";
  for (list<double>::iterator it=first.begin(); it!=first.end(); ++it){
    std::cout << ' ' << *it;
  }
  std::cout << '\n';
  return 0;
}