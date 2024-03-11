#include "duration.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

Duration::Duration(Second seconds)
{
  hours_ = seconds / 3600;
  seconds %= 3600;

  minutes_ = seconds / 60;
  seconds %= 60;

  seconds_ = seconds;
}

Duration::Duration(Hour hours, Minute minutes, Second seconds)
{
  hours_ = hours;

  if (minutes >= 60) throw std::out_of_range("Unos minuta nije validan (0 <= minutes < 60).");
  minutes_ = minutes;

  if (seconds >= 60) throw std::out_of_range("Unos sekundi nije validan (0 <= seconds < 60).");
  seconds_ = seconds;
}

Duration::Duration(const std::string& input)
{
  if (input.size() != 8 || input[2] != ':' || input[5] != ':')
    throw std::invalid_argument("Format nije validan.");

  std::string hours { input[0], input[1] };
  std::string minutes { input[3], input[4] };
  std::string seconds { input[6], input[7] };

  hours_ = std::stoi(hours);
  minutes_ = std::stoi(minutes);
  seconds_ = std::stoi(seconds);
}

Duration& Duration::set_s(Second seconds)
{
  if (seconds >= 60) throw std::out_of_range("Unos sekundi nije validan (0 <= seconds < 60).");
  seconds_ = seconds;

  return *this;
}

Duration& Duration::set_m(Minute minutes)
{
  if (minutes >= 60) throw std::out_of_range("Unos minuta nije validan (0 <= minutes < 60).");
  minutes_ = minutes;

  return *this;
}

Duration& Duration::set_h(Hour hours)
{
  hours_ = hours;

  return *this;
}

bool Duration::operator==(const Duration& other) const
{
  return this->hours_ == other.hours_ && this->minutes_ == other.minutes_ && this->seconds_ == other.seconds_;
}

bool Duration::operator!=(const Duration& other) const
{
  return this->hours_ != other.hours_ || this->minutes_ != other.minutes_ || this->seconds_ != other.seconds_;
}

bool Duration::operator>(const Duration& other) const
{
  if (this->hours_ > other.hours_) return true;
  if (this->hours_ < other.hours_) return false;

  if (this->minutes_ > other.minutes_) return true;
  if (this->minutes_ < other.minutes_) return false;

  if (this->seconds_ > other.seconds_) return true;
  return false;
}

bool Duration::operator<(const Duration& other) const
{
  if (this->hours_ < other.hours_) return true;
  if (this->hours_ > other.hours_) return false;

  if (this->minutes_ < other.minutes_) return true;
  if (this->minutes_ > other.minutes_) return false;

  if (this->seconds_ < other.seconds_) return true;
  return false;
}

bool Duration::operator>=(const Duration& other) const
{
  if (this->hours_ > other.hours_) return true;
  if (this->hours_ < other.hours_) return false;

  if (this->minutes_ > other.minutes_) return true;
  if (this->minutes_ < other.minutes_) return false;

  if (this->seconds_ >= other.seconds_) return true;
  return false;
}

bool Duration::operator<=(const Duration& other) const
{
  if (this->hours_ < other.hours_) return true;
  if (this->hours_ > other.hours_) return false;

  if (this->minutes_ < other.minutes_) return true;
  if (this->minutes_ > other.minutes_) return false;

  if (this->seconds_ <= other.seconds_) return true;
  return false;
}

