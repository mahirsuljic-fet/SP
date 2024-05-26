#include "Number.hpp"
#include <iostream>

int main()
{
  // Kreiranje brojeva za testiranje
  Number num1(123);
  Number num2(-456);

  // Testiranje operatora +, -, +=, -= sa drugim brojevima
  Number sum = num1 + num2;
  Number diff = num1 - num2;
  sum += diff;
  diff -= sum;

  // Testiranje operatora +, -, +=, -= sa konstantnim vrednostima
  sum = sum + 100;
  diff = diff - 50;
  sum += 200;
  diff -= 300;

  // Testiranje operatora ==, !=, >, <, >=, <= sa drugim brojevima
  bool equal = (num1 == num2);
  bool not_equal = (num1 != num2);
  bool greater = (num1 > num2);
  bool less = (num1 < num2);
  bool greater_equal = (num1 >= num2);
  bool less_equal = (num1 <= num2);

  // Testiranje operatora ==, !=, >, <, >=, <= sa konstantnim vrednostima
  equal = (num1 == 123);
  not_equal = (num2 != -456);
  greater = (num1 > -100);
  less = (num2 < 500);
  greater_equal = (num1 >= 50);
  less_equal = (num2 <= -500);

  // Testiranje stepenovanja
  Number power = num1 ^ short(2);

  // Testiranje operatora bool()
  if (num1)
    std::cout << "num1 je validan broj." << std::endl;
  else
    std::cout << "num1 nije validan broj." << std::endl;

  // Testiranje prefiksnog i postfiksnog inkrementa i dekrementa
  Number post_inc = num1++;
  Number pre_inc = ++num2;
  Number post_dec = num1--;
  Number pre_dec = --num2;

  // Ispis rezultata
  std::cout << "Suma: " << sum << std::endl;
  std::cout << "Razlika: " << diff << std::endl;
  std::cout << "Jednaki: " << equal << std::endl;
  std::cout << "Nisu jednaki: " << not_equal << std::endl;
  std::cout << "Veći: " << greater << std::endl;
  std::cout << "Manji: " << less << std::endl;
  std::cout << "Veći ili jednak: " << greater_equal << std::endl;
  std::cout << "Manji ili jednak: " << less_equal << std::endl;
  std::cout << "Stepenovanje: " << power << std::endl;
  std::cout << "Postfiksni inkrement: " << post_inc << std::endl;
  std::cout << "Prefiksni inkrement: " << pre_inc << std::endl;
  std::cout << "Postfiksni dekrement: " << post_dec << std::endl;
  std::cout << "Prefiksni dekrement: " << pre_dec << std::endl;

  return 0;
}
