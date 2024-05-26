#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue destructor") {
  Queue<int> q;
  q.push(1).push(2).push(3);
  q.~Queue();
//   CHECK(q.size() == 0);
}
