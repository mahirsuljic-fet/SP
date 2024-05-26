#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Stack.hpp"

TEST_CASE("Stack copy assignment operator") {
  Stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  Stack<int> copy;
  copy = original;
  CHECK(copy.size() == original.size());
  CHECK(copy.top() == original.top());
}
