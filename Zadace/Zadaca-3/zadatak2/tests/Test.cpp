#include "Test.hpp"
#include "../Number.hpp"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void Test::add(size_t combinations)
{
  std::srand(clock());

  int n1 = 0;
  int n2 = 0;
  Number num1;
  Number num2;
  Number result;

  system("clear");
  std::cout << "Testing operator+ ... 0%" << std::endl;

  for (int i = 0; i < DEFAULT_TEST_VALUES_SIZE; ++i)
  {
    n1 = DEFAULT_TEST_VALUES[i];
    num1 = n1;
    for (int j = 0; j < DEFAULT_TEST_VALUES_SIZE; ++j)
    {
      n2 = DEFAULT_TEST_VALUES[j];
      num2 = n2;
      result = num1 + num2;

      if (result != Number { n1 + n2 }) throw_exception('+', n1, n2, result);
    }
  }

  for (int i = 1; i <= combinations; ++i)
  {
    if (i % (combinations / 100) == 0)
    {
      system("clear");
      std::cout << "Testing operator+ ... " << (int)(100 / (combinations / (double)i)) << "%" << std::endl;
    }

    n1 = rand() % MAX_ADD_LHS;
    n2 = rand() % MAX_ADD_RHS;

    n1 *= rand() % 2 ? 1 : -1;
    n2 *= rand() % 2 ? 1 : -1;

    num1 = n1;
    num2 = n2;

    result = num1 + num2;

    if (result != Number { n1 + n2 }) throw_exception('+', n1, n2, result);
  }
}

void Test::sub(size_t combinations)
{
  std::srand(clock());

  int n1 = 0;
  int n2 = 0;
  Number num1;
  Number num2;
  Number result;

  system("clear");
  std::cout << "Testing operator- ... 0%" << std::endl;

  for (int i = 0; i < DEFAULT_TEST_VALUES_SIZE; ++i)
  {
    n1 = DEFAULT_TEST_VALUES[i];
    num1 = n1;
    for (int j = 0; j < DEFAULT_TEST_VALUES_SIZE; ++j)
    {
      n2 = DEFAULT_TEST_VALUES[j];
      num2 = n2;
      result = num1 - num2;

      if (result != Number { n1 - n2 }) throw_exception('-', n1, n2, result);
    }
  }

  for (int i = 1; i <= combinations; ++i)
  {
    if (i % (combinations / 100) == 0)
    {
      system("clear");
      std::cout << "Testing operator- ... " << (int)(100 / (combinations / (double)i)) << "%" << std::endl;
    }

    n1 = rand() % MAX_SUB_LHS;
    n2 = rand() % MAX_SUB_RHS;

    n1 *= rand() % 2 ? 1 : -1;
    n2 *= rand() % 2 ? 1 : -1;

    num1 = n1;
    num2 = n2;

    result = num1 - num2;

    if (result != Number { n1 - n2 }) throw_exception('-', n1, n2, result);
  }
}

void Test::mul(size_t combinations)
{
  std::srand(clock());

  int n1 = 0;
  int n2 = 0;
  Number num1;
  Number num2;
  Number result;

  system("clear");
  std::cout << "Testing operator* ... 0%" << std::endl;

  for (int i = 0; i < DEFAULT_TEST_VALUES_SIZE; ++i)
  {
    n1 = DEFAULT_TEST_VALUES[i];
    num1 = n1;
    for (int j = 0; j < DEFAULT_TEST_VALUES_SIZE; ++j)
    {
      n2 = DEFAULT_TEST_VALUES[j];
      num2 = n2;
      result = num1 * num2;

      if (result != Number { n1 * n2 }) throw_exception('*', n1, n2, result);
    }
  }

  for (int i = 1; i <= combinations; ++i)
  {
    if (i % (combinations / 100) == 0)
    {
      system("clear");
      std::cout << "Testing operator* ... " << (int)(100 / (combinations / (double)i)) << "%" << std::endl;
    }

    n1 = rand() % MAX_MUL_LHS;
    n2 = rand() % MAX_MUL_RHS;

    n1 *= rand() % 2 ? 1 : -1;
    n2 *= rand() % 2 ? 1 : -1;

    num1 = n1;
    num2 = n2;

    result = num1 * num2;

    if (result != Number { n1 * n2 }) throw_exception('*', n1, n2, result);
  }
}

void Test::exp(size_t combinations)
{
  std::srand(clock());

  int n1 = 0;
  short n2 = 0;
  Number num1;
  Number num2;
  Number result;

  system("clear");
  std::cout << "Testing operator^ ... 0%" << std::endl;

  for (int i = 0; i < DEFAULT_TEST_VALUES_SIZE; ++i)
  {
    n1 = DEFAULT_TEST_VALUES[i];

    if (n1 < 0) continue;

    num1 = n1;
    for (int j = 0; j < DEFAULT_TEST_VALUES_SIZE; ++j)
    {
      n2 = DEFAULT_TEST_VALUES[j];

      if (n1 > MAX_EXP_LHS || n2 > MAX_EXP_RHS) continue;

      try
      {
        result = num1 ^ n2;
      }
      catch (const std::exception& err)
      {
        continue;
      }
      catch (...)
      {
        std::cout << n1 << "^" << n2 << " -> ERROR" << std::endl;
      }

      if (result != Number { (int)std::pow(n1, n2) }) throw_exception('^', n1, n2, result);
    }
  }

  for (int i = 1; i <= combinations; ++i)
  {
    if (i % (combinations / 100) == 0)
    {
      system("clear");
      std::cout << "Testing operator^ ... " << (int)(100 / (combinations / (double)i)) << "%" << std::endl;
    }

    n1 = rand() % MAX_EXP_LHS;
    n2 = rand() % MAX_EXP_RHS;

    if (n1 == 0 && n2 == 0) continue;

    num1 = n1;

    result = num1 ^ n2;

    if (result != Number { (int)std::pow(n1, n2) }) throw_exception('^', n1, n2, result);
  }
}

void Test::throw_exception(char op, int n1, int n2, Number result)
{
  std::ostringstream oss;
  oss << "Operator" << op << ": " << n1 << " " << op << " " << n2 << " = " << result << " (F)" << std::endl
      << "True result: ";
  switch (op)
  {
  case '+':
    oss << n1 + n2;
    break;
  case '-':
    oss << n1 - n2;
    break;
  case '*':
    oss << n1 * n2;
    break;
  case '^':
    if (n1 == 0 && n2 <= 0)
      oss << "undefined (exception not thrown)";
    else
      oss << (int)std::pow(n1, n2);
    break;
  }
  throw std::runtime_error(oss.str());
}
