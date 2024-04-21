#include "Library.hpp"
#include "User.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

void Library::add_user(const User& user)
{
  users_.push_back(user);
}

void Library::add_user(User&& user)
{
  users_.push_back(std::move(user));
}

void Library::add_book(const Book& book)
{
  books_.push_back(book);
}

void Library::add_book(Book&& book)
{
  books_.push_back(std::move(book));
}

void Library::lend_book(const Book& book, size_t ID)
{
  auto book_it = find_book_(book);
  auto user_it = find_user_(ID);
  if (book_it->copies_ == 0) throw std::invalid_argument("U biblioteci nema kopije navedene knjige");

  user_it->lent_book_ = &(*book_it);
  --book_it->copies_;
}

void Library::return_book(const Book& book, size_t ID)
{
  auto book_it = find_book_(book);
  auto user_it = find_user_(ID);

  if (user_it->lent_book_ != &(*book_it)) throw std::invalid_argument("Korisnik nema unesenu knjigu");

  user_it->lent_book_ = nullptr;
  ++book_it->copies_;
}

void Library::print_books_by_title(const std::string& title) const
{
  bool exists = false;
  for (const auto& book : books_)
  {
    if (book.title_ == title)
    {
      std::cout << book << std::endl;
      exists = true;
    }
  }

  if (!exists) std::cout << "U biblioteci ne postoji knjiga sa naslobom \"" << title << "\"" << std::endl;
}

void Library::print_books_by_author(const std::string& author) const
{
  bool exists = false;
  for (const auto& book : books_)
  {
    if (book.author_ == author)
    {
      std::cout << book << std::endl;
      exists = true;
    }
  }

  if (!exists) std::cout << "U biblioteci ne postoji knjiga od autora \"" << author << "\"" << std::endl;
}

void Library::print_books_by_publisher(const std::string& publisher) const
{
  bool exists = false;
  for (const auto& book : books_)
  {
    if (book.publisher_ == publisher)
    {
      std::cout << book << std::endl;
      exists = true;
    }
  }

  if (!exists) std::cout << "U biblioteci ne postoji knjiga od izdavaca \"" << publisher << "\"" << std::endl;
}

void Library::print_books_by_release_year(size_t release_year) const
{
  bool exists = false;
  for (const auto& book : books_)
  {
    if (book.release_year_ == release_year)
    {
      std::cout << book << std::endl;
      exists = true;
    }
  }

  if (!exists) std::cout << "U biblioteci ne postoji knjiga izdana " << release_year << " godine" << std::endl;
}

void Library::print_users() const
{
  if (users_.empty())
  {
    std::cout << "Nema unesenih korisnika!" << std::endl;
    return;
  }

  for (const auto& user : users_)
    std::cout << user << std::endl;
}

bool Library::book_exists(const Book& book) const
{
  for (const auto& b : books_)
    if (b == book) return true;
  return false;
}

bool Library::user_exists(const std::string& name, const std::string& last_name) const
{
  for (const auto& u : users_)
    if (u.name_ == name && u.last_name_ == last_name) return true;
  return false;
}

bool Library::user_exists(size_t ID) const
{
  for (const auto& u : users_)
    if (u.ID_ == ID) return true;
  return false;
}

Books::Iterator Library::find_book_(const Book& book)
{
  auto predicate = [&book](const Book& other) { return book == other; };
  return std::find_if(books_.begin(), books_.end(), predicate);
}

Books::Iterator Library::find_book_(const std::string& title)
{
  auto predicate = [&title](const Book& other) { return title == other.title_; };
  return std::find_if(books_.begin(), books_.end(), predicate);
}

Users::Iterator Library::find_user_(size_t ID)
{
  auto predicate = [&ID](const User& other) { return other.ID_ == ID; };
  return std::find_if(users_.begin(), users_.end(), predicate);
}

Users::Iterator Library::find_user_(const std::string& name, const std::string& last_name)
{
  auto predicate = [&name, &last_name](const User& other) { return other.name_ == name && other.last_name_ == last_name; };
  return std::find_if(users_.begin(), users_.end(), predicate);
}

const Book& Library::get_book(const Book& book)
{
  return *find_book_(book);
}

const Book& Library::get_book(const std::string& title, const std::string& author, const std::string& publisher, size_t release_year)
{
  return *find_book_(Book { title, author, publisher, release_year, 0 });
}

const User& Library::get_user(const std::string& name, const std::string& last_name)
{
  return *find_user_(name, last_name);
}

const User& Library::get_user(size_t ID)
{
  return *find_user_(ID);
}
