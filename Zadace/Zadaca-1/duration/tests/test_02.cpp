#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za konstruktore i get metode") {

  SUBCASE("Konstruktor sa vrijednosti sekundi, minuta i sati") {
    {
      Duration d{1, 2, 3};
      CHECK(d.get_s() == 3);
      CHECK(d.get_m() == 2);
      CHECK(d.get_h() == 1);
    }
    {
      Duration d{30, 40,  50};
      CHECK(d.get_s() == 50);
      CHECK(d.get_m() == 40);
      CHECK(d.get_h() == 30);
    }
  }

  SUBCASE("Konstruktor sa vrijednosti sekundi, minuta i sati baca iznimku na prevelikim vrijednostima") {
    CHECK_THROWS_AS(Duration(30, 40, 60), std::out_of_range);
    CHECK_THROWS_AS(Duration(30, 40, 70), std::out_of_range);
    CHECK_THROWS_AS(Duration(30, 60, 10), std::out_of_range);
    CHECK_THROWS_AS(Duration(30, 80, 10), std::out_of_range);
  }
}

TEST_CASE("Testni kod za copy/move konstruktore i operatore =") {

  SUBCASE("Copy Constructor") {
    Duration d{11 + 12 * 60 + 13 * 60 * 60};
    Duration d1{d};
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);
  }

  SUBCASE("Move Constructor") {
    Duration d{11 + 12 * 60 + 13 * 60 * 60};
    Duration d1{std::move(d)};
    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);
  }
}

TEST_CASE("Testni kod za operator= (i get metode)") { 
  Duration d{11 + 12 * 60 + 13 * 60 * 60};
  Duration d1;
  Duration d2{21 + 22 * 60 + 23 * 60 * 60};
  Duration d3;

  SUBCASE("Copy operator=") {
    d1 = d;
    d = d3;

    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("Nadovezani copy operator=") {
    d3 = d2 = d1 = d;

    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    CHECK(d2.get_s() == 11);
    CHECK(d2.get_m() == 12);
    CHECK(d2.get_h() == 13);

    CHECK(d3.get_s() == 11);
    CHECK(d3.get_m() == 12);
    CHECK(d3.get_h() == 13);
  }

  SUBCASE("Move operator=") {
    d1 = std::move(d);
    d = std::move(d2);

    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    CHECK(d.get_s() == 21);
    CHECK(d.get_m() == 22);
    CHECK(d.get_h() == 23);
  }

  SUBCASE("Kombinacija move i copy operator=") {
    d2 = d1 = std::move(d);

    CHECK(d1.get_s() == 11);
    CHECK(d1.get_m() == 12);
    CHECK(d1.get_h() == 13);

    CHECK(d2.get_s() == 11);
    CHECK(d2.get_m() == 12);
    CHECK(d2.get_h() == 13);
  }
}
