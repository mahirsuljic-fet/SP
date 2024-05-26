#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue size and capacity functions") {
  Queue<int> q;
  CHECK(q.size() == 0);
  CHECK(q.capacity() == 10);

  q.push(1).push(2).push(3);
  CHECK(q.size() == 3);
  CHECK(q.capacity() >= 3);

  q.push(4).push(5).push(6);
  CHECK(q.size() == 6);
  CHECK(q.capacity() >= 6);

  q.pop();
  q.pop();
  CHECK(q.size() == 4);
  CHECK(q.capacity() >= 6);

  q.clear();
  CHECK(q.size() == 0);
  CHECK(q.capacity() >= 6);
}
