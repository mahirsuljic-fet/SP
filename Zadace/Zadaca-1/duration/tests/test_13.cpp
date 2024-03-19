#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../duration.hpp"
#include "doctest.h"

TEST_CASE("Testni kod za operator>>") {
  Duration d1{10, 30, 50};
  Duration d2{10, 30, 5};
  Duration d3{10, 3, 5};
  Duration d4{1, 3, 5};
  Duration d5;

  Duration d;

  {
    std::stringstream ss{"10:30:50"};
    ss >> d;
    CHECK_EQ(d, d1);
  }

  {
    std::stringstream ss{"10:30:05"};
    ss >> d;
    CHECK_EQ(d, d2);
  }

  {
    std::stringstream ss{"10:03:05"};
    ss >> d;
    CHECK_EQ(d, d3);
  }

  {
    std::stringstream ss{"01:03:05"};
    ss >> d;
    CHECK_EQ(d, d4);
  }

  {
    std::stringstream ss{"00:00:00"};
    ss >> d;
    CHECK_EQ(d, d5);
  }
}
