#include "array.h"
#include <iostream>

template <typename T>
void print(Array<T> arr)
{
  std::cout << "<" << std::endl;
  for (auto iter = arr.begin(); iter != arr.end(); ++iter)
    std::cout << *iter << ", ";
  std::cout << ">" << std::endl;
}

int main()
{
  Array<int> moj_niz;
  // Drugi dio - implementirati jednostavni push_back
  for (int i = 1; i < 5000; i++)
    moj_niz.push_back(i);

  std::cout << "Size: " << moj_niz.size() << std::endl;

  Array<int> moj_niz1;
  for (int i = 1; i < 10; i++)
    moj_niz1.push_back(i);

  moj_niz1.resize(20, 0);
  for (auto iter = moj_niz1.begin(); iter != moj_niz1.end(); ++iter)
    std::cout << *iter << ", ";
  std::cout << std::endl;
}
