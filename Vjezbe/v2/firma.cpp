#include "firma.hpp"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

bool Firma::ucitaj_radnike(const std::string& file)
{
  std::ifstream input(file);

  if (!input)
  {
    std::cout << "Error: nije moguce otvoriti fajl." << std::endl;
    return false;
  }

  std::string temp;
  std::getline(input, temp);

  Radnik r;
  while (std::getline(input, temp))
  {
    std::stringstream ssin { temp };
    ssin >> r;
    push_back(r);
  }

  input.close();
  return true;
}

double Firma::ukupna_plata() const
{
  double sum = 0.0;
  for (const auto& radnik : *this)
    sum += radnik.plata();

  return sum;
}
