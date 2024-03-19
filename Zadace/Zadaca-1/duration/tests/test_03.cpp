#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za set metode nad objektima Duration") {
  Duration d;
  Duration d1{11 + 12 * 60 + 13 * 60 * 60};

  SUBCASE("set_s metoda nad default inicijliziranim objektom") {
    d.set_s(30);
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);

    d.set_s(0);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);

    d.set_s(59);
    CHECK(d.get_s() == 59);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("set_m metoda nad default inicijliziranim objektom") {
    d.set_m(30);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 30);
    CHECK(d.get_h() == 0);

    d.set_m(0);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);

    d.set_m(59);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 59);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("set_h metoda nad default inicijliziranim objektom") {
    d.set_h(30);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 30);

    d.set_h(0);
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("set_s metoda nad objektom koji već ima  neku vrijedonst") {
    d1.set_s(30);
    CHECK(d1.get_s() == 30);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    d1.set_s(0);
    CHECK(d1.get_s() == 0);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    d1.set_s(59);
    CHECK(d1.get_s() == 59);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);
  }

  SUBCASE("set_m metoda nad objektom koji već ima  neku vrijedonst") {
    d1.set_m(30);
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 30);
    CHECK(d1.get_h() == 13);

    d1.set_m(0);
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 0);
    CHECK(d1.get_h() == 13);

    d1.set_m(59);
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 59);
    CHECK(d1.get_h() == 13);
  }

  SUBCASE("set_h metoda nad objektom koji već ima  neku vrijedonst") {
    d1.set_h(30);
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 30);

    d1.set_h(0);
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 0);
  }
}

TEST_CASE("Testni kod kad set metode bacaju iznimku") {
  Duration d;

  SUBCASE("set_s metod baca iznimku") {
    CHECK_THROWS_AS(d.set_s(-1), std::out_of_range);
    CHECK_THROWS_AS(d.set_s(60), std::out_of_range);
  }

  SUBCASE("set_m metod baca iznimku") {
    CHECK_THROWS_AS(d.set_m(-1), std::out_of_range);
    CHECK_THROWS_AS(d.set_m(60), std::out_of_range);
  }

  SUBCASE("set_h metod baca iznimku") {
    CHECK_THROWS_AS(d.set_h(-1), std::out_of_range);
  }
}

TEST_CASE("Testni kod za nadovezivanje set metoda") {
  Duration d;

  d.set_s(31).set_m(50).set_h(10);
  CHECK(d.get_s() == 31);
  CHECK(d.get_m() == 50);
  CHECK(d.get_h() == 10);
}
