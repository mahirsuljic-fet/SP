#include <iostream>

#include "rational.hpp"

int main()
{
  Rational a(4,6);
  Rational b(6,2);

  std::cout << a << std::endl << b << std::endl;
  std::cout << a + b << std::endl;

  return 0;
}
