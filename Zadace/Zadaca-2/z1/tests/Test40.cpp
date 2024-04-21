#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("MojVektor rotate() function test") {
  // Test case 1
  {
    MojVektor<int> v{1, 2, 3, 4, 5};
    v.rotate();
    CHECK(v == MojVektor<int>{5, 4, 3, 2, 1});
  }

  // Test case 2
  {
    MojVektor<char> v({'a', 'b', 'c', 'd'});
    v.rotate();
    CHECK(v == MojVektor<char>{'d', 'c', 'b', 'a'});
  }

  // Test case 3
  {
    MojVektor<double> v{1.1, 2.2, 3.3};
    v.rotate();
    CHECK(v == MojVektor<double>{3.3, 2.2, 1.1});
  }
}
