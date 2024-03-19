#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za relacione operatore") {
  Duration d1{10, 30, 45};
  Duration d2{10, 30, 50};
  Duration d3{10, 31, 45};

  Duration d4{11, 30, 45};
  Duration d5{11, 30, 45};

  Duration d6{11, 30, 50};
  Duration d7{11, 31, 45};
  Duration d8{12, 30, 45};

  SUBCASE("Testiranje operatora==") {
    CHECK_FALSE(d1 == d2);
    CHECK_FALSE(d1 == d3);
    CHECK_FALSE(d1 == d4);

    CHECK(d4 == d5);

    CHECK_FALSE(d5 == d6);
    CHECK_FALSE(d5 == d7);
    CHECK_FALSE(d5 == d8);

    d2.set_s(45);
    CHECK(d1 == d2);

    d3.set_m(30);
    CHECK(d1 == d3);

    d4.set_h(10);
    CHECK(d1 == d4);
  }

  SUBCASE("Testiranje operatora!=") {
    CHECK(d1 != d2);
    CHECK(d1 != d3);
    CHECK(d1 != d4);

    CHECK_FALSE(d4 != d5);

    CHECK(d5 != d6);
    CHECK(d5 != d7);
    CHECK(d5 != d8);

    d2.set_s(45);
    CHECK_FALSE(d1 != d2);

    d3.set_m(30);
    CHECK_FALSE(d1 != d3);

    d4.set_h(10);
    CHECK_FALSE(d1 != d4);
  }

  SUBCASE("Testiranje operatore < i >") {
    CHECK(d1 < d2);
    CHECK(d1 < d3);
    CHECK(d1 < d4);

    CHECK_FALSE(d1 > d2);
    CHECK_FALSE(d1 > d3);
    CHECK_FALSE(d1 > d4);

    CHECK_FALSE(d8 < d5);
    CHECK_FALSE(d8 < d6);
    CHECK_FALSE(d8 < d7);

    CHECK(d8 > d5);
    CHECK(d8 > d6);
    CHECK(d8 > d7);
  }

  SUBCASE("Testiranje operatore<=") {
    CHECK(d4 <= d4);
    CHECK(d4 <= d5);
    CHECK(d4 <= d6);
    CHECK(d4 <= d7);
    CHECK(d4 <= d8);

    CHECK_FALSE(d5 <= d1);
    CHECK_FALSE(d5 <= d2);
    CHECK_FALSE(d5 <= d3);
  }

  SUBCASE("Testiranje operator>=") {
    CHECK(d5 >= d1);
    CHECK(d5 >= d2);
    CHECK(d5 >= d3);
    CHECK(d5 >= d4);
    CHECK(d5 >= d5);

    CHECK_FALSE(d4 >= d6);
    CHECK_FALSE(d4 >= d7);
    CHECK_FALSE(d4 >= d8);
  }
}
