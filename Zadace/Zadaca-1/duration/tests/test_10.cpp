#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za operator*=") {
  Duration d1{1, 20, 20};
  Duration d2{1, 20, 30};
  Duration d3{1, 20, 50};
  Duration d4{1, 30, 20};
  Duration d5{1, 40, 20};
  Duration d6{1, 40, 50};

  Duration d;

  SUBCASE("Bez potrebe za prenos") {
    d = d1 *= 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 40);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos sekundi na minute") {
    d = d2 *= 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);

    d = d3 *= 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos sekundi na minute") {
    d = d2 *= 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);

    d = d3 *= 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos minuta na sate") {
    d = d4 *= 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 3);

    d = d5 *= 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 20);
    CHECK(d.get_h() == 3);
  }
}

TEST_CASE("Testni kod za operator*") {
  Duration d1{1, 20, 20};
  Duration d2{1, 20, 30};
  Duration d3{1, 20, 50};
  Duration d4{1, 30, 20};
  Duration d5{1, 40, 20};
  Duration d6{1, 40, 50};

  Duration d;

  SUBCASE("Bez potrebe za prenos") {
    d = d1 * 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 40);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos sekundi na minute") {
    d = d2 * 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);

    d = d3 * 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos sekundi na minute") {
    d = d2 * 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);

    d = d3 * 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 41);
    CHECK(d.get_h() == 2);
  }

  SUBCASE("Prenos minuta na sate") {
    d = d4 * 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 3);

    d = d5 * 2;
    CHECK(d.get_s() == 40);
    CHECK(d.get_m() == 20);
    CHECK(d.get_h() == 3);
  }
}
