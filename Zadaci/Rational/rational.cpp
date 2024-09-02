#include "rational.hpp"

#include <ostream>

Rational::Rational(int numerator, int denominator)
{
  if (denominator == 0) throw std::invalid_argument("Nazivnik ne smije biti nula.");
  int gcd = std::__gcd(numerator, denominator);

  numerator_ = numerator / gcd;
  denominator_ = denominator / gcd;
}

Rational Rational::operator+(const Rational& other)
{
  return Rational(this->numerator_ * other.denominator_ + other.numerator_ + this->denominator_, this->denominator_ * other.denominator_);
}

std::ostream& operator<<(std::ostream& os, const Rational& rational)
{
  os << rational.numerator_;

  if (rational.denominator_ != 1) os << '/' << rational.denominator_;

  return os;
}
