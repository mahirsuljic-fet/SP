#pragma once

#include <cstddef>
#include <cstdint>
#include <istream>
#include <ostream>
#include <string>

using Second = int8_t;
using Minute = int8_t;
using Hour = int32_t;

class Duration
{
  public:
    Duration() : hours_(0), minutes_(0), seconds_(0) { }
    Duration(size_t total_seconds);
    Duration(Hour hours, Minute minutes, Second seconds);
    Duration(const std::string& input);

    Second get_s() const { return seconds_; }
    Minute get_m() const { return minutes_; }
    Hour get_h() const { return hours_; }
    Duration& set_s(Second seconds);
    Duration& set_m(Minute minutes);
    Duration& set_h(Hour hours);

    explicit operator bool() const { return hours_ && minutes_ && seconds_; }
    bool operator!() const { return !(hours_ && minutes_ && seconds_); }
    bool operator==(const Duration& other) const;
    bool operator!=(const Duration& other) const;
    bool operator>=(const Duration& other) const;
    bool operator<=(const Duration& other) const;
    bool operator>(const Duration& other) const;
    bool operator<(const Duration& other) const;
    Duration operator+(const Duration& other);
    Duration operator-(const Duration& other);
    Duration operator+(const Duration& other) const;
    Duration operator-(const Duration& other) const;
    Duration& operator+=(const Duration& other);
    Duration& operator-=(const Duration& other);
    Duration operator*(int n);
    Duration operator/(int n);
    Duration operator*(int n) const;
    Duration operator/(int n) const;
    Duration& operator*=(int n);
    Duration& operator/=(int n);

  private:
    Hour hours_ = 0;
    Minute minutes_ = 0;
    Second seconds_ = 0;
    size_t total_seconds_ = 0;
    void set_total_seconds_();
};

std::ostream& operator<<(std::ostream& output, const Duration& duration);
std::istream& operator>>(std::istream& input, Duration& duration);
