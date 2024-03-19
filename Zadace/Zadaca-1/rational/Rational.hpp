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

class Rational
{
  public:
    Rational();
    Rational(int numerator, int denominator);
    Rational(const char* rational);
    Rational(const std::string&);
    Rational(const Rational& rational);
    Rational(Rational&& rational);

    Rational& operator=(const Rational& other);
    Rational& operator=(Rational&& other);
    Rational operator+(const Rational& other) const;
    Rational operator+(int numerator) const;
    Rational operator-(const Rational& other) const;
    Rational operator-(int numerator) const;
    Rational operator*(const Rational& other) const;
    Rational operator*(int numerator) const;
    Rational operator/(const Rational& other) const;
    Rational operator/(int numerator) const;
    Rational operator^(int) const;
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    bool operator==(const Rational& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const Rational& other) const;
    bool operator!=(const char* other) const;

    const int numerator() const { return numerator_; }
    const int denominator() const { return denominator_; }

    ~Rational() = default;

  private:
    long numerator_;
    long denominator_;
};

std::ostream& operator<<(std::ostream& output, const Rational& rational);
