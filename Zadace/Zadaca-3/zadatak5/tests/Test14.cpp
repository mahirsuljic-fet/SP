#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Stack.hpp"
#include "doctest.h"

TEST_CASE("Testing Stack::clear()") {
  // Create a stack with some elements
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  SUBCASE("Testing Stack::clear()") {
    const int cap = s.capacity();
    s.clear();
    CHECK(s.empty());
    CHECK(s.capacity() == cap);
  }
}
