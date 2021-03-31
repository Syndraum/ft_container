#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  list<int> mydeque (3,100);          // deque with 3 elements
  vector<int> myvector (2,200);        // vector with 2 elements

  stack<int> first;                    // empty stack
//   stack<int> second (mydeque);         // stack initialized to copy of deque

  stack<int,vector<int> > third;  // empty stack using vector
//   stack<int,vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
//   std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
//   std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}