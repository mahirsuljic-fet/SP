#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack destructor") {
  Stack<int> stack;
  stack.push(2).push(3);
  stack.~Stack();
  CHECK(stack.empty());
  CHECK(stack.size() == 0);
  CHECK(stack.capacity() == 0);
}

