#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../duration.hpp"
#include "doctest.h"

TEST_CASE("Testni kod za operator<<") {
  Duration d1{10, 30, 50};
  Duration d2{10, 30, 5};
  Duration d3{10, 3, 5};
  Duration d4{1, 3, 5};
  Duration d5;

  {
    std::stringstream ss;
    ss << d1;
    CHECK_EQ(ss.str(), "10:30:50");
  }

  {
    std::stringstream ss;
    ss << d2;
    CHECK_EQ(ss.str(), "10:30:05");
  }

  {
    std::stringstream ss;
    ss << d3;
    CHECK_EQ(ss.str(), "10:03:05");
  }

  {
    std::stringstream ss;
    ss << d4;
    CHECK_EQ(ss.str(), "01:03:05");
  }

  {
    std::stringstream ss;
    ss << d5;
    CHECK_EQ(ss.str(), "00:00:00");
  }
}
