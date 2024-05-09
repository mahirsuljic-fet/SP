#include "annotated.hpp"

#include <iostream>
#include <string>

// rvo (return value optimization)
AnnotatedString stringFactory()
{
  AnnotatedString ime;
  ime.value = "Mak";
  return ime;
}

int main()
{
  const auto ime = stringFactory();
  return 0;
}
