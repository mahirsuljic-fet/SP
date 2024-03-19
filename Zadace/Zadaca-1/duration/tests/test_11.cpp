#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za operator/=") {
  Duration d1{2, 0, 0};
  Duration d2{1, 0, 0};
  Duration d3{1, 20, 0};

  Duration d4{0, 5, 0};
  Duration d5{1, 5, 00};
  Duration d6{1, 5, 10};

  Duration d;

  SUBCASE("Bez potrebe za prenos") {
    d = d1 /= 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 1);
  }

  SUBCASE("Prenos sati na minute") {
    d = d2 /= 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 30);
    CHECK(d.get_h() == 0);

    d = d3 /= 2;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 40);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("Prenos minuta na sekunde") {
    d = d4 /= 2;
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 2);
    CHECK(d.get_h() == 0);

    d = d5 /= 2;
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 32);
    CHECK(d.get_h() == 0);

    d = d6 /= 2;
    CHECK(d.get_s() == 35);
    CHECK(d.get_m() == 32);
    CHECK(d.get_h() == 0);
  }
}



