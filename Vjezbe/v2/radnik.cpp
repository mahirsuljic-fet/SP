#include "radnik.hpp"
#include <string>

// Napomena: vidimo privatne clanove zbog friend deklaracije.
std::ostream& operator<<(std::ostream& out, const Radnik& radnik)
{
  return out << radnik.ime() << "," << radnik.prezime() << ","
             << radnik.godine() << "," << radnik.godineStaza() << ","
             << radnik.plata() << "," << radnik.brojTelefona();
}

// Napomena: vidimo privatne clanove zbog friend deklaracije.
std::istream& operator>>(std::istream& in, Radnik& r)
{
  std::getline(in, r.ime_, ',');
  std::getline(in, r.prezime_, ',');

  std::string temp;
  std::getline(in, temp, ',');
  r.godine_ = std::stoi(temp);

  std::getline(in, temp, ',');
  r.godine_staza_ = std::stoi(temp);

  std::getline(in, temp, ',');
  r.plata_ = std::stod(temp);

  std::getline(in, r.broj_telefona_);

  return in;
}
