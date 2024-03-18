#include "firma.hpp"
#include "radnik.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <vector>

int main()
{
  Firma corp;
  corp.ucitaj_radnike("acme.txt");
  corp.ucitaj_radnike("globex.txt");
  std::cout << "Ucitano " << corp.size() << " osoba iz firmi acme i globex."
            << std::endl;
  // Ukupna plata prvi put.
  std::cout << "Ukupna plata: " << std::fixed << std::setprecision(2) << corp.ukupna_plata() << std::endl;
  // Obrisati osobe starije od 60 godina.
  for (auto it = corp.begin(); it != corp.end();)
  {
    if (it->godine() > 60)
      it = corp.erase(it--);
    else
      ++it;
  }
  // Povecati platu
  for (auto it = corp.begin(); it != corp.end(); ++it)
  {
    if (it->godineStaza() > 10)
      it->plata(it->plata() * 1.1);
    else if (it->godineStaza() > 5)
      it->plata(it->plata() * 1.05);
  }
  // Ukupna plata drugi put.
  std::cout << "Ukupna plata: " << std::fixed << std::setprecision(2) << corp.ukupna_plata() << std::endl;
  // Ispis u file corp.txt
  std::ofstream output("corp.txt");
  for (const auto& el : corp)
    output << el << std::endl;

  output.close();
}
