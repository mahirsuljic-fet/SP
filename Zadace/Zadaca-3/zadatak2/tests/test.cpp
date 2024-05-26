#include "Test.hpp"
#include <exception>
#include <iostream>

int main()
{
  try
  {
    Test::add();
    Test::sub();
    Test::mul();
    Test::exp();
    std::system("clear");
    std::cout << "All tests passed successfully." << std::endl;
  }
  catch (const std::exception& err)
  {
    std::system("clear");
    std::cout << err.what() << std::endl;
  }

  return 0;
}
