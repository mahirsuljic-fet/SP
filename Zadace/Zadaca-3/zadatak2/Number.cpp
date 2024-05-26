#include "Number.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>

Number::Number() { digits_.push_back(0); }

Number::Number(const Number& other)
{
  for (const auto& digit : other.digits_)
    this->digits_.push_back(digit);
  this->negative_ = other.negative_;
}

Number::Number(Number&& other)
{
  this->digits_ = std::move(other.digits_);
  this->negative_ = other.negative_;
}

Number& Number::operator=(const Number& other)
{
  if (this != &other)
  {
    this->digits_.clear();
    for (const auto& digit : other.digits_)
      this->digits_.push_back(digit);
    this->negative_ = other.negative_;
  }
  return *this;
}

Number& Number::operator=(Number&& other)
{
  if (this != &other)
  {
    // std::swap(*this, other);
    this->digits_.clear();
    this->digits_ = std::move(other.digits_);
    this->negative_ = other.negative_;
  }
  return *this;
}

Number::Number(const std::string& str)
{
  if (str[0] == '-') this->negative_ = true;
  for (auto it = str.rbegin(); it != str.rend() && *it != '-' && *it != '+'; ++it)
  {
    if (*it < '0' || *it > '9') throw std::invalid_argument("Argument std::string konstruktora nije validan broj");
    this->digits_.push_back(*it - '0');
  }
}

Number::Number(long n)
{
  if (n != 0)
  {
    if (n < 0)
      negative_ = true;
    else
      negative_ = false;

    n = std::abs(n);

    do
    {
      digits_.push_back(n % 10);
      n /= 10;
    }
    while (n != 0);
  }
  else
    digits_.push_back(0);
}

Number Number::operator+(const Number& other) const
{
  if (other == 0) return *this;
  if (*this == 0) return other;

  Number result = 0;

  size_t remainder = 0;
  Digit current_digit = 0;
  int16_t current_result = 0;

  const Number& lhs = this->digits_.size() >= other.digits_.size() ? *this : other;
  const Number& rhs = this->digits_.size() >= other.digits_.size() ? other : *this;

  auto it_lhs = lhs.digits_.begin();
  auto it_rhs = rhs.digits_.begin();

  result.digits_.clear();
  result.negative_ = true;
  if (!this->negative_ && !other.negative_) result.negative_ = false;

  if (this->negative_ && !other.negative_)
  {
    this->negative_ = false;
    result = other - *this;
    this->negative_ = true;
    return result;
  }

  if (!this->negative_ && other.negative_)
  {
    other.negative_ = false;
    result = *this - other;
    other.negative_ = true;
    return result;
  }

  while (it_lhs != lhs.digits_.end())
  {
    if (it_rhs != rhs.digits_.end())
      current_result = *it_lhs + *it_rhs + remainder;
    else
      current_result = *it_lhs + remainder;

    if (current_result < 10)
    {
      current_digit = current_result;
      remainder = 0;
    }
    else
    {
      current_digit = current_result % 10;
      remainder = current_result / 10;
    }

    result.digits_.push_back(current_digit);

    ++it_lhs;
    if (it_rhs != rhs.digits_.end())
      ++it_rhs;
  }

  while (remainder != 0)
  {
    result.digits_.push_back(remainder % 10);
    remainder /= 10;
  }

  return result;
}

