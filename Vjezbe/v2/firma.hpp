#pragma once

#include "radnik.hpp"

#include <vector>

class Firma : public std::vector<Radnik>
{
  public:
    bool ucitaj_radnike(const std::string& file);

    double ukupna_plata() const;
};
