#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../duration.hpp"

TEST_CASE("Testni kod za operator istinitosti") {
  Duration d1;
  Duration d2{10, 30, 50};

  SUBCASE("Testiranje izraza tačno bool()") {
    CHECK_FALSE(d1);
    CHECK(d2);
  }

  SUBCASE("Testiranje izraza negacije") {
    CHECK(!d1);
    CHECK_FALSE(!d2);
  }
}
