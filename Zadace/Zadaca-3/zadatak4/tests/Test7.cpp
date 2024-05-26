#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../Queue.hpp"
#include "doctest.h"

TEST_CASE("Queue push function") {
  Queue<int> q;
  q.push(1);
  CHECK(q.size() == 1);
  CHECK(q.front() == 1);

  q.push(2).push(3);
  CHECK(q.size() == 3);
  CHECK(q.front() == 1);

  Queue<std::string> q2;
  q2.push("Hello");
  CHECK(q2.size() == 1);
  CHECK(q2.front() == "Hello");

  q2.push(std::string("world")).push("!");
  CHECK(q2.size() == 3);
  CHECK(q2.front() == "Hello");
}
