#include "../functions.h"
#include "f1_teams.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void sort_filter_teams(std::vector<F1_Team>& teams);

int main(int argc, char* argv[])
{
  constexpr const char* INPUT_FILE = "f1_teams.csv";
  constexpr const char* OUTPUT_FILE = "f1_teams_sorted.csv";
  std::vector<F1_Team> teams;

  try
  {
    load_from_file(INPUT_FILE, teams);
    sort_filter_teams(teams);
    store_to_file(OUTPUT_FILE, teams);
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Desila se nepoznata greska" << std::endl;
  }

  return 0;
}

void sort_filter_teams(std::vector<F1_Team>& teams)
{
  // sort
  auto sort_lambda = [](const F1_Team& team1, const F1_Team& team2) { return team1.number_of_championships() > team2.number_of_championships(); };
  std::sort(teams.begin(), teams.end(), sort_lambda);

  // filter duplicates
  auto it = teams.begin();
  auto it_other = teams.begin();
  while (it != teams.end())
  {
    ++it_other;

    if (it->team_name() == it_other->team_name() && it->country_of_origin() == it_other->country_of_origin())
    {
      it->year_founded(std::min(it->year_founded(), it_other->year_founded()));
      it->number_of_championships(it->number_of_championships() + it_other->number_of_championships());
      it->team_budget_million_usd(it->team_budget_million_usd() + it_other->team_budget_million_usd());

      teams.erase(it_other);
    }

    if (it_other == teams.end())
      it_other = ++it;
  }

  // filter championships
  it = teams.begin();
  while (it->number_of_championships() > 0) ++it;
  teams.erase(it, teams.end());
}
