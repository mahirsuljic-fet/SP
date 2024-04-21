#pragma once

#include "../z1/MojVektor.hpp"
#include "Book.hpp"
#include "User.hpp"
#include <cstddef>
#include <string>

using Books = MojVektor<Book>;
using Users = MojVektor<User>;

class Library
{
  public:
    Library() = default;
    Library(Library&&) = delete;
    Library(const Library&) = delete;
    Library& operator=(Library&&) = delete;
    Library& operator=(const Library&) = delete;
    ~Library() = default;

    void add_user(const User&);
    void add_user(User&&);
    void add_book(const Book&);
    void add_book(Book&&);
    void lend_book(const Book&, size_t ID);
    void return_book(const Book&, size_t ID);
    void print_books_by_title(const std::string&) const;
    void print_books_by_author(const std::string&) const;
    void print_books_by_publisher(const std::string&) const;
    void print_books_by_release_year(size_t) const;
    void print_users() const;

    bool book_exists(const Book&) const;
    bool user_exists(const std::string& name, const std::string& last_name) const;
    bool user_exists(size_t ID) const;
    const Book& get_book(const Book&);
    const Book& get_book(const std::string& title, const std::string& author, const std::string& publisher, size_t release_year);
    const User& get_user(const std::string& name, const std::string& last_name);
    const User& get_user(size_t ID);

  private:
    Books books_;
    Users users_;
    Books::Iterator find_book_(const Book&);
    Books::Iterator find_book_(const std::string& title);
    Users::Iterator find_user_(size_t ID);
    Users::Iterator find_user_(const std::string& name, const std::string& last_name);
};