Duration Duration::operator+(const Duration& other)
{
  Second seconds = this->seconds_ + other.seconds_;
  Minute minutes = this->minutes_ + other.minutes_;
  Hour hours = this->hours_ + other.hours_;

  if (seconds >= 60)
  {
    seconds %= 60;
    ++minutes;
  }

  if (minutes >= 60)
  {
    minutes %= 60;
    ++hours;
  }

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator-(const Duration& other)
{
  if (other > *this) throw std::out_of_range("Nije dozvoljeno oduzimanje veceg objekta Duration od manjeg.");

  Second seconds = this->seconds_ - other.seconds_;
  Minute minutes = this->minutes_ - other.minutes_;
  Hour hours = this->hours_ - other.hours_;

  if (seconds < 0)
  {
    seconds += 60;
    --minutes;
  }

  if (minutes < 0)
  {
    minutes += 60;
    --hours;
  }

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator+(const Duration& other) const
{
  Second seconds = this->seconds_ + other.seconds_;
  Minute minutes = this->minutes_ + other.minutes_;
  Hour hours = this->hours_ + other.hours_;

  if (seconds >= 60)
  {
    seconds %= 60;
    ++minutes;
  }

  if (minutes >= 60)
  {
    minutes %= 60;
    ++hours;
  }

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator-(const Duration& other) const
{
  if (other > *this) throw std::out_of_range("Nije dozvoljeno oduzimanje veceg objekta Duration od manjeg.");

  Second seconds = this->seconds_ - other.seconds_;
  Minute minutes = this->minutes_ - other.minutes_;
  Hour hours = this->hours_ - other.hours_;

  if (seconds < 0)
  {
    seconds += 60;
    --minutes;
  }

  if (minutes < 0)
  {
    minutes += 60;
    --hours;
  }

  return Duration(hours, minutes, seconds);
}

Duration& Duration::operator+=(const Duration& other)
{
  return *this = *this + other;
}

Duration& Duration::operator-=(const Duration& other)
{
  return *this = *this - other;
}

Duration Duration::operator*(int n)
{
  if (n < 0) throw std::out_of_range("Nije dozvoljeno mnozenje objekta tipa Duration sa negativnim brojevima.");

  Second seconds = this->seconds_ * n;
  Minute minutes = this->minutes_ * n;
  Hour hours = this->hours_ * n;

  if (seconds >= 60)
  {
    minutes += seconds / 60;
    seconds %= 60;
  }

  if (minutes >= 60)
  {
    hours += minutes / 60;
    minutes %= 60;
  }

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator/(int n)
{
  if (n <= 0) throw std::out_of_range("Nije dozvoljeno dijeljenje objekta tipa Duration sa nulom i negativnim brojevima.");

  Second seconds = this->seconds_ / n;
  Minute minutes = this->minutes_ / n;
  Hour hours = this->hours_ / n;

  double remainder_seconds = (double)this->seconds_ / n - seconds;
  double remainder_minutes = (double)this->minutes_ / n - minutes;
  double remainder_hours = (double)this->hours_ / n - hours;

  minutes += remainder_hours * 60;
  seconds += remainder_hours * 3600 + remainder_minutes * 60 + std::round(remainder_seconds);

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator*(int n) const
{
  if (n < 0) throw std::out_of_range("Nije dozvoljeno mnozenje objekta tipa Duration sa negativnim brojevima.");

  Second seconds = this->seconds_ * n;
  Minute minutes = this->minutes_ * n;
  Hour hours = this->hours_ * n;

  if (seconds >= 60)
  {
    minutes += seconds / 60;
    seconds %= 60;
  }

  if (minutes >= 60)
  {
    hours += minutes / 60;
    minutes %= 60;
  }

  return Duration(hours, minutes, seconds);
}

Duration Duration::operator/(int n) const
{
  if (n <= 0) throw std::out_of_range("Nije dozvoljeno dijeljenje objekta tipa Duration sa nulom i negativnim brojevima.");

  Second seconds = this->seconds_ / n;
  Minute minutes = this->minutes_ / n;
  Hour hours = this->hours_ / n;

  double remainder_seconds = (double)this->seconds_ / n - seconds;
  double remainder_minutes = (double)this->minutes_ / n - minutes;
  double remainder_hours = (double)this->hours_ / n - hours;

  minutes += remainder_hours * 60;
  seconds += remainder_hours * 3600 + remainder_minutes * 60 + std::round(remainder_seconds);

  return Duration(hours, minutes, seconds);
}

Duration& Duration::operator*=(int n)
{
  return *this = *this * n;
}

Duration& Duration::operator/=(int n)
{
  return *this = *this / n;
}

std::ostream& operator<<(std::ostream& output, const Duration& duration)
{
  if (duration.get_h() < 10) output << "0";
  output << duration.get_h() << ":";
  if (duration.get_m() < 10) output << "0";
  output << duration.get_m() << ":";
  if (duration.get_s() < 10) output << "0";
  output << duration.get_s();

  return output;
}

std::istream& operator>>(std::istream& input, Duration& duration)
{
  std::string input_data;

  input >> input_data;
  duration = input_data;

  return input;
}
