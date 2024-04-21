#pragma once

#include "../z1/MojVektor.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

template <typename value_t = long, typename coef_t = value_t>
class Polinom
{
  public:
    Polinom() = default;
    Polinom(const std::string&);
    Polinom(std::initializer_list<coef_t>);

    Polinom(Polinom&&);
    Polinom(const Polinom&);
    ~Polinom() = default;

    Polinom& operator=(Polinom&&);
    Polinom& operator=(const Polinom&);

    Polinom operator+(const Polinom&) const;
    Polinom operator-(const Polinom&) const;
    Polinom operator*(const Polinom&) const;

    Polinom operator-();
    Polinom operator-() const;

    Polinom& operator+=(const Polinom&);
    Polinom& operator-=(const Polinom&);
    Polinom& operator*=(const Polinom&);

    Polinom operator+(const coef_t&) const; // sa svakim elementom
    Polinom operator-(const coef_t&) const; // sa svakim elementom
    Polinom operator*(const coef_t&) const;
    Polinom operator/(const coef_t&) const;

    Polinom& operator+=(const coef_t&);
    Polinom& operator-=(const coef_t&);
    Polinom& operator*=(const coef_t&);
    Polinom& operator/=(const coef_t&);

    bool operator==(const Polinom&) const;
    bool operator!=(const Polinom&) const;

    value_t operator()(const value_t&) const;

    Polinom derivative() const;

    friend std::ostream& operator<<(std::ostream& out, const Polinom& poli)
    {
      std::string output = "";

      bool first = true;
      for (long i = 0; i < poli.coefs_.size(); ++i)
      {
        coef_t& current_coef = poli.coefs_[i];
        if (current_coef == 0) continue;
        if (current_coef > 0 && !first) output += '+';
        if (current_coef == -1 && !first) output += '-';
        if (abs(current_coef) != 1 || first)
        {
          output += std::to_string(current_coef);
          first = false;
        }
        if (i > 0) output += 'x';
        if (i > 1) output += '^' + std::to_string(i);
      }

      if (output.empty()) output = '0';

      return out << output;
    }

