#include "duration.hpp"
#include <iostream>

int main()
{
  Duration d;
  std::cin >> d;
  std::cout << (d * 2) << std::endl;
  std::cout << (d / 2) << std::endl;
  std::cout << ((d * 2) + d) << std::endl;
  std::cout << ((d * 2) - d) << std::endl;
}
