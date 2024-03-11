#pragma once
#include <ostream>

/*! \class Rational
 *
 *  Klasa Rational simulira rad sa racionalnim brojevima.
 *  Stanje ove klase cine dva cijela broja: brojnik i nazivnik.
 *  Sve operacije moraju bit optimialne, sto znaci da ako je moguce i brojnik i
 * nazivnik treba skratiti na najmanju mogucu vrijednost, na primjer: 10/12 je
 * neophodno prikazati kao 5/6 nakon kracenja sa 2.
 * Ne dozvoliti da nazivnik bude 0!
 */

class Rational {
  public:
  // Numerator 0, denominator 1
  Rational();
  // denominator should not be 0!
  Rational(int numerator, int denominator);
  // Split const char* by / delimiter
  Rational(const char* rational);
  Rational(const std::string&);
  // copy constructor
  Rational(const Rational& rational);
  // Move constructor
  Rational(Rational&& rational);
  // Copy op=
  Rational& operator=(const Rational& rational);
  // Move op=
  Rational& operator=(Rational&& rational);
  // Return optimal rational number
  // 2/3 + 4/3, operator should return 3/1.
  // std::cout should print it as 3, not 3/1!
  Rational operator+(const Rational& rational) const;
  Rational operator+(int numerator) const;
  Rational operator-(const Rational& rational) const;
  Rational operator-(int numerator) const;
  // Rational multiplication
  Rational operator*(const Rational& rational) const;
  Rational operator*(int numerator) const;
  // Rational division
  Rational operator/(const Rational& rational) const;
  Rational operator/(int numerator) const;
  // Pow operator: (4/3) ^ 2 = (16/9);
  Rational operator^(int) const;
  // Prefix operator++, increase rational number by 1
  Rational& operator++();
  // Postfix operator++, increase rational number by 1
  Rational operator++(int);
  // Prefix operator--, decrease rational number by 1
  Rational& operator--();
  // Postfix operator--, decrease rational number by 1
  Rational operator--(int);
  bool operator==(const Rational& rational) const;
  bool operator==(const char* rational) const;
  bool operator!=(const Rational& rational) const;
  bool operator!=(const char* rational) const;
  // Get numerator
  const int numerator() const;
  // Get denominator
  const int denominator() const;

  ~Rational();

  private:
  int numerator_;   // brojnik
  int denominator_; // nazivnik
};

// Example:
// 5/1 should be printed as 5!
// 10/5 should be printed as 2
// 12/8 should be printed as 3/2
std::ostream& operator<<(std::ostream& os, const Rational& rational);
// You could use gcd(numerator, denominator) to find the greatest common
// divisior gcd will return the greatest number that we should use to divide
// numerator and denominator(Normalization)
int gcd(const int numerator, const int denominator);