Number Number::operator-(const Number& other) const
{
  if (other == 0) return *this;
  if (*this == other) return 0;

  Number result = 0;

  if (*this == 0)
  {
    result = other;
    result.negative_ = !other.negative_;
    return result;
  }

  if (this->negative_ && !other.negative_)
  {
    this->negative_ = false;
    result = other + *this;
    this->negative_ = true;
    result.negative_ = true;
    return result;
  }

  if (!this->negative_ && other.negative_)
  {
    other.negative_ = false;
    result = *this + other;
    other.negative_ = true;
    return result;
  }

  long remainder = 0;
  Digit current_digit = 0;
  int16_t current_result = 0;

  bool original_this_negative = this->negative_;
  bool original_other_negative = other.negative_;

  this->negative_ = false;
  other.negative_ = false;

  const Number& lhs = *this >= other ? *this : other;
  const Number& rhs = *this >= other ? other : *this;

  auto it_lhs = lhs.digits_.begin();
  auto it_rhs = rhs.digits_.begin();
  Digit lhs_digit = *it_lhs;
  Digit rhs_digit = *it_rhs;

  result.digits_.clear();
  result.negative_ = *this >= other ? false : true;

  if (original_this_negative && original_other_negative) result.negative_ = !result.negative_;

  while (it_lhs != lhs.digits_.end())
  {
    lhs_digit = *it_lhs + remainder;
    if (it_rhs != rhs.digits_.end())
      rhs_digit = *it_rhs;
    else
      rhs_digit = 0;

    remainder = 0;
    if (lhs_digit >= rhs_digit)
      current_result = lhs_digit - rhs_digit;
    else
    {
      current_result = lhs_digit + 10 - rhs_digit;
      --remainder;
    }

    current_digit = current_result % 10;
    result.digits_.push_back(current_digit);

    ++it_lhs;
    if (it_rhs != rhs.digits_.end())
      ++it_rhs;
  }

  while (result.digits_.back() == 0)
    result.digits_.pop_back();

  this->negative_ = original_this_negative;
  other.negative_ = original_other_negative;

  return result;
}

Number Number::operator*(const Number& other) const
{
  if (other == 1) return *this;
  if (*this == 1) return other;
  if (*this == 0 || other == 0) return 0;

  Number result = 0;
  long remainder = 0;
  Digit current_digit = 0;
  int16_t current_result = 0;

  const Number& lhs = *this;
  const Number& rhs = other;

  result.digits_.clear();
  for (int i = 0; i < this->digits_.size() + other.digits_.size(); ++i)
    result.digits_.push_back(0);

  if (this->negative_ && !other.negative_ || !this->negative_ && other.negative_) result.negative_ = true;

  auto it_result = result.digits_.begin();
  auto it_result_mem = result.digits_.begin();
  for (auto it_lhs = lhs.digits_.begin(); it_lhs != lhs.digits_.end(); ++it_lhs, ++it_result_mem)
  {
    it_result = it_result_mem;
    for (auto it_rhs = rhs.digits_.begin(); it_rhs != rhs.digits_.end(); ++it_rhs, ++it_result)
    {
      current_result = *it_result + *it_lhs * *it_rhs + remainder;

      if (current_result > 9)
      {
        current_digit = current_result % 10;
        remainder = current_result / 10;
      }
      else
      {
        current_digit = current_result;
        remainder = 0;
      }

      *it_result = current_digit;
    }

    while (remainder != 0)
    {
      *it_result++ = remainder % 10;
      remainder /= 10;
    }
  }

  while (result.digits_.back() == 0) result.digits_.pop_back();

  return result;
}

Number& Number::operator+=(const Number& other)
{
  return *this = *this + other;
}

Number& Number::operator-=(const Number& other)
{
  return *this = *this - other;
}

Number& Number::operator*=(const Number& other)
{
  return *this = *this * other;
}

Number& Number::operator=(const int& n)
{
  digits_.clear();
  return *this = Number { n };
}

Number& Number::operator=(int&& n)
{
  digits_.clear();
  return *this = Number { std::move(n) };
}

Number Number::operator+(const int& n) const
{
  return *this + Number { n };
}

Number Number::operator-(const int& n) const
{
  return *this - Number { n };
}

Number Number::operator*(const int& n) const
{
  return *this * Number { n };
}

Number& Number::operator+=(const int& n)
{
  return *this += Number { n };
}

Number& Number::operator-=(const int& n)
{
  return *this -= Number { n };
}

Number& Number::operator*=(const int& n)
{
  return *this *= Number { n };
}

