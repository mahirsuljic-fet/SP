#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack full") {
  Stack<int> stack;
  CHECK(!stack.full());
}