  private:
    MojVektor<coef_t> coefs_;
    void equalize_size(Polinom&, Polinom&);
};

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>::Polinom(const std::string& input)
{
  MojVektor<std::string> monomials;
  MojVektor<coef_t> coefficients;
  MojVektor<int> exponents;
  std::string current;
  int max_exp = 0;

  // ekstrakcija monoma iz input-a
  for (auto i = 0; i < input.size() - 1; ++i)
  {
    if (!isspace(input[i]))
      current += input[i];

    if (input[i + 1] != '+' && input[i + 1] != '-')
      continue;

    monomials.push_back(current);
    current.clear();
  }

  monomials.push_back(current + input.back());

  // ekstrakcija koeficijenata iz monoma
  for (const auto& mono : monomials)
  {
    if (mono[0] == 'x')
      coefficients.push_back(1);
    else if (mono.size() > 1 && mono[1] == 'x')
    {
      if (mono[0] == '+')
        coefficients.push_back(1);
      else if (mono[0] == '-')
        coefficients.push_back(-1);
      else
        coefficients.push_back(std::stod(mono));
    }
    else
      coefficients.push_back(std::stod(mono));
  }

  current = "";

  // ekstrakcija eksponenata iz monoma
  for (const auto& mono : monomials)
  {
    int i = 0;
    int end_ind = mono.size();

    while (mono[i] != 'x' && i < end_ind) ++i;

    if (i == end_ind)
    {
      exponents.push_back(0);
      if (max_exp < 0) max_exp = 0;
      continue;
    }

    while (mono[i] != '^' && i < end_ind) ++i;

    if (i == end_ind)
    {
      exponents.push_back(1);
      if (max_exp < 1) max_exp = 1;
      continue;
    }

    current = "";
    while (i < end_ind) current += mono[++i];
    exponents.push_back(std::stod(current));
    if (max_exp < exponents.back()) max_exp = exponents.back();
  }

  // formiranje polinoma
  coefs_.reserve(max_exp + 1);
  for (int i = 0; i < max_exp + 1; ++i) coefs_.push_back(0);
  for (int i = 0; i < coefs_.size(); ++i)
    if (coefficients[i] != 0)
      coefs_[exponents[i]] = coefficients[i];
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>::Polinom(std::initializer_list<coef_t> list)
  : coefs_ { list } { }

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>::Polinom(Polinom&& other)
  : coefs_ { std::move(other.coefs_) } { }

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>::Polinom(const Polinom& other)
  : coefs_ { other.coefs_ } { }

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator=(Polinom&& other)
{
  if (this != &other) *this = Polinom { std::move(other) };
  return *this;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator=(const Polinom& other)
{
  if (this != &other) *this = Polinom { other };
  return *this;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator+(const Polinom& other) const
{
  const auto& bigger = (this->coefs_.size() >= other.coefs_.size() ? *this : other);
  const auto& smaller = (this->coefs_.size() < other.coefs_.size() ? *this : other);

  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(bigger.coefs_.size());

  for (auto i = 0; i < smaller.coefs_.size(); ++i)
    result.coefs_.push_back(this->coefs_[i] + other.coefs_[i]);

  for (auto i = smaller.coefs_.size(); i < bigger.coefs_.size(); ++i)
    result.coefs_.push_back(bigger.coefs_[i]);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator-(const Polinom& other) const
{
  const auto& bigger = (this->coefs_.size() >= other.coefs_.size() ? *this : other);
  const auto& smaller = (this->coefs_.size() < other.coefs_.size() ? *this : other);

  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(bigger.coefs_.size());

  for (auto i = 0; i < smaller.coefs_.size(); ++i)
    result.coefs_.push_back(this->coefs_[i] - other.coefs_[i]);

  if (bigger == *this)
    for (auto i = smaller.coefs_.size(); i < bigger.coefs_.size(); ++i)
      result.coefs_.push_back(bigger.coefs_[i]);
  else
    for (auto i = smaller.coefs_.size(); i < bigger.coefs_.size(); ++i)
      result.coefs_.push_back(-bigger.coefs_[i]);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator*(const Polinom& other) const
{
  auto coef_number = this->coefs_.size() + other.coefs_.size() - 1;
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(coef_number);

  for (long i = 0; i < coef_number; ++i) result.coefs_.push_back(0);

  for (long i = 0; i < this->coefs_.size(); ++i)
    for (long j = 0; j < other.coefs_.size(); ++j)
      result.coefs_[i + j] += this->coefs_[i] * other.coefs_[j];

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator-()
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(coefs_.size());

  for (const auto& el : coefs_)
    result.coefs_.push_back(-el);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator+=(const Polinom& other)
{
  return *this = *this + other;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator-=(const Polinom& other)
{
  return *this = *this - other;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator*=(const Polinom& other)
{
  return *this = *this * other;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator+(const coef_t& n) const
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(this->coefs_.size());

  for (const auto& el : this->coefs_) result.push_back(el + n);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator-(const coef_t& n) const
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(this->coefs_.size());

  for (const auto& el : this->coefs_) result.push_back(el - n);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator*(const coef_t& n) const
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(this->coefs_.size());

  for (const auto& el : this->coefs_) result.push_back(el * n);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::operator/(const coef_t& n) const
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(this->coefs_.size());

  for (const auto& el : this->coefs_) result.push_back(el / n);

  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator+=(const coef_t& n)
{
  return *this = *this + n;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator-=(const coef_t& n)
{
  return *this = *this - n;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator*=(const coef_t& n)
{
  return *this = *this * n;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t>& Polinom<value_t, coef_t>::operator/=(const coef_t& n)
{
  return *this = *this / n;
}

template <typename value_t, typename coef_t>
bool Polinom<value_t, coef_t>::operator==(const Polinom& other) const
{
  if (this->coefs_.size() != other.coefs_.size()) return false;
  for (int i = 0; i < this->coefs_.size(); ++i)
    if (this->coefs_[i] != other.coefs_[i]) return false;
  return true;
}

template <typename value_t, typename coef_t>
bool Polinom<value_t, coef_t>::operator!=(const Polinom& other) const
{
  return !(*this == other);
}

template <typename value_t, typename coef_t>
value_t Polinom<value_t, coef_t>::operator()(const value_t& value) const
{
  value_t result = 0;
  for (long i = 0; i < coefs_.size(); ++i)
    result += coefs_[i] * std::pow(value, i);
  return result;
}

template <typename value_t, typename coef_t>
Polinom<value_t, coef_t> Polinom<value_t, coef_t>::derivative() const
{
  Polinom<value_t, coef_t> result;
  result.coefs_.reserve(coefs_.size() - 1);

  for (long i = 1; i < coefs_.size(); ++i)
    result.coefs_.push_back(this->coefs_[i] * i);

  return result;
}

template <typename value_t, typename coef_t>
void Polinom<value_t, coef_t>::equalize_size(Polinom& p1, Polinom& p2)
{
  if (p1.coefs_.size() < p2.size)
    p1.coefs_.resize(p2.size, 0);
  else if (p1.coefs_.size() > p2.size)
    p2.coefs_.resize(p1.coefs_.size(), 0);
}
