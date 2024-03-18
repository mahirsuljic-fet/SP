#pragma once

#include <iostream>
#include <ostream>
#include <string>

class F1_Team
{
  public:
    F1_Team(std::string data);

    std::string team_name() const { return team_name_; }
    std::string country_of_origin() const { return country_of_origin_; }
    unsigned short year_founded() const { return year_founded_; }
    unsigned short number_of_championships() const { return number_of_championships_; }
    unsigned short team_budget_million_usd() const { return team_budget_million_usd_; }

    F1_Team& team_name(const std::string& name);
    F1_Team& country_of_origin(const std::string& country);
    F1_Team& year_founded(unsigned short year);
    F1_Team& number_of_championships(unsigned short championships);
    F1_Team& team_budget_million_usd(unsigned short budget);

    friend std::ostream& operator<<(std::ostream& output, const F1_Team& team);

  private:
    std::string team_name_;
    std::string country_of_origin_;
    unsigned short year_founded_ = 0;
    unsigned short number_of_championships_ = 0;
    unsigned short team_budget_million_usd_ = 0;
};
