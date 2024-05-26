#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue move constructor") {
  Queue<int> q1;
  q1.push(1).push(2).push(3);

  Queue<int> q2(std::move(q1));

  CHECK(q1.empty());
  CHECK(q2.size() == 3);
  CHECK(q2.capacity() >= 3);

  CHECK(q2.front() == 1);
  q2.pop();
  CHECK(q2.front() == 2);
  q2.pop();
  CHECK(q2.front() == 3);
}
