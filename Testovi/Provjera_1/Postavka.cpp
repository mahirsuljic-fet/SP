#include <iomanip>
#include <iostream>
#include <stdexcept>

class Duration
{
  public:
    Duration() = default;

    // Vas kod ovdje

  private:
    friend std::ostream& operator<<(std::ostream& out, const Duration& dd);

    int s = 0;
    int m = 0;
    int h = 0;
};

std::ostream& operator<<(std::ostream& out, const Duration& dd)
{
  out << std::setfill('0') << std::setw(2) << dd.h << ':' << std::setfill('0')
      << std::setw(2) << dd.m << ':' << std::setfill('0') << std::setw(2)
      << dd.s;
  return out;
}

int main()
{
  // Napraviti konstruktor koji prima jednu vrijednost tipa int - 10%

  // Duration x{51636};
  // std::cout << x << std::endl; // ispis 14:20:36

  // Baciti iznimku kod negativnih vrijednosti - 10%

  // try {
  //   Duration d1{-1000};
  //   std::cout << "Iznimka FAIL" << std::endl;
  // } catch (...) {
  //   std::cout << "Iznimka OK" << std::endl;
  // }

  // Implementirati *= sa cijelim brojem - 20%

  // Duration t{120};
  // t *= 30;
  // std::cout << t << std::endl; // ispis: 01:00:00
  //
  // auto& k = t *= 15;
  // std::cout << k << std::endl; // ispis: 15:00:00

  // Implementirati operator += sa drugim Duration tipom - 20%

  // Duration y{51636};
  // y += x;
  // std::cout << y << std::endl; // ispis: 28:41:12
  //
  // auto& r = y += x;
  // std::cout << r << std::endl; // ispis: 43:01:48

  // Napraviti metod koji dodaje broj sekundi na trenutno vrijeme - 20%

  // x.add_seconds(3730);
  // std::cout << x << std::endl; // ispis 15:22:46

  // Implementirati operator - koji oduzima dva durationa i vraća natrag
  // broj sekundi koje su protekle od prvog do drugog termina. - 20%

  // Duration z{51636};
  // int elapsed = x - z;
  // std::cout << elapsed << std::endl; // Ispis 3730
  // elapsed = z - x;
  // std::cout << elapsed << std::endl; // Ispis -3730

  return 0;
}
