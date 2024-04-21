#pragma once

#include <cstddef>
#include <ostream>
#include <string>

class Book
{
  public:
    Book() = default;
    Book(const std::string&, const std::string&, const std::string&, size_t, size_t);
    Book(Book&&);
    Book(const Book&);
    Book& operator=(Book&&);
    Book& operator=(const Book&);
    ~Book() = default;

    bool operator==(const Book&) const;
    bool operator!=(const Book&) const;

    size_t copies() const { return copies_; }

    friend class Library;
    friend std::ostream& operator<<(std::ostream&, const Book&);

  private:
    std::string title_;
    std::string author_;
    std::string publisher_;
    size_t release_year_ = 0;
    size_t copies_ = 0;
};
