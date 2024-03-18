#include "../functions.h"
#include "Rational.hpp"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void print_numbers(const std::vector<Rational>& numbers);
void tests();

int main(int argc, char* argv[])
{
  constexpr const char* FILE_NAME = "input.txt";
  std::vector<Rational> numbers;

  try
  {
    load_from_file(FILE_NAME, numbers);
    print_numbers(numbers);
    tests();
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Desila se nepoznata greska" << std::endl;
  }
}

void print_numbers(const std::vector<Rational>& numbers)
{
  std::cout << std::endl
            << "Ucitani brojevi:" << std::endl;
  for (auto el : numbers) std::cout << el << "  ";
  std::cout << std::endl
            << std::endl;
}

void tests()
{
  srand(time(NULL));

  int rand_n;
  Rational rand_r1, rand_r2;

  auto new_rand_const = [&rand_n]() { rand_n = std::rand() % 10 + 1; }; // generator random cijelih brojeva

  auto new_rand_rational = [&rand_r1, &rand_r2]() { // generator random racionalnih brojeva
    rand_r1 = Rational(std::rand() % 10, std::rand() % 9 + 1);
    rand_r2 = Rational(std::rand() % 10, std::rand() % 9 + 1);
  };

  // koristena je ova lambda da bi se pojedinacno za svaku operaciju hvatala i
  // tretirala iznimka i zbog skracenja i citljivosti koda ako je sve u jednom
  // try-catch bloku tada se ne izvrsi nista posle bacene iznimke
  auto try_func = [](const std::function<void(void)>& func) {
    try
    {
      func();
    }
    catch (const std::exception& err)
    {
      std::cout << err.what() << std::endl;
    }
    catch (...)
    {
      std::cout << "Desila se nepoznata greska" << std::endl;
    }
  };

  std::cout << "Operacije sa random brojevima:" << std::endl;

  try_func([&]() {
    new_rand_rational();
    std::cout << rand_r1 << "\t+\t" << rand_r2 << "\t= " << rand_r1 + rand_r2 << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    std::cout << rand_r1 << "\t-\t" << rand_r2 << "\t= " << rand_r1 - rand_r2 << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    new_rand_const();
    std::cout << rand_r1 << "\t*\t" << rand_r2 << "\t= " << rand_r1 * rand_r2 << std::endl;
    std::cout << rand_r1 << "\t*\t" << rand_n << "\t= " << rand_r1 * rand_n << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    new_rand_const();
    std::cout << rand_r1 << "\t/\t" << rand_r2 << "\t= " << rand_r1 / rand_r2 << std::endl;
    std::cout << rand_r1 << "\t/\t" << rand_n << "\t= " << rand_r1 / rand_n << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    std::cout << rand_r1 << "\t==\t" << rand_r1 << "\t= " << ((rand_r1 == rand_r1) ? "true" : "false") << std::endl;
    std::cout << rand_r1 << "\t!=\t" << rand_r1 << "\t= " << ((rand_r1 != rand_r1) ? "true" : "false") << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    std::cout << rand_r1 << "\t==\t" << rand_r2 << "\t= " << ((rand_r1 == rand_r2) ? "true" : "false") << std::endl;
    std::cout << rand_r1 << "\t!=\t" << rand_r2 << "\t= " << ((rand_r1 != rand_r2) ? "true" : "false") << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    new_rand_const();
    std::cout << rand_r1 << "\t^\t" << rand_n << "\t= " << (rand_r1 ^ rand_n) << std::endl;
    std::cout << rand_r1 << "\t^\t" << -rand_n << "\t= " << (rand_r1 ^ -rand_n) << std::endl;
    std::cout << rand_r1 << "\t^\t" << '0' << "\t= " << (rand_r1 ^ 0) << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    std::cout << "(" << rand_r1 << ")++\t= " << rand_r1++ << "\t->\t" << rand_r1 << std::endl;
    std::cout << "++(" << rand_r2 << ")\t= " << ++rand_r2 << "\t->\t" << rand_r2 << std::endl;
  });
  try_func([&]() {
    new_rand_rational();
    std::cout << "(" << rand_r1 << ")--\t= " << rand_r1-- << "\t->\t" << rand_r1 << std::endl;
    std::cout << "--(" << rand_r2 << ")\t= " << --rand_r2 << "\t->\t" << rand_r2 << std::endl;
  });
}
