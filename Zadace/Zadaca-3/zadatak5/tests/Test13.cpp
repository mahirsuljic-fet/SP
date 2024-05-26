#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Stack.hpp"
#include "doctest.h"

TEST_CASE("Testing Stack::resize()") {
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  SUBCASE("Testing Stack::resize()") {
    // Resize the stack to a smaller size
    s.resize(2);
    CHECK(s.size() == 2);
    CHECK(s.top() == 2);

    // Resize the stack to a larger size
    s.resize(5);
    CHECK(s.size() == 5);
    CHECK(s.top() == 0);
  }
}
