#include "Book.hpp"
#include "Library.hpp"
#include "User.hpp"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#define MAX_OPTION 6
#define MAX_SEARCH_OPTION 4

static Library library;

int menu_option();
void print_menu();
void handle_option(int);

int search_menu_option();
void print_search_menu();
void handle_search_option(int);

void dialogue_add_book();
void dialogue_add_user();
void dialogue_lend_book();
void dialogue_return_book();
void dialogue_search_book();
void dialogue_search_books_by_title();
void dialogue_search_books_by_author();
void dialogue_search_books_by_publisher();
void dialogue_search_books_by_release_year();
void dialogue_print_users();

void cin_reset();

int main()
{
  int option = -1;

  while (option)
  {
    option = menu_option();
    handle_option(option);
  }

  return 0;
}

void print_menu()
{
  std::cout << "BIBLIOTEKA" << std::endl
            << std::endl
            << "1 - Unos knjige" << std::endl
            << "2 - Posudjivanje knjige" << std::endl
            << "3 - Vracanje knjige" << std::endl
            << "4 - Pretraga knjiga" << std::endl
            << "5 - Unos korisnika" << std::endl
            << "6 - Ispis korisnika" << std::endl
            << "0 - Izlaz" << std::endl
            << std::endl
            << "Izbor: ";
}

int menu_option()
{
  unsigned int option = 0;

  do
  {
    print_menu();
    std::cin >> option;
    system("clear");

    if (option > MAX_OPTION)
      std::cout << "Izbor nije validan!\n\n";
  }
  while (option > MAX_OPTION);

  return option;
}

void handle_option(int option)
{
  switch (option)
  {
  case 1:
    dialogue_add_book();
    break;
  case 2:
    dialogue_lend_book();
    break;
  case 3:
    dialogue_return_book();
    break;
  case 4:
    dialogue_search_book();
    break;
  case 5:
    dialogue_add_user();
    break;
  case 6:
    dialogue_print_users();
    break;
  case 0:
  default:
    return;
  }
}

