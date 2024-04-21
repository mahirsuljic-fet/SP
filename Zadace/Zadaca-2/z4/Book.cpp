#include "Book.hpp"
#include <algorithm>

Book::Book(const std::string& title, const std::string& author, const std::string& publisher, size_t release_year, size_t copies)
  : title_ { std::move(title) },
    author_ { std::move(author) },
    publisher_ { std::move(publisher) },
    release_year_ { release_year },
    copies_ { copies } { }

Book::Book(Book&& other)
  : title_ { std::move(other.title_) },
    author_ { std::move(other.author_) },
    publisher_ { std::move(other.publisher_) },
    release_year_ { other.release_year_ },
    copies_ { other.copies_ }
{
  other.release_year_ = 0;
  other.copies_ = 0;
}

Book::Book(const Book& other)
  : title_ { other.title_ },
    author_ { other.author_ },
    publisher_ { other.publisher_ },
    release_year_ { other.release_year_ },
    copies_ { other.copies_ } { }

Book& Book::operator=(Book&& other)
{
  this->title_ = std::move(other.title_);
  this->author_ = std::move(other.author_);
  this->publisher_ = std::move(other.publisher_);
  this->release_year_ = other.release_year_;
  this->copies_ = other.copies_;

  other.release_year_ = 0;
  other.copies_ = 0;

  return *this;
}

Book& Book::operator=(const Book& other)
{
  this->title_ = other.title_;
  this->author_ = other.author_;
  this->publisher_ = other.publisher_;
  this->release_year_ = other.release_year_;
  this->copies_ = other.copies_;

  return *this;
}

bool Book::operator==(const Book& other) const
{
  return this->title_ == other.title_
    && this->author_ == other.author_
    && this->publisher_ == other.publisher_
    && this->release_year_ == other.release_year_;
}

bool Book::operator!=(const Book& other) const
{
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Book& book)
{
  return out << "Naslov:\t\t\t" << book.title_ << std::endl
             << "Autor:\t\t\t" << book.author_ << std::endl
             << "Izdavac:\t\t" << book.publisher_ << std::endl
             << "Godina izdavanja:\t" << book.release_year_ << std::endl
             << "Broj primjeraka:\t" << book.copies_ << std::endl;
}
