#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za aritmetički operator-") {
  Duration d1{10, 30, 20};
  Duration d2{1, 10, 10};
  Duration d3{1, 10, 50};
  Duration d4{1, 40, 10};
  Duration d5{1, 40, 50};

  Duration d;

  SUBCASE("Test operator-") {
    d = d1 - d2;
    CHECK(d.get_s() == 10);
    CHECK(d.get_m() == 20);
    CHECK(d.get_h() == 9);

    d = d1 - d1;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("operator- baca iznimku kada bi vrijednost postala negativna") {
    CHECK_THROWS_AS(d2 - d1, std::out_of_range);
    CHECK_THROWS_AS(d3 - d1, std::out_of_range);
    CHECK_THROWS_AS(d4 - d1, std::out_of_range);
  }

  SUBCASE("Test operator- sa posuđivanjem minuta") {
    d = d1 - d3;
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 19);
    CHECK(d.get_h() == 9);
  }

  SUBCASE("Test operator- sa posuđivanjem sati") {
    d = d1 - d4;
    CHECK(d.get_s() == 10);
    CHECK(d.get_m() == 50);
    CHECK(d.get_h() == 8);
  }

  SUBCASE("Test operator- sa posuđivanjem minuta i sati") {
    d = d1 - d5;
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 49);
    CHECK(d.get_h() == 8);
  }

  SUBCASE("Test nadovezanog operator-") {
    d = d1 - d2 - d3;
    CHECK(d.get_s() == 20);
    CHECK(d.get_m() == 9);
    CHECK(d.get_h() == 8);
  }
}
