#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::Iterator constructor with pointer parameter") {
  int arr[] = {1, 2, 3};
  int* ptr = arr;

  SUBCASE("The constructor should create an iterator that points to the given "
          "pointer") {
    MojVektor<int>::Iterator it(ptr);
    CHECK(*it == 1);
  }
}

