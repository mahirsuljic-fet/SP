#include "Map.hpp"
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main()
{
  Map<int, int> map;

  auto line = []() { std::cout << std::string(60, '-') << std::endl; };

  auto add = [&map](int n) {
    std::cout << "ADDING    -> " << std::left << std::setw(2) << n << ": ";
    map[n] = n;
    map.print();
  };

  auto insert = [&map](int n) {
    std::cout << "INSERTING -> " << std::left << std::setw(2) << n << ": ";
    try
    {
      map.insert(n, n);
      map.print();
    }
    catch (const std::exception& err)
    {
      std::cout << err.what() << std::endl;
    }
  };

  auto erase = [&map](int n) {
    std::cout << "ERASING   -> " << std::left << std::setw(2) << n << " " << (map.erase(n) ? "(T)" : "(F)") << ": ";
    map.print();
  };

  add(5);
  add(3);
  add(8);
  add(1);
  add(4);
  insert(7);
  add(6);
  insert(9);
  add(12);
  insert(10);
  add(11);
  insert(13);
  add(13);
  insert(13);

  line();

  erase(9);
  erase(6);
  erase(13);
  erase(3);
  erase(3);

  line();

  map.print();

  return 0;
}
