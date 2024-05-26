#include "Stack.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  Stack<double> myStack;
  myStack.push(2.5).push(3.5).push(5.5).push(10.01);

  try
  {
    std::cout << "Top element: " << myStack.top() << std::endl;
    myStack.pop();
    std::cout << "Top element after pop: " << myStack.top() << std::endl;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "Elements" << std::endl;
  std::cout << std::string(30, '-') << std::endl;
  while (!myStack.empty())
    std::cout << myStack.pop() << " ";
  std::cout << std::endl;

  return 0;
}
