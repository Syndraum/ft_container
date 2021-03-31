#include "test_utils.hpp"

using namespace NAMESPACE;

int main ()
{
  queue<int> myqueue;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  myqueue.push (20);
  myqueue.push (42);
  myqueue.push (0);
  myqueue.push (-6);

  std::cout << "myqueue contains: ";
  while (!myqueue.empty())
  {
    std::cout << ' ' << myqueue.front();
    myqueue.pop();
  }
  std::cout << '\n';

  return 0;
}