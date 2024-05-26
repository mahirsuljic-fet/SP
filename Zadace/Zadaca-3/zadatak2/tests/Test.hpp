#pragma once

#include "../Number.hpp"
#include <cstddef>
class Test
{
  public:
    static void add(size_t combinations = DEFAULT_COMBINATIONS);
    static void sub(size_t combinations = DEFAULT_COMBINATIONS);
    static void mul(size_t combinations = DEFAULT_COMBINATIONS);
    static void exp(size_t combinations = DEFAULT_COMBINATIONS);

  private:
    constexpr static const int NUMW = 10;
    constexpr static const int DEFAULT_COMBINATIONS = 1000000;
    constexpr static const int MAX_ADD_LHS = 100000000;
    constexpr static const int MAX_ADD_RHS = MAX_ADD_LHS;
    constexpr static const int MAX_SUB_LHS = MAX_ADD_LHS;
    constexpr static const int MAX_SUB_RHS = MAX_SUB_LHS;
    constexpr static const int MAX_MUL_LHS = 10000;
    constexpr static const int MAX_MUL_RHS = MAX_MUL_LHS;
    constexpr static const int MAX_EXP_LHS = 35;
    constexpr static const int MAX_EXP_RHS = 6;
    constexpr static const int DEFAULT_TEST_VALUES_SIZE = 9;
    constexpr static const int DEFAULT_TEST_VALUES[DEFAULT_TEST_VALUES_SIZE] = { 0, 1, -1, 2, -2, 5, -5, 10, -10 };

    Test() = delete;
    Test(Test&&) = delete;
    Test(const Test&) = delete;
    Test& operator=(Test&&) = delete;
    Test& operator=(const Test&) = delete;
    ~Test() = delete;

    static void throw_exception(char op, int n1, int n2, Number result);
};
