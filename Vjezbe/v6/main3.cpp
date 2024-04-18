#include <iostream>
#include <list>

int main()
{
  std::list<int> moja_lista { 1, 2, 3, 4, 5 };

  for (auto it = moja_lista.begin(); it != moja_lista.end(); ++it)
    std::cout << *it << std::endl;

  auto it = moja_lista.end();
  it--;
}
