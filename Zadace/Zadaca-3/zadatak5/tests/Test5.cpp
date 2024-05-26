#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack move assignment operator") {
  Stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  Stack<int> moved;
  moved = std::move(original);
  CHECK(original.empty());
  CHECK(moved.size() == 3);
  CHECK(moved.top() == 3);
}
