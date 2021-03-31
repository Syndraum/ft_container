#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> mydeck (3,100);        // deque with 3 elements
  std::list<int> mylist (2,200);         // list with 2 elements

  queue<int> first;                 // empty queue
//   queue<int> second (mydeck);       // queue initialized to copy of deque

  queue<int,std::list<int> > third; // empty queue with list as underlying container
//   queue<int,std::list<int> > fourth (mylist);

  std::cout << "size of first: " << first.size() << '\n';
//   std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
//   std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}