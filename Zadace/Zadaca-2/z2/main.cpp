#include "Polinom.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main()
{
  std::string poli;

  // redoslijed monoma i razmaci unutar polinoma nisu bitni
  std::cout << "Unesite prvi polinom (a+bx+cx^2+...): ";
  std::getline(std::cin, poli);

  Polinom<double> p1 { poli };

  std::cout << "Unesite drugi polinom (a+bx+cx^2+...): ";
  std::getline(std::cin, poli);

  Polinom<double> p2 { poli };

  std::cout << std::fixed << std::setprecision(2);

  std::cout << std::endl;
  std::cout << "P1(x) = " << p1 << std::endl;
  std::cout << "P2(x) = " << p2 << std::endl;
  std::cout << std::endl;
  std::cout << "P1(x) + P2(x) = " << (p1 + p2) << std::endl;
  std::cout << "P1(x) - P2(x) = " << (p1 - p2) << std::endl;
  std::cout << "P1(x) * P2(x) = " << (p1 * p2) << std::endl;
  std::cout << "P1(x)' = " << p1.derivative() << std::endl;
  std::cout << "P2(x)' = " << p2.derivative() << std::endl;
  std::cout << std::endl;

  auto p1_derivative = p1.derivative();
  for (int i = -10; i <= 10; ++i)
    std::cout << "P1(" << i << ")\t= " << p1(i) << "\t       P1'(" << i << ")\t= " << p1_derivative(i) << std::endl;

  return 0;
}