bool Number::operator==(const Number& other) const
{
  if (this->negative_ != other.negative_) return false;
  if (this->digits_.size() != other.digits_.size()) return false;

  auto it_this = this->digits_.rbegin();
  auto it_other = other.digits_.rbegin();
  while (it_this != this->digits_.rend())
    if (*it_this-- != *it_other--)
      return false;
  return true;
}

bool Number::operator!=(const Number& other) const
{
  return !(*this == other);
}

bool Number::operator>(const Number& other) const
{
  if (!this->negative_ && other.negative_) return true;
  if (this->negative_ && !other.negative_) return false;
  if (!this->negative_ && !other.negative_)
  {
    if (this->digits_.size() > other.digits_.size()) return true;
    if (this->digits_.size() < other.digits_.size()) return false;
  }
  else
  {
    if (this->digits_.size() > other.digits_.size()) return false;
    if (this->digits_.size() < other.digits_.size()) return true;
  }

  const Number& lhs = !this->negative_ && !other.negative_ ? *this : other;
  const Number& rhs = !this->negative_ && !other.negative_ ? other : *this;

  auto it_this = lhs.digits_.rbegin();
  auto it_other = rhs.digits_.rbegin();
  while (it_this != this->digits_.rend())
  {
    if (*it_this > *it_other) return true;
    if (*it_this-- < *it_other--) return false;
  }
  return false;
}

bool Number::operator<(const Number& other) const
{
  if (this->negative_ && !other.negative_) return true;
  if (!this->negative_ && other.negative_) return false;
  if (!this->negative_ && !other.negative_)
  {
    if (this->digits_.size() < other.digits_.size()) return true;
    if (this->digits_.size() > other.digits_.size()) return false;
  }
  else
  {
    if (this->digits_.size() < other.digits_.size()) return false;
    if (this->digits_.size() > other.digits_.size()) return true;
  }

  const Number& lhs = !this->negative_ && !other.negative_ ? *this : other;
  const Number& rhs = !this->negative_ && !other.negative_ ? other : *this;

  auto it_this = lhs.digits_.rbegin();
  auto it_other = rhs.digits_.rbegin();
  while (it_this != this->digits_.rend())
  {
    if (*it_this < *it_other) return true;
    if (*it_this-- > *it_other--) return false;
  }
  return false;
}

bool Number::operator>=(const Number& other) const
{
  return !(*this < other);
}

bool Number::operator<=(const Number& other) const
{
  return !(*this > other);
}

bool Number::operator==(const int& n) const
{
  return *this == Number { n };
}

bool Number::operator!=(const int& n) const
{
  return *this != Number { n };
}

bool Number::operator>(const int& n) const
{
  return *this > Number { n };
}

bool Number::operator<(const int& n) const
{
  return *this < Number { n };
}

bool Number::operator>=(const int& n) const
{
  return *this >= Number { n };
}

bool Number::operator<=(const int& n) const
{
  return *this <= Number { n };
}

Number Number::operator^(Number n) const
{
  if (*this == 0)
  {
    if (n > 0)
      return 0;
    else
      throw std::invalid_argument("Dijeljenje sa nulom nije dozvoljeno");
  }

  if (*this == 1) return 1;
  if (n == 0) return 1;
  if (*this == -1) return n % 2 == 0 ? 1 : -1;
  if (n < 0) return 0;

  Number result = 1;
  for (Number i = 0; i < n; ++i)
    result *= *this;

  return result;
}

Number Number::operator^(short n) const
{
  return *this ^ Number { n };
}

Number::operator bool() const
{
  return !this->digits_.empty();
}

Number& Number::operator++()
{
  return *this += 1;
}

Number Number::operator++(int)
{
  Number temp = *this;
  *this += 1;
  return temp;
}

Number& Number::operator--()
{
  return *this -= 1;
}

Number Number::operator--(int)
{
  Number temp = *this;
  *this -= 1;
  return temp;
}

std::ostream& operator<<(std::ostream& o, const Number& num)
{
  std::ostringstream oss;
  if (num.negative_) oss << '-';
  for (auto it = num.digits_.rbegin(); it != nullptr; --it)
    oss << +*it;
  return o << oss.str();
}
