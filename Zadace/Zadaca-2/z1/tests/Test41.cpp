#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("MojVektor rotate() function test") {
  // Test case 1
  {
    MojVektor<int> v{1, 2, 3, 4, 5};
    v.rotate(v.begin() + 1, v.begin() + 4);
    CHECK(v == MojVektor<int>{1, 4, 3, 2, 5});
  }

  // Test case 2
  {
    MojVektor<char> v{'a', 'b', 'c', 'd'};
    v.rotate(v.begin() + 2, v.end());
    CHECK(v == MojVektor<char>{'a', 'b', 'd', 'c'});
  }

  // Test case 3
  {
    MojVektor<double> v{1.1, 2.2, 3.3, 4.4};
    v.rotate(v.begin(), v.begin() + 3);
    CHECK(v == MojVektor<double>{3.3, 2.2, 1.1, 4.4});
  }
}
