#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::Iterator copy constructor") {
  int arr[] = {1, 2, 3};
  MojVektor<int>::Iterator it(arr);

  SUBCASE(
      "The copy constructor should create a new iterator with the same "
      "value as the original") {
    MojVektor<int>::Iterator it_copy(it);
    CHECK(it.operator*() == it_copy.operator*());
  }
}
