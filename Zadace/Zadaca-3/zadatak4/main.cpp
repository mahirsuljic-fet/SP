#include "Queue.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  Queue<int> queue;

  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);

  while (!queue.empty())
    std::cout << queue.pop() << std::endl;

  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(1);
  queue.push(2);
  queue.push(3);

  Queue<int> queue2 = queue;
  Queue<int> queue3 = queue;

  std::cout << "Queue1" << std::endl;
  while (!queue.empty())
    std::cout << queue.pop() << std::endl;

  std::cout << "queue2" << std::endl;
  while (!queue2.empty())
    std::cout << queue2.pop() << std::endl;

  queue2 = queue3;

  std::cout << "queue2 op=" << std::endl;
  while (!queue2.empty())
    std::cout << queue2.pop() << std::endl;

  return 0;
}
