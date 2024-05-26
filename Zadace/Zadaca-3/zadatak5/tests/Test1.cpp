#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack constructor") {
  Stack<int> stack;
  CHECK(stack.empty());
  CHECK(stack.size() == 0);
}

