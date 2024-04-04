#include "array.h"

#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  Array<std::string> moj_niz;

  std::string s1 { "Strukture" };
  std::string s2 { "Podataka" };

  // Ubacujem elemente s1 i s2 u niz
  moj_niz.push_back(s1);
  moj_niz.push_back(s2);

  // Međutim, ti elementi mi trebaju nakon operacije ubacivanja
  std::cout << s1 << " " << s2 << std::endl;

  std::string s3 = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris mollis "
    "ante in neque condimentum rhoncus. Phasellus nec quam ornare, commodo "
    "massa in, rutrum dui. Nullam arcu turpis, bibendum non dolor placerat, "
    "auctor posuere libero. Pellentesque quam dolor, rutrum at nunc in, "
    "convallis condimentum purus. Vivamus nec mattis arcu. Aenean eleifend, "
    "nunc at rhoncus rhoncus, justo sapien aliquam turpis, eu viverra ligula "
    "ipsum vel velit. Vestibulum id interdum lacus, nec finibus velit. Sed "
    "et dignissim velit. Sed eu ipsum sagittis nulla ultricies condimentum "
    "eget quis libero. Ut volutpat massa sit amet luctus ultrices. Etiam "
    "pulvinar tincidunt lorem sit amet condimentum. Morbi ultrices vitae "
    "enim in imperdiet. Maecenas vitae arcu placerat augue dignissim congue. "
    "Duis tempus in odio quis convallis. Proin volutpat lectus at tortor "
    "malesuada dapibus. Mauris fringilla fermentum dapibus. Maecenas rhoncus "
    "tincidunt tellus id porta. Aenean dapibus vestibulum lacus in "
    "fermentum. Praesent cras amet."
  };

  // Ubacujem element s3 u niz
  moj_niz.push_back(std::move(s3));
  // Ako znam da mi s3 više nije potreban nakon ove linije, kako mogu
  // optimizirati program
  std::cout << moj_niz[2] << std::endl;

  return 0;
}
