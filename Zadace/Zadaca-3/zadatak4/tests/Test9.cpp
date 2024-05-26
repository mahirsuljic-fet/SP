#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue front function") {
  Queue<int> q;
  q.push(1).push(2).push(3);

  int& x = q.front();
  CHECK(x == 1);

  x = 4;
  CHECK(q.front() == 4);

  // Try getting the front element of an empty queue - this should throw an
  // exception
  Queue<std::string> q2;
  CHECK_THROWS(q2.front());
}
