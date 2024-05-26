#include "Location.hpp"
#include <algorithm>

Location::Location(const std::string& name, double latitude, double longitude)
  : name_ { name }, latitude_ { latitude }, longitude_ { longitude } { }

Location::Location(Location&& other)
  : name_ { std::move(other.name_) }, latitude_ { other.latitude_ }, longitude_ { other.longitude_ } { }

Location::Location(const Location& other)
  : name_ { other.name_ }, latitude_ { other.latitude_ }, longitude_ { other.longitude_ } { }

Location& Location::operator=(Location&& other)
{
  this->name_ = std::move(other.name_);
  this->latitude_ = other.latitude_;
  this->longitude_ = other.longitude_;
  return *this;
}

Location& Location::operator=(const Location& other)
{
  this->name_ = other.name_;
  this->latitude_ = other.latitude_;
  this->longitude_ = other.longitude_;
  return *this;
}

bool Location::operator==(const Location& other) const
{
  return this->name_ == other.name_ && this->latitude_ == other.latitude_ && this->longitude_ == other.longitude_;
}

bool Location::operator!=(const Location& other) const
{
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Location& location)
{
  return out << "Name: " << location.name_ << std::endl
             << "Latitude:  " << location.latitude_ << std::endl
             << "Longitude: " << location.longitude_ << std::endl;
}
