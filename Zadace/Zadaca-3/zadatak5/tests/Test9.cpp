#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack capacity") {
  Stack<int> stack;
  CHECK(stack.capacity() > 0);

  for (int i = 1; i <= 100; ++i) {
    stack.push(i);
    CHECK(stack.capacity() >= stack.size());
  }
}
