#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack push with perfect forwarding") {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  CHECK(stack.top() == 3);
  CHECK(stack.size() == 3);

  const int x = 4;
  stack.push(x);
  CHECK(stack.top() == 4);
  CHECK(stack.size() == 4);
}
