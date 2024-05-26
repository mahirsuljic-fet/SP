#include "PostfixCalc.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

int PostfixCalc::eval(const std::string& expression)
{
  std::istringstream iss(expression);
  std::string unit;

  while (!values_.empty()) values_.pop();

  while (iss >> unit)
  {
    if (unit == "q" || unit == "exit") throw unit;

    if (unit.size() == 1)
    {
      switch (unit[0])
      {
      case '+':
        add();
        break;
      case '-':
        sub();
        break;
      case '*':
        mul();
        break;
      case '/':
        div();
        break;
      case '0' ... '9':
        values_.push(std::stoi(unit));
        break;
      default:
        throw std::invalid_argument("Unos \"" + unit + "\" nije validan");
      }
    }
    else
      values_.push(std::stoi(trim(unit)));
  }

  return values_.top();
}

void PostfixCalc::add()
{
  if (values_.size() < 2) throw std::invalid_argument("Nedostaje operand za operator +");

  int rhs = values_.top();
  values_.pop();
  int lhs = values_.top();
  values_.pop();
  values_.push(lhs + rhs);
}

void PostfixCalc::sub()
{
  if (values_.size() < 2) throw std::invalid_argument("Nedostaje operand za operator -");

  int rhs = values_.top();
  values_.pop();
  int lhs = values_.top();
  values_.pop();
  values_.push(lhs - rhs);
}

void PostfixCalc::mul()
{
  if (values_.size() < 2) throw std::invalid_argument("Nedostaje operand za operator *");

  int rhs = values_.top();
  values_.pop();
  int lhs = values_.top();
  values_.pop();
  values_.push(lhs * rhs);
}

void PostfixCalc::div()
{
  if (values_.size() < 2) throw std::invalid_argument("Nedostaje operand za operator /");

  int rhs = values_.top();
  values_.pop();
  int lhs = values_.top();
  values_.pop();
  values_.push(lhs / rhs);
}

std::string PostfixCalc::trim(const std::string& input)
{
  std::string result;
  for (int i = 0; i < input.size(); ++i)
  {
    switch (input[i])
    {
    case '0' ... '9':
    case '+':
    case '-':
    case '*':
    case '/':
    case ' ':
      result += input[i];
      break;
    default:
      throw std::invalid_argument("Unos \"" + std::string { input[i] } + "\" nije validan");
    }
  }
  return result;
}
