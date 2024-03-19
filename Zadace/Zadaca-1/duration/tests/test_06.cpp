#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za aritmetički operator+=") {
  Duration d1{10, 30, 20};
  Duration d2{1, 10, 10};
  Duration d3{1, 10, 50};

  SUBCASE("Test operator+=") {
    d1 += d2;
    CHECK(d1.get_s() == 30);
    CHECK(d1.get_m() == 40);
    CHECK(d1.get_h() == 11);
  }

  SUBCASE("Test operator+= sa preljevom sekundi") {
    d1 += d3;
    CHECK(d1.get_s() == 10);
    CHECK(d1.get_m() == 41);
    CHECK(d1.get_h() == 11);
  }

  SUBCASE("Test operator+= sa preljevom minuta") {
    d1 += d1;
    CHECK(d1.get_s() == 40);
    CHECK(d1.get_m() == 0);
    CHECK(d1.get_h() == 21);
  }
}
