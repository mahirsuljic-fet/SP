#include "binary.hpp"
#include <cstdint>
#include <iostream>

int main(int argc, char* argv[])
{
  Binary<int16_t> a, b;

  std::cout << "Unesite prvi binarni broj (<= " << a.str().size() << " bit): ";
  std::cin >> a;

  std::cout << "Unesite drugi binarni broj (<= " << b.str().size() << " bit): ";
  std::cin >> b;

  std::cout << std::endl;
  std::cout << a.str() << " + " << b.str() << " = "
            << " = " << (a + b).str() << " | " << a.val() << " + " << b.val() << " = " << (a + b).val() << std::endl;
  std::cout << a.str() << " - " << b.str() << " = "
            << " = " << (b - a).str() << " | " << a.val() << " - " << b.val() << " = " << (a - b).val() << std::endl;
  std::cout << a.str() << " * " << b.str() << " = "
            << " = " << (a * b).str() << " | " << a.val() << " * " << b.val() << " = " << (a * b).val() << std::endl;
  std::cout << a.str() << " / " << b.str() << " = "
            << " = " << (b / a).str() << " | " << a.val() << " / " << b.val() << " = " << (a / b).val() << std::endl;
  std::cout << (a++).val() << " -> " << a.val() << std::endl;
  std::cout << (++a).val() << " -> " << a.val() << std::endl;
  std::cout << (a--).val() << " -> " << a.val() << std::endl;
  std::cout << (--a).val() << " -> " << a.val() << std::endl;

  std::cout << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  return 0;
}
