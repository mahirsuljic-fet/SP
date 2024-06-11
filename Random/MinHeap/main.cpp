#include "MinHeap.hpp"
#include <iostream>

int main()
{
  using Heap = MinHeap<int>;

  auto line = []() { std::cout << std::string(30, '-') << std::endl; };

  std::cout << "DEFAULT CONSTRUCTOR" << std::endl
            << "this  -> " << Heap {} << std::endl;
  line();

  Heap list { 1, 2, 3 };
  std::cout << "INITIALIZER LIST CONSTRUCTOR" << std::endl
            << "this  -> " << list << std::endl;
  line();

  Heap copy { list };
  std::cout << "COPY CONSTRUCTOR" << std::endl
            << "this  -> " << copy << std::endl
            << "other -> " << list << std::endl;
  line();

  Heap move { std::move(copy) };
  std::cout << "MOVE CONSTRUCTOR" << std::endl
            << "this  -> " << move << std::endl
            << "other -> " << copy << std::endl;
  line();

  copy = list;
  std::cout << "COPY OPERATOR=" << std::endl
            << "this  -> " << copy << std::endl
            << "other -> " << list << std::endl;
  line();

  move = std::move(copy);
  std::cout << "MOVE OPERATOR=" << std::endl
            << "this  -> " << move << std::endl
            << "other -> " << copy << std::endl;
  line();

  list = { 5, 6, 3, 8, 9, 10, 3, 7 };
  std::cout << "MOVE OPERATOR= (list)" << std::endl
            << "this  -> " << list << std::endl;
  line();

  int n = 0;
  list.push(n);
  std::cout << "PUSHING -> " << n << std::endl
            << "this  -> " << list << std::endl;
  line();

  n = 11;
  list.push(n);
  std::cout << "PUSHING -> " << n << std::endl
            << "this  -> " << list << std::endl;
  line();

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  std::cout << "REMOVING -> " << list.pop_min() << std::endl;
  std::cout << list << std::endl;

  return 0;
}
