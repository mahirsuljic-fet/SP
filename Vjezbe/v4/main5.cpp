#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> moja_lista { 1, 3, 3, 4, 4, 2, 6, 5, 7, 8, 9 };

  // Problem - obrisati sve neparne brojeve iz niza
  // asimptotska slozenost O n ^ 2

  // Prvi nacin
  // for (auto it = moja_lista.begin(); it < moja_lista.end();)
  // {
  //   if (*it % 2)
  //     it = moja_lista.erase(it);
  //   else
  //     ++it;
  // }

  // Nacin sa std funkcijama
  // asimptotska slozenos O(n)
  auto it = std::remove_if(moja_lista.begin(), moja_lista.end(), [](auto el) { return el % 2; });
  moja_lista.erase(it, moja_lista.end());

  for (auto it = moja_lista.begin(); it < moja_lista.end(); ++it)
    std::cout << *it << " ";

  std::cout << std::endl;

  return 0;
}
