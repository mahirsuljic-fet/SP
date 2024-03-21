#include "array.h"

#include <iostream>
#include <stdexcept>

// void print(const Array& niz) {
//   for (auto i = 0; i < niz.size(); i++) {
//     std::cout << niz[i] << ", ";
//   }
//   std::cout << std::endl;
// }

int main()
{
  // Prvi dio - default konstruktor i konstruktor koji prima kapacitet.
  Array moj_niz;

  // Implementirati konstruktor koji prima kapacitet.
  // Array niz{200};

  // Pitanje: Šta je rezultat ove komande?
  // Array niz(-1);

  // Drugi dio - implementirati jednostavni push_back
  for (int i = 1; i < 11; i++)
    moj_niz.push_back(i);

  // Pitanje: Šta je rezultat ove komande?
  // try
  // {
  //   while (1) moj_niz.push_back(42);
  // }
  // catch (const std::out_of_range& err)
  // {
  //   std::cout << err.what() << std::endl;
  // }

  // Treći dio - size i operator[]
  // Implementirati operator[]
  // moj_niz[0] *= 100;
  // moj_niz[1] *= 100;

  // std::cout << "<" << moj_niz[0] << ", " << moj_niz[1] << ">" << std::endl;

  // Implementiati size()
  // for (auto i = 0; i < moj_niz.size(); i++) {
  //  std::cout << moj_niz[i] << ", ";
  //}
  // std::cout << std::endl;

  // Cetvrti dio - da li rješenje radi kod const Array& tipa
  // print(moj_niz);
  // std::cout << "Idemo dalje" << std::endl;

  // Peti dio - implementirati metod at te uhvatiti iznimku
  //  moj_niz.at(5);
  //  moj_niz.at(6);
  //  moj_niz.at(10);
  //  moj_niz.at(-1);
}
