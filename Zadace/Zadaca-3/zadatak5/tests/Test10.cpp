#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack empty") {
  Stack<int> stack;
  CHECK(stack.empty());

  stack.push(1);
  CHECK(!stack.empty());

  stack.pop();
  CHECK(stack.empty());
}
