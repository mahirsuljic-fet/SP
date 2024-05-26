#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack size") {
  Stack<int> stack;
  CHECK(stack.size() == 0);
  stack.push(1);
  CHECK(stack.size() == 1);
  stack.push(2);
  CHECK(stack.size() == 2);
  stack.push(3);

  CHECK(stack.size() == 3);
  stack.pop();
  CHECK(stack.size() == 2);
  stack.pop();
  CHECK(stack.size() == 1);
}
