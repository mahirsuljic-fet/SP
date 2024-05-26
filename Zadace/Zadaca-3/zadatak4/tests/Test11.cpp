#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue empty and full functions") {
  Queue<int> q;
  CHECK(q.empty());
  CHECK_FALSE(q.full());

  q.push(1);
  CHECK_FALSE(q.empty());
  CHECK_FALSE(q.full());

  q.push(2).push(3).push(4).push(5).push(6);
  CHECK_FALSE(q.empty());
  CHECK_FALSE(q.full());

  q.pop();
  q.pop();
  q.pop();
  CHECK_FALSE(q.empty());
  CHECK_FALSE(q.full());

  q.pop();
  q.pop();
  q.pop();
  CHECK(q.empty());
  CHECK_FALSE(q.full());
}
