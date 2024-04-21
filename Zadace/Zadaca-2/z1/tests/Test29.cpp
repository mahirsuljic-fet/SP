#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing push_front with dynamic resizing") {
  // Create a vector with initial capacity of 10 elements
  MojVektor<int> v;

  // Add more than 10 elements to the vector
  const int n = 15;
  for (int i = 0; i < n; i++) {
    v.push_front(i);
  }

  // Check that the size of the vector is equal to the number of added elements
  CHECK(v.size() == n);

  // Check that the capacity of the vector has been increased to hold all the
  // elements
  CHECK(v.capacity() == 20);

  // Check that the elements in the vector are correct
  for (int i = 0; i < n; ++i) {
    CHECK(v[i] == n - i - 1);
  }
}
