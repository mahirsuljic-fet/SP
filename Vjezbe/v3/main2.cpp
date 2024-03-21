#include "array.h"

#include <algorithm>
#include <iostream>

void short_print(const Array& niz)
{
  std::cout << niz[0] << ", " << niz[1] << ", ..., " << niz[niz.size() - 2]
            << ", " << niz[niz.size() - 1] << std::endl;
}

int main(int argc, char* argv[])
{
  Array moja_lista;

  for (size_t i = 0; i < 10; i++)
  {
    moja_lista.push_back(i);
  }
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  // copy ctor
  Array list1(moja_lista);
  Array list2 = moja_lista;
  Array list3 { moja_lista };

  std::cout << "Broj elemenata: " << list1.size() << std::endl;
  short_print(list1);
  short_print(list2);
  short_print(list3);

  // move ctor
  Array list4 { std::move(moja_lista) };
  Array list5 = std::move(list1);
  short_print(list4);
  short_print(list5);

  // copy assignment
  list1 = list4;
  short_print(list1);

  // move assignment
  list3 = std::move(list4);
  list2 = std::move(list5);

  for (size_t i = 0; i < list2.size(); i++)
    std::cout << list2[i] << std::endl;

  // self assignment
  list2 = list2;
  std::cout << "Ispis sadzaja list2" << std::endl;
  for (size_t i = 0; i < list2.size(); i++)
    std::cout << list2[i] << std::endl;

  // Pitanje: self assignment za move op=
  list2 = std::move(list2);
  std::cout << "Ispis sadzaja list2" << std::endl;
  for (size_t i = 0; i < list2.size(); i++)
    std::cout << list2[i] << std::endl;

  return 0;
}