void dialogue_add_book()
{
  std::string title;
  std::string author;
  std::string publisher;
  size_t release_year;
  size_t copies;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "UNOS KNJIGE" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite naslov knjige: ";
      if (!(std::cin >> title)) throw std::invalid_argument("Unos naslova nije validan!");

      std::cout << "Unesite autora knjige: ";
      if (!(std::cin >> author)) throw std::invalid_argument("Unos autora nije validan!");

      std::cout << "Unesite izdavaca knjige: ";
      if (!(std::cin >> publisher)) throw std::invalid_argument("Unos izdavaca nije validan!");

      std::cout << "Unesite godinu izdavanja knjige: ";
      if (!(std::cin >> release_year)) throw std::invalid_argument("Unos godine izdavanja nije validan!");

      std::cout << "Unesite broj kopija knjige: ";
      if (!(std::cin >> copies)) throw std::invalid_argument("Unos broja kopija nije validan!");

      library.add_book(Book { title, author, publisher, release_year, copies });

      system("clear");
      std::cout << "Knjiga uspjesno unesena!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_add_user()
{
  std::string name;
  std::string last_name;
  size_t ID;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "UNOS KORISNIKA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite ime korisnika: ";
      if (!(std::cin >> name)) throw std::invalid_argument("Unos imena nije validan!");

      std::cout << "Unesite prezime korisnika: ";
      if (!(std::cin >> last_name)) throw std::invalid_argument("Unos prezimena nije validan!");

      library.add_user(User { name, last_name });

      system("clear");
      std::cout << "Korisnik uspjesno unesen!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_lend_book()
{
  std::string title;
  std::string author;
  std::string publisher;
  size_t release_year;
  size_t ID;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "POSUDJIVANJE KNJIGE" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite ID korisnika: ";
      if (!(std::cin >> ID)) throw std::invalid_argument("Unos ID nije validan!");

      if (!library.user_exists(ID)) throw std::invalid_argument("Korisnik ne postoji!");
      const User& user = library.get_user(ID);
      if (user.has_book()) throw std::invalid_argument("Korisnik je vec posudio neku knjigu!");

      std::cout << "Unesite naslov knjige: ";
      if (!(std::cin >> title)) throw std::invalid_argument("Unos naslova nije validan!");

      std::cout << "Unesite autora knjige: ";
      if (!(std::cin >> author)) throw std::invalid_argument("Unos autora nije validan!");

      std::cout << "Unesite izdavaca knjige: ";
      if (!(std::cin >> publisher)) throw std::invalid_argument("Unos izdavaca nije validan!");

      std::cout << "Unesite godinu izdavanja knjige: ";
      if (!(std::cin >> release_year)) throw std::invalid_argument("Unos godine izdavanja nije validan!");

      Book temp { title, author, publisher, release_year, 0 };
      if (!library.book_exists(temp)) throw std::invalid_argument("Knjiga ne postoji!");
      const Book& book = library.get_book(temp);

      library.lend_book(book, user.ID());

      system("clear");
      std::cout << "Knjiga uspjesno posudjena!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_return_book()
{
  std::string title;
  std::string author;
  std::string publisher;
  size_t release_year;
  size_t ID;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "VRACANJE KNJIGE" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite ID korisnika: ";
      if (!(std::cin >> ID)) throw std::invalid_argument("Unos ID nije validan!");

      if (!library.user_exists(ID)) throw std::invalid_argument("Korisnik ne postoji!");
      const User& user = library.get_user(ID);
      if (!user.has_book()) throw std::invalid_argument("Korisnik nema posudjenih knjiga!");

      std::cout << "Unesite naslov knjige: ";
      if (!(std::cin >> title)) throw std::invalid_argument("Unos naslova nije validan!");

      std::cout << "Unesite autora knjige: ";
      if (!(std::cin >> author)) throw std::invalid_argument("Unos autora nije validan!");

      std::cout << "Unesite izdavaca knjige: ";
      if (!(std::cin >> publisher)) throw std::invalid_argument("Unos izdavaca nije validan!");

      std::cout << "Unesite godinu izdavanja knjige: ";
      if (!(std::cin >> release_year)) throw std::invalid_argument("Unos godine izdavanja nije validan!");

      Book temp { title, author, publisher, release_year, 0 };
      if (!library.book_exists(temp)) throw std::invalid_argument("Knjiga ne postoji!");
      const Book& book = library.get_book(temp);

      library.return_book(book, user.ID());

      system("clear");
      std::cout << "Knjiga uspjesno vracena!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_search_book()
{
  unsigned int option = -1;

  system("clear");
  std::cout << "PRETRAGA KNJIGA" << std::endl;
  std::cout << std::endl;

  while (option)
  {
    option = search_menu_option();
    handle_search_option(option);
  }

  system("clear");
}

void print_search_menu()
{
  std::cout << "1 - Pretraga po naslovu" << std::endl
            << "2 - Pretraga po autoru" << std::endl
            << "3 - Pretraga po izdavacu" << std::endl
            << "4 - Pretraga po godini izdavanja" << std::endl
            << "0 - nazad" << std::endl
            << "Izbor: ";
}

int search_menu_option()
{
  unsigned int option = 0;

  do
  {
    print_search_menu();
    std::cin >> option;
    system("clear");

    if (option > MAX_SEARCH_OPTION)
      std::cout << "Izbor nije validan!\n\n";
  }
  while (option > MAX_SEARCH_OPTION);

  return option;
}

void handle_search_option(int option)
{
  switch (option)
  {
  case 1:
    dialogue_search_books_by_title();
    break;
  case 2:
    dialogue_search_books_by_author();
    break;
  case 3:
    dialogue_search_books_by_publisher();
    break;
  case 4:
    dialogue_search_books_by_release_year();
    break;
  case 0:
  default:
    return;
  }
}

void dialogue_search_books_by_title()
{
  std::string title;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "PRETRAGA KNJIGA PO NASLOVU" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite naslov knjige: ";
      if (!(std::cin >> title)) throw std::invalid_argument("Unos naslova nije validan!");

      library.print_books_by_title(title);

      std::cout << std::endl;
      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_search_books_by_author()
{
  std::string author;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "PRETRAGA KNJIGA PO AUTORU" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite autora: ";
      if (!(std::cin >> author)) throw std::invalid_argument("Unos autora nije validan!");

      library.print_books_by_author(author);

      std::cout << std::endl;
      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_search_books_by_publisher()
{
  std::string publisher;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "PRETRAGA KNJIGA PO IZDAVACU" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite izdavaca: ";
      if (!(std::cin >> publisher)) throw std::invalid_argument("Unos izdavaca nije validan!");

      library.print_books_by_publisher(publisher);

      std::cout << std::endl;
      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_search_books_by_release_year()
{
  size_t release_year;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "PRETRAGA KNJIGA PO GODINI IZDAVANJA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite godinu izdavanja: ";
      if (!(std::cin >> release_year)) throw std::invalid_argument("Unos godine izdavanja nije validan!");

      library.print_books_by_release_year(release_year);

      std::cout << std::endl;
      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_print_users()
{
  system("clear");
  std::cout << "ISPIS KORISNIKA" << std::endl;
  std::cout << std::endl;
  library.print_users();
  std::cout << std::endl;
  std::cout << "Pritisnite bilo koju tipku za nastavak... ";
  cin_reset();
  std::cin.get();
  system("clear");
  return;
}

void cin_reset()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
