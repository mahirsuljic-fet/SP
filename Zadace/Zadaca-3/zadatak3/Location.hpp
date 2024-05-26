#pragma once

#include <ostream>
#include <string>

class Location
{
  public:
    Location(const std::string&, double, double);
    Location(Location&&);
    Location(const Location&);
    Location& operator=(Location&&);
    Location& operator=(const Location&);
    ~Location() = default;

    bool operator==(const Location&) const;
    bool operator!=(const Location&) const;

    const std::string& name() const { return name_; }
    double latitude() const { return latitude_; }
    double longitude() const { return longitude_; }

    friend std::ostream& operator<<(std::ostream& out, const Location& location);
    friend class TripPlanner;

  private:
    Location() = default;
    std::string name_;
    double latitude_ = 0.0;
    double longitude_ = 0.0;
};
