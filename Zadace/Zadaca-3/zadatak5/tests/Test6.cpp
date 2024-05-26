#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack pop") {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  CHECK(stack.pop() == 3);
  CHECK(stack.pop() == 2);
  CHECK(stack.pop() == 1);
  CHECK(stack.empty());
}

TEST_CASE("Stack pop from empty stack. Exception should be thrown!") {
  Stack<int> stack;
  CHECK_THROWS_AS(stack.pop(), std::out_of_range);
}
