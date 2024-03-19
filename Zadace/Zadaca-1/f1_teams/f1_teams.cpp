#include "f1_teams.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

F1_Team::F1_Team(std::string data)
{
  std::string name, country, year, champs, budget;

  // trim end
  while (data.back() == '\r' || data.back() == '\n' || data.back() == ' ') data.pop_back();
  if (data.back() == ',') throw std::invalid_argument("Greska pri citanju \"" + data + "\": nedostaje argument.");

  auto c = data.begin();                        // trenutni karakter
  while (*c != ',' && *c != '\0') name += *c++; // prolaz kroz string
  team_name_ = name;

  if (*c++ == '\0') return; // provjera kraja i prekoracenje zareza
  while (*c != ',' && *c != '\0') country += *c++;
  country_of_origin_ = country;

  if (*c++ == '\0') return;
  while (*c != ',' && *c != '\0') year += *c++;
  year_founded_ = std::stoi(year);

  if (*c++ == '\0') return;
  while (*c != ',' && *c != '\0') champs += *c++;
  number_of_championships_ = std::stoi(champs);

  if (*c++ == '\0') return;
  while (*c != '\0') budget += *c++;
  team_budget_million_usd_ = std::stoi(budget);
}

F1_Team& F1_Team::team_name(const std::string& name)
{
  team_name_ = name;
  return *this;
}

F1_Team& F1_Team::country_of_origin(const std::string& country)
{
  country_of_origin_ = country;
  return *this;
}

F1_Team& F1_Team::year_founded(unsigned short year)
{
  year_founded_ = year;
  return *this;
}

F1_Team& F1_Team::number_of_championships(unsigned short championships)
{
  number_of_championships_ = championships;
  return *this;
}

F1_Team& F1_Team::team_budget_million_usd(unsigned short budget)
{
  team_budget_million_usd_ = budget;
  return *this;
}

std::ostream& operator<<(std::ostream& output, const F1_Team& team)
{
  return output << team.team_name_ << ", "
                << team.country_of_origin_ << ", "
                << team.year_founded_ << ", "
                << team.number_of_championships_ << ", "
                << team.team_budget_million_usd_;
}
