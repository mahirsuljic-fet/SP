#include "duration.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

Duration::Duration(size_t total_seconds)
{
  total_seconds_ = total_seconds;

  hours_ = total_seconds / 3600;
  total_seconds %= 3600;

  minutes_ = total_seconds / 60;
  total_seconds %= 60;

  seconds_ = total_seconds;
}

Duration::Duration(Hour hours, Minute minutes, Second seconds)
{
  set_h(hours);
  set_m(minutes);
  set_s(seconds);
  set_total_seconds_();
}

Duration::Duration(const std::string& input)
{
  int i = 0;
  for (char c : input)
    if (c == ':') ++i;

  if (i != 2) throw std::invalid_argument("Format nije validan.");

  std::string hours, minutes, seconds;

  i = 0;
  while (input[i] != ':') hours += input[i++];
  ++i;
  while (input[i] != ':') minutes += input[i++];
  ++i;
  while (input[i] != '\0') seconds += input[i++];

  set_h(std::stoi(hours));
  set_m(std::stoi(minutes));
  set_s(std::stoi(seconds));
}

Duration& Duration::set_s(Second seconds)
{
  if (seconds >= 60 || seconds < 0) throw std::out_of_range("Unos sekundi nije validan (0 <= seconds < 60).");
  seconds_ = seconds;

  set_total_seconds_();

  return *this;
}

Duration& Duration::set_m(Minute minutes)
{
  if (minutes >= 60 || minutes < 0) throw std::out_of_range("Unos minuta nije validan (0 <= minutes < 60).");
  minutes_ = minutes;

  set_total_seconds_();

  return *this;
}

Duration& Duration::set_h(Hour hours)
{
  if (hours < 0) throw std::out_of_range("Unos sati nije validan (hours >= 0).");
  hours_ = hours;

  set_total_seconds_();

  return *this;
}

void Duration::set_total_seconds_()
{
  total_seconds_ = hours_ * 3600 + minutes_ * 60 + seconds_;
}

bool Duration::operator==(const Duration& other) const
{
  return this->total_seconds_ == other.total_seconds_;
}

bool Duration::operator!=(const Duration& other) const
{
  return this->total_seconds_ != other.total_seconds_;
}

bool Duration::operator>(const Duration& other) const
{
  return this->total_seconds_ > other.total_seconds_;
}

bool Duration::operator<(const Duration& other) const
{
  return this->total_seconds_ < other.total_seconds_;
}

bool Duration::operator>=(const Duration& other) const
{
  return this->total_seconds_ >= other.total_seconds_;
}

bool Duration::operator<=(const Duration& other) const
{
  return this->total_seconds_ <= other.total_seconds_;
}

Duration Duration::operator+(const Duration& other)
{
  return Duration(this->total_seconds_ + other.total_seconds_);
}

Duration Duration::operator-(const Duration& other)
{
  if (other > *this) throw std::out_of_range("Nije dozvoljeno oduzimanje veceg objekta Duration od manjeg.");

  return Duration(this->total_seconds_ - other.total_seconds_);
}

Duration Duration::operator+(const Duration& other) const
{
  return Duration(this->total_seconds_ + other.total_seconds_);
}

Duration Duration::operator-(const Duration& other) const
{
  if (other > *this) throw std::out_of_range("Nije dozvoljeno oduzimanje veceg objekta Duration od manjeg.");

  return Duration(this->total_seconds_ - other.total_seconds_);
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

  return Duration(total_seconds_ * n);
}

Duration Duration::operator/(int n)
{
  if (n <= 0) throw std::out_of_range("Nije dozvoljeno dijeljenje objekta tipa Duration sa nulom i negativnim brojevima.");

  return Duration(total_seconds_ / n);
}

Duration Duration::operator*(int n) const
{
  if (n < 0) throw std::out_of_range("Nije dozvoljeno mnozenje objekta tipa Duration sa negativnim brojevima.");

  return Duration(total_seconds_ * n);
}

Duration Duration::operator/(int n) const
{
  if (n <= 0) throw std::out_of_range("Nije dozvoljeno dijeljenje objekta tipa Duration sa nulom i negativnim brojevima.");

  return Duration(total_seconds_ / n);
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
  output << unsigned(duration.get_m()) << ":";
  if (duration.get_s() < 10) output << "0";
  output << unsigned(duration.get_s());

  return output;
}

std::istream& operator>>(std::istream& input, Duration& duration)
{
  std::string input_data;

  input >> input_data;
  duration = input_data;

  return input;
}
