#include "stack.hpp"

#include <iostream>
#include <stdexcept>

// Napisati program koji provjerava da li su zagrade u izrazu balansirane

bool matching()
{
  Stack<char> zagrade;
  char c;
  while (std::cin >> c)
  {
    if (c == '(' || c == '[')
      zagrade.push(c);
    else if (c == ')')
    {
      if (zagrade.empty()) return false;
      if (zagrade.top() != '(')
        return false;
      zagrade.pop();
    }
    else if (c == ']')
    {
      if (zagrade.empty()) return false;
      if (zagrade.top() != '[')
        return false;
      zagrade.pop();
    }
  }
  return zagrade.empty();
}

int main()
{
  if (matching())
    std::cout << "Zagrade su pravilno rasporedene" << std::endl;
  else
    std::cout << "Zagrade nisu pravilno rasporedene" << std::endl;
  return 0;
}
