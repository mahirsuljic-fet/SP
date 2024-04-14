#include "array.h"
#include <algorithm>
#include <iostream>

template <typename T>
void print(Array<T> arr)
{
  std::cout << "<" << std::endl;
  for (auto iter = arr.begin(); iter != arr.end(); ++iter)
    std::cout << *iter << ", ";
  std::cout << ">" << std::endl;
}

int main(int argc, char* argv[])
{
  Array<int> moja_lista;

  for (int i = 1; i <= 10; i++)
    moja_lista.push_back(i);

  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  print(moja_lista);

  moja_lista.insert(moja_lista.begin() + 5, 100);
  print(moja_lista);

  moja_lista.erase(moja_lista.begin() + 5);
  print(moja_lista);

  return 0;
}
