#include "Rational.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

Rational::Rational() : numerator_(0), denominator_(1) { }

Rational::Rational(int numerator, int denominator)
{
  if (denominator == 0) throw std::invalid_argument("Nazivnik ne smije biti nula.");

  int gcd = std::gcd(numerator, denominator);

  numerator_ = numerator / gcd;
  denominator_ = denominator / gcd;
}

Rational::Rational(const char* rational)
{
  bool slash = false;
  std::string numerator_str, denominator_str;

  for (int i = 0; rational[i] != '\0'; ++i)
  {
    if (rational[i] >= '0' && rational[i] <= '9')
    {
      if (!slash)
        numerator_str += rational[i];
      else
        denominator_str += rational[i];
    }
    else
    {
      if (rational[i] == '/')
      {
        if (!slash)
          slash = true;
        else
          throw std::invalid_argument("Razlomak pored brojeva mora sadrzavati samo jedan znak /.");
      }
      else
        throw std::invalid_argument("Razlomak sadrzi nesto sto nije broj ili /.");
    }
  }

  if (!numerator_str.empty() && denominator_str.empty())
  {
    numerator_ = std::stoi(numerator_str);
    denominator_ = 1;
    return;
  }

  int numerator = std::stoi(numerator_str);
  int denominator = std::stoi(denominator_str);

  if (denominator == 0) throw std::invalid_argument("Nazivnik ne smije biti nula.");

  int gcd = std::gcd(numerator, denominator);
  numerator_ = numerator / gcd;
  denominator_ = denominator / gcd;
}

Rational::Rational(const std::string& rational)
{
  *this = Rational(rational.c_str());
}

Rational::Rational(const Rational& rational)
{
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
}

Rational::Rational(Rational&& rational)
{
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;

  rational.numerator_ = 0;
  rational.denominator_ = 1;
}

Rational& Rational::operator=(const Rational& other)
{
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;

  return *this;
}

Rational& Rational::operator=(Rational&& other)
{
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;

  other.numerator_ = 0;
  other.denominator_ = 1;

  return *this;
}

Rational Rational::operator+(const Rational& other) const
{
  int common = this->denominator_ * other.denominator_;
  int numerator = this->numerator_ * other.denominator_ + other.numerator_ * this->denominator_;

  return Rational(numerator, common);
}

Rational Rational::operator+(int numerator) const
{
  return Rational(this->numerator_ + numerator * this->denominator_, this->denominator_);
}

Rational Rational::operator-(const Rational& other) const
{
  int common = this->denominator_ * other.denominator_;
  int numerator = this->numerator_ * other.denominator_ - other.numerator_ * this->denominator_;

  return Rational(numerator, common);
}

Rational Rational::operator-(int numerator) const
{
  return Rational(this->numerator_ - numerator * this->denominator_, this->denominator_);
}

Rational Rational::operator*(const Rational& other) const
{
  int numerator = this->numerator_ * other.numerator_;
  int denominator = this->denominator_ * other.denominator_;

  return Rational(numerator, denominator);
}

Rational Rational::operator*(int numerator) const
{
  return Rational(this->numerator_ * numerator, this->denominator_);
}

Rational Rational::operator/(const Rational& other) const
{
  int numerator = this->numerator_ * other.denominator_;
  int denominator = this->denominator_ * other.numerator_;

  return Rational(numerator, denominator);
}

Rational Rational::operator/(int numerator) const
{
  return Rational(this->numerator_, this->denominator_ * numerator);
}

Rational Rational::operator^(int n) const
{
  int numerator = 1;
  int denominator = 1;

  for (int i = 0; i < abs(n); ++i)
  {
    numerator *= numerator_;
    denominator *= denominator_;
  }

  return n > 0 ? Rational(numerator, denominator) : Rational(denominator, numerator);
}

Rational& Rational::operator++()
{
  *this = *this + 1;
  return *this;
}

Rational Rational::operator++(int)
{
  Rational temp = *this;
  *this = *this + 1;
  return temp;
}

Rational& Rational::operator--()
{
  *this = *this - 1;
  return *this;
}

Rational Rational::operator--(int)
{
  Rational temp = *this;
  *this = *this - 1;
  return temp;
}

bool Rational::operator==(const Rational& other) const
{
  return this->numerator_ == other.numerator_ && this->denominator_ == other.denominator_;
}

bool Rational::operator==(const char* other) const
{
  return *this == Rational(other);
}

bool Rational::operator!=(const Rational& other) const
{
  return this->numerator_ != other.numerator_ || this->denominator_ != other.denominator_;
}

bool Rational::operator!=(const char* other) const
{
  return *this != Rational(other);
}

std::ostream& operator<<(std::ostream& output, const Rational& rational)
{
  if (rational.denominator() == 1)
    output << rational.numerator();
  else
    output << rational.numerator() << "/" << rational.denominator();

  return output;
}
