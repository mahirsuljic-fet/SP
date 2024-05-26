#pragma once

#include "../zadatak1/DoubleLinkedList.hpp"
#include <cstdint>
#include <iostream>
#include <string>

class Number
{
  public:
    Number();
    Number(const Number&);
    Number(Number&&);
    Number& operator=(const Number&);
    Number& operator=(Number&&);
    Number(const std::string&);
    Number(long);

    Number operator+(const Number&) const;
    Number operator-(const Number&) const;
    Number operator*(const Number&) const;
    Number& operator+=(const Number&);
    Number& operator-=(const Number&);
    Number& operator*=(const Number&);
    Number& operator=(const int&);
    Number& operator=(int&&);
    Number operator+(const int&) const;
    Number operator-(const int&) const;
    Number operator*(const int&) const;
    Number& operator+=(const int&);
    Number& operator-=(const int&);
    Number& operator*=(const int&);
    bool operator==(const Number& o) const;
    bool operator!=(const Number&) const;
    bool operator>(const Number&) const;
    bool operator<(const Number&) const;
    bool operator>=(const Number&) const;
    bool operator<=(const Number&) const;
    bool operator==(const int&) const;
    bool operator!=(const int&) const;
    bool operator>(const int&) const;
    bool operator<(const int&) const;
    bool operator>=(const int&) const;
    bool operator<=(const int&) const;
    Number operator^(short) const;
    Number operator^(Number) const;
    operator bool() const;
    Number& operator++();
    Number operator++(int);
    Number& operator--();
    Number operator--(int);

    friend std::ostream& operator<<(std::ostream& o, const Number& num);

  private:
    using Digit = int8_t;
    DoubleLinkedList<Digit> digits_ {};
    mutable bool negative_ = false;
};
