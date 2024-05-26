#include "Queue.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  Queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  test(queue);
  while (!queue.empty())
    std::cout << queue.pop() << std::endl;
  std::cout << "CLEARED\n";
  queue.push(1);
  // test(queue);
  queue.push(2);
  // test(queue);
  queue.push(3);
  // test(queue);
  queue.push(1);
  // test(queue);
  queue.push(2);
  // test(queue);
  queue.push(3);
  // test(queue);
  queue.push(1);
  // test(queue);
  queue.push(2);
  // test(queue);
  queue.push(3);
  // test(queue);
  while (!queue.empty())
    std::cout << queue.pop() << std::endl;

  return 0;
}
