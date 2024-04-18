#include "list.hpp"

#include <iostream>

int main()
{
  List<int> moja_lista;

  for (int i = 3; i <= 5; i++)
    moja_lista.push_back(i);
  for (int i = 2; i >= 1; i--)
    moja_lista.push_front(i);

  std::cout << moja_lista.size() << " == 5" << std::endl;
  moja_lista.print();

  // Pravilo petorke.
  auto moja_lista2 = moja_lista;
  moja_lista2.print();
  auto moja_lista3 = std::move(moja_lista2);
  moja_lista3.print();
  moja_lista2 = std::move(moja_lista3);
  moja_lista2.print();
  moja_lista3 = moja_lista;
  moja_lista3.print();

  // Brisanje iz liste.
  std::cout << "test pop back" << std::endl;
  while (!moja_lista2.empty())
    moja_lista2.pop_back();
  moja_lista2.print();
  std::cout << "kraj testa" << std::endl;

  std::cout << "test pop front" << std::endl;
  while (!moja_lista3.empty())
    moja_lista3.pop_front();
  moja_lista3.print();
  std::cout << "kraj testa" << std::endl;

  std::cout << "Metod at" << std::endl;
  try
  {
    std::cout << moja_lista.at(0) << ", " << moja_lista.at(1) << ", "
              << moja_lista.at(2) << ", " << moja_lista.at(3) << ", "
              << moja_lista.at(4) << ", " << moja_lista.at(5) << std::endl;
  }
  catch (...)
  {
    std::cout << "Ups" << std::endl;
  }

  // std::cout << "Iteratori" << std::endl;
  // auto begin = moja_lista3.begin();
  // std::cout << moja_lista3.at(0) << std::endl;
  // std::cout << *begin << std::endl;
  // std::cout << *++begin << std::endl;
  //
  // std::cout << "Iteratori 2" << std::endl;
  // for (auto iter = moja_lista3.begin(); iter != moja_lista3.end(); ++iter) {
  //   std::cout << *iter << std::endl;
  // }
}
