#pragma once

#include <bitset>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

template <typename T>
class Binary
{
  public:
    Binary() : number_(sizeof(T) * 8, '0') { }
    Binary(T decimal) : number_(std::bitset<sizeof(T) * 8>(decimal).to_string()) { }
    Binary(std::string binary) : number_(std::string(sizeof(T) * 8 - binary.size(), '0') + binary) { }

    Binary operator+(const Binary& other);
    Binary operator+(const Binary& other) const;
    Binary operator-(const Binary& other);
    Binary operator-(const Binary& other) const;
    Binary operator*(const Binary& other);
    Binary operator*(const Binary& other) const;
    Binary operator/(const Binary& other);
    Binary operator/(const Binary& other) const;
    Binary operator++(int);
    Binary& operator++();
    Binary operator--(int);
    Binary& operator--();

    std::string str() const { return number_; }
    T val() const;

  private:
    std::string number_;
};

template <typename T>
Binary<T> Binary<T>::operator+(const Binary<T>& other)
{
  return Binary(this->val() + other.val());
}

template <typename T>
Binary<T> Binary<T>::operator+(const Binary<T>& other) const
{
  return Binary(this->val() + other.val());
}

template <typename T>
Binary<T> Binary<T>::operator-(const Binary<T>& other)
{
  return Binary(this->val() - other.val());
}

template <typename T>
Binary<T> Binary<T>::operator-(const Binary<T>& other) const
{
  return Binary(this->val() - other.val());
}

template <typename T>
Binary<T> Binary<T>::operator*(const Binary<T>& other)
{
  return Binary(this->val() * other.val());
}

template <typename T>
Binary<T> Binary<T>::operator*(const Binary<T>& other) const
{
  return Binary(this->val() * other.val());
}

template <typename T>
Binary<T> Binary<T>::operator/(const Binary<T>& other)
{
  return Binary(this->val() / other.val());
}

template <typename T>
Binary<T> Binary<T>::operator/(const Binary<T>& other) const
{
  return Binary(this->val() / other.val());
}

template <typename T>
Binary<T> Binary<T>::operator++(int)
{
  Binary temp(*this);
  *this = *this + 1;
  return temp;
}

template <typename T>
Binary<T>& Binary<T>::operator++()
{
  return *this = *this + 1;
}

template <typename T>
Binary<T> Binary<T>::operator--(int)
{
  Binary temp(*this);
  *this = *this - 1;
  return temp;
}

template <typename T>
Binary<T>& Binary<T>::operator--()
{
  return *this = *this - 1;
}

template <typename T>
T Binary<T>::val() const
{
  T result = 0;
  size_t b_val = 1;

  for (auto c = number_.end() - 1; c >= number_.begin(); --c)
  {
    if (*c == '1') result += b_val;
    b_val <<= 1;
  }

  return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Binary<T>& binary)
{
  return os << binary.str();
}

template <typename T>
std::istream& operator>>(std::istream& is, Binary<T>& binary)
{
  std::string sbinary;
  is >> sbinary;
  binary = sbinary;
  return is;
}
