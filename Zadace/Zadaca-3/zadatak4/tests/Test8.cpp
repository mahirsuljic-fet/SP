#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue pop function") {
  Queue<int> q;
  q.push(1).push(2).push(3);

  int x = q.pop();
  CHECK(x == 1);
  CHECK(q.size() == 2);
  CHECK(q.front() == 2);

  x = q.pop();
  CHECK(x == 2);
  CHECK(q.size() == 1);
  CHECK(q.front() == 3);

  x = q.pop();
  CHECK(x == 3);
  CHECK(q.size() == 0);
  CHECK(q.empty());

  // Try popping from an empty queue - this should throw an exception
  CHECK_THROWS(q.pop());
}
