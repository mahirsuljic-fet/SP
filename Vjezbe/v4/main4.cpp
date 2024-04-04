#include "array.h"

#include <algorithm>
#include <iostream>

int main(int argc, char* argv[])
{
  Array<int> moja_lista;

  moja_lista.push_back(1);
  moja_lista.push_back(2);
  moja_lista.push_back(3);

  std::cout << "Metod Front" << std::endl;
  std::cout << moja_lista.front() << std::endl;
  moja_lista.front() *= 100;
  std::cout << moja_lista.front() << std::endl;

  std::cout << "Metod Back" << std::endl;
  std::cout << moja_lista.back() << std::endl;
  moja_lista.back() *= 100;
  std::cout << moja_lista.front() << std::endl;

  std::cout << "Metod pop_back" << std::endl;
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;
  std::cout << "Pop back!" << std::endl;
  moja_lista.pop_back();
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  std::cout << "Metod clear" << std::endl;
  moja_lista.clear();
  std::cout << "Clear!" << std::endl;
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  moja_lista.push_back(1);
  moja_lista.push_back(2);
  moja_lista.push_back(3);
  moja_lista.push_back(4);
  moja_lista.push_back(5);
  moja_lista.push_back(6);
  moja_lista.push_back(7);
  moja_lista.push_back(8);
  moja_lista.push_back(9);
  moja_lista.push_back(10);
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  // Iteratori - print pomocu iteratora
  for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter)
    std::cout << *iter << " ";

  std::cout << std::endl;

  // Da bi find radio potreban je operator-: iter - iter
  auto iter = std::find(moja_lista.begin(), moja_lista.end(), 5);
  if (iter != moja_lista.end())
    std::cout << "Pronaden element: " << *iter << std::endl;

  // Partition - potreban operator-- i operator==
  std::partition(moja_lista.begin(), moja_lista.end(), [](auto el) { return el % 2; });
  std::cout << "Nakon partitiona" << std::endl;
  for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter)
    std::cout << *iter << " ";

  std::cout << std::endl;

  // Sort - potrebni operaori iter + n, iter - n, iter < iter
  std::sort(moja_lista.begin(), moja_lista.end());
  std::cout << "Nakon sorta" << std::endl;
  for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter)
    std::cout << *iter << " ";

  std::cout << std::endl;

  return 0;
}
