#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../duration.hpp"
#include "doctest.h"

TEST_CASE("Testni kod za konstruktor koji prima string") {
  Duration d1{10, 30, 50};
  Duration d2{10, 30, 5};
  Duration d3{10, 3, 5};
  Duration d4{1, 3, 5};
  Duration d5;

  Duration d;

  d = Duration{"10:30:50"};
  CHECK_EQ(d, d1);

  d = Duration{"10:30:05"};
  CHECK_EQ(d, d2);

  d = Duration{"10:03:05"};
  CHECK_EQ(d, d3);

  d = Duration{"01:03:05"};
  CHECK_EQ(d, d4);

  d = Duration{"00:00:00"};
  CHECK_EQ(d, d5);
}
