#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("MojVektor push_back with rvalue reference") {
  MojVektor<std::string> v;

  std::string val1{"First value"};
  v.push_back(std::move(val1));
  REQUIRE(v.size() == 1);
  REQUIRE(v.back() == std::string{"First value"});

  std::string val2 = "Second value";
  v.push_back(std::move(val2));
  REQUIRE(v.size() == 2);
  REQUIRE(v.back() == "Second value");

  std::string val3{"Third value"};
  v.push_back(std::move(val3));
  REQUIRE(v.size() == 3);
  REQUIRE(v.back() == std::string{"Third value"});
}
