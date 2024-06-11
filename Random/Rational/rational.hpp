#pragma once

#include <algorithm>
#include <numeric>
#include <ostream>
#include <stdexcept>

class Rational
{
  public:
    Rational() : numerator_ { 0 }, denominator_ { 1 } { }
    Rational(int numerator, int denominator);

    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);

    Rational operator+(const Rational& other);

  private:
    int numerator_;
    int denominator_;
};
