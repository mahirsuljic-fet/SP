#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Stack.hpp"
#include "doctest.h"

TEST_CASE("Stack operator==") {
  SUBCASE("Two empty stacks are equal") {
    Stack<int> s1, s2;
    CHECK(s1 == s2);
  }

  SUBCASE("Stacks with different sizes are not equal") {
    Stack<int> s1, s2;
    s1.push(1);
    CHECK_FALSE(s1 == s2);
  }

  SUBCASE("Stacks with the same elements are equal") {
    Stack<int> s1, s2;
    s1.push(1);
    s1.push(2);
    s2.push(1);
    s2.push(2);
    CHECK(s1 == s2);
  }

  SUBCASE("Stacks with different elements are not equal") {
    Stack<int> s1, s2;
    s1.push(1);
    s1.push(2);
    s2.push(2);
    s2.push(1);
    CHECK_FALSE(s1 == s2);
  }
}
