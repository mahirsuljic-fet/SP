#pragma once

#include "Book.hpp"
#include <cstddef>
#include <string>

class User
{
  public:
    User() = default;
    User(const std::string&, const std::string&);
    User(User&&);
    User(const User&);
    User& operator=(User&&);
    User& operator=(const User&);
    ~User() = default;

    bool operator==(const User&) const;
    bool operator!=(const User&) const;

    bool has_book() const { return lent_book_ != nullptr; }

    size_t ID() const { return ID_; }
    std::string name() const { return name_; }
    std::string last_name() const { return last_name_; }

    friend class Library;
    friend std::ostream& operator<<(std::ostream&, const User&);

  private:
    std::string name_;
    std::string last_name_;
    size_t ID_ = 0;
    Book* lent_book_ = nullptr;
    static size_t ID_counter_;
};
