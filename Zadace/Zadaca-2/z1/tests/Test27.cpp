#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::Iterator move assignment operator") {
  int arr[] = {1, 2, 3};
  MojVektor<int>::Iterator it(arr);

  SUBCASE(
      "The move assignment operator should move the value from the "
      "original iterator to the new iterator") {
    int arr2[] = {4, 5, 6};
    MojVektor<int>::Iterator it2(arr2);
    it2 = std::move(it);
    CHECK(it.operator->() == nullptr);
    CHECK(*it2 == 1);
  }
}
