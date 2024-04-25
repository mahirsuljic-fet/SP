#include "list.hpp"
#include <iostream>

int main()
{
  List<std::string> lista;
  lista.push_back("Strukture");
  lista.push_back("Podataka");
  lista.push_back("2024");
  lista.push_back(" - ");
  lista.push_back("Sredina");
  lista.push_back("semestra");

  for (auto iter = lista.begin(); iter != lista.end(); ++iter)
    std::cout << *iter << std::endl;

  auto pos = lista.begin();
  pos++;
  pos++;
  lista.insert(pos, "Zadaca");
  lista.insert(lista.begin(), "Poruka: ");
  lista.erase(++lista.begin());
  lista.erase(lista.begin());
  for (auto iter = lista.begin(); iter != lista.end(); ++iter)
    std::cout << *iter << std::endl;
}
