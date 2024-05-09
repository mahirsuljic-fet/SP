#include "annotated.hpp"

#include <iostream>
#include <string>

class Customer
{
    AnnotatedString firstname;
    AnnotatedString lastname;

  public:
    // Customer(const AnnotatedString& ime, const AnnotatedString& prezime)
    //   : firstname { ime }, lastname { prezime } { }
    //
    // Customer(AnnotatedString&& ime, AnnotatedString&& prezime)
    //   : firstname { std::move(ime) }, lastname { std::move(prezime) } { }

    template <typename F, typename G>
    Customer(F&& ime, G&& prezime)
      : firstname { std::forward<F>(ime) }, lastname { std::forward<G>(prezime) } { }
};

int main()
{
  AnnotatedString ime { "Harun" };
  AnnotatedString prezime { "Delic" };

  Customer customer1(ime, prezime);
  Customer customer2(std::move(ime), std::move(prezime));
  Customer customer3(ime, std::move(prezime));
  Customer customer4(std::move(ime), prezime);

  return 0;
}
