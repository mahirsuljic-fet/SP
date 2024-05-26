#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue default constructor") {
  Queue<int> q;
  CHECK(q.size() == 0);
  CHECK(q.capacity() == 10);
  CHECK(q.empty());
}
