#include "PostfixCalc.hpp"
#include <exception>
#include <iostream>
#include <string>

int main()
{
  PostfixCalc calc;
  std::string input;

  std::cout << "Unesite matematicki izraz (postfix notacija): ";
  while (std::getline(std::cin, input))
  {
    try
    {
      std::cout << calc.eval(input) << std::endl;
    }
    catch (const std::exception& err)
    {
      std::cout << err.what() << std::endl;
    }
    catch (const std::string& str)
    {
      break;
    }

    std::cout << std::endl;
    std::cout << "Unesite matematicki izraz (postfix notacija): ";
  }

  return 0;
}
