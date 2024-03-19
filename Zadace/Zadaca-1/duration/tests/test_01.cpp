#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za konstruktore i get metode") {

  SUBCASE("Default konstruktor") {
    Duration d;
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
  }

  SUBCASE("Konstruktor sa vrijednosti sekundi bez preliva") {
    {
    Duration d{30};
    CHECK(d.get_s() == 30);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
    }

    {
    Duration d{59};
    CHECK(d.get_s() == 59);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
    }

    {
    Duration d{0};
    CHECK(d.get_s() == 0);
    CHECK(d.get_m() == 0);
    CHECK(d.get_h() == 0);
    }
  }

  SUBCASE("Konstruktor sa vrijednosti sekundi sa prelivom na minute") {
    {
      Duration d{60};
      CHECK(d.get_s() == 0);
      CHECK(d.get_m() == 1);
      CHECK(d.get_h() == 0);
    }
    {
      Duration d{30 + 60};
      CHECK(d.get_s() == 30);
      CHECK(d.get_m() == 1);
      CHECK(d.get_h() == 0);
    }
    {
      Duration d{120};
      CHECK(d.get_s() == 0);
      CHECK(d.get_m() == 2);
      CHECK(d.get_h() == 0);
    }
    {
      Duration d{30 + 9 * 60};
      CHECK(d.get_s() == 30);
      CHECK(d.get_m() == 9);
      CHECK(d.get_h() == 0);
    }
    {
      Duration d{30 + 59 * 60};
      CHECK(d.get_s() == 30);
      CHECK(d.get_m() == 59);
      CHECK(d.get_h() == 0);
    }
  }

  SUBCASE("Konstruktor sa vrijednosti sekundi sa prelivom na sate i minute") {
    {
      Duration d{60 * 60};
      CHECK(d.get_s() == 0);
      CHECK(d.get_m() == 0);
      CHECK(d.get_h() == 1);
    }
    {
      Duration d{30 * 60 * 60};
      CHECK(d.get_s() == 0);
      CHECK(d.get_m() == 0);
      CHECK(d.get_h() == 30);
    }
    {
      Duration d{30 * 60 + 30 * 60 * 60};
      CHECK(d.get_s() == 0);
      CHECK(d.get_m() == 30);
      CHECK(d.get_h() == 30);
    }
    {
      Duration d{30 + 30 * 60 + 30 * 60 * 60};
      CHECK(d.get_s() == 30);
      CHECK(d.get_m() == 30);
      CHECK(d.get_h() == 30);
    }
  }

}
