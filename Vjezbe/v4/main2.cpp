#include "array.h"

#include <algorithm>
#include <iostream>

template <typename T>
void short_print(const char* ime, const Array<T>& niz)
{
  std::cout << ime << " velicina: " << niz.size() << " <" << niz[0] << ", "
            << niz[1] << ", ..., " << niz[niz.size() - 2] << ", "
            << niz[niz.size() - 1] << ">" << std::endl;
}

int main(int argc, char* argv[])
{
  Array<int> moja_lista;

  for (size_t i = 0; i < 10; i++)
  {
    moja_lista.push_back(i);
  }

  std::cout << "Prvi dio - copy ctor" << std::endl;
  // Načini poziva copy ctor-a
  // Array<int> list1(moja_lista);
  // Array<int> list1 = moja_lista;
  Array<int> list1 { moja_lista };

  short_print("moja_lista", moja_lista);
  short_print("list1", list1);

  std::cout << "\nPovecavam prvi element objekta moja_lista" << std::endl;
  moja_lista[0] += 50;

  short_print("moja_lista", moja_lista);
  short_print("list1", list1);

  std::cout << "Drugi dio - move ctor" << std::endl;
  Array<int> list2 { std::move(moja_lista) };
  auto list3 = std::move(list1);
  short_print("list2", list2);
  short_print("list3", list3);

  // Sta je sa objektoima
  // moja_lista i list1
  // Kako bi zavrsila instrukcija std::cout << list1[0] << std::endl;

  std::cout << "Treci dio - copy assignment" << std::endl;
  moja_lista = list2;
  short_print("moja_lista", moja_lista);
  short_print("lista2", list2);

  std::cout << "Self assignment - specijalni slucaj" << std::endl;
  moja_lista = moja_lista;
  short_print("moja_lista", moja_lista);

  // std::cout << "Cetvrti dio - move assignment" << std::endl;
  list1 = std::move(list3);
  short_print("list1", list1);

  // std::cout << "Self assignment - specijalni slucaj" << std::endl;
  moja_lista = std::move(moja_lista);
  short_print("moja_lista", moja_lista);

  return 0;
}
