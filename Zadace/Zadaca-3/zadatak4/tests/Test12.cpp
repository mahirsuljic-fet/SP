#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue clear function") {
  Queue<int> q;
  q.push(1).push(2).push(3);
  CHECK(q.size() == 3);

  q.clear();
  CHECK(q.size() == 0);
  CHECK(q.empty());

  // Try clearing an already empty queue - this should not cause any issues
  q.clear();
  CHECK(q.size() == 0);
  CHECK(q.empty());
}
