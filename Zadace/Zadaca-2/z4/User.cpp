#include "User.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

size_t User::ID_counter_ = 0;

User::User(const std::string& name, const std::string& last_name)
  : ID_ { ++ID_counter_ },
    name_ { std::move(name) },
    last_name_ { std::move(last_name) },
    lent_book_ { nullptr } { }

User::User(User&& other)
  : ID_ { other.ID_ },
    name_ { std::move(other.name_) },
    last_name_ { std::move(other.last_name_) },
    lent_book_ { other.lent_book_ }
{
  other.ID_ = 0;
  other.lent_book_ = nullptr;
}

User::User(const User& other)
  : ID_ { other.ID_ },
    name_ { other.name_ },
    last_name_ { other.last_name_ },
    lent_book_ { other.lent_book_ } { }

User& User::operator=(User&& other)
{
  this->ID_ = other.ID_;
  this->name_ = std::move(other.name_);
  this->last_name_ = std::move(other.last_name_);
  this->lent_book_ = other.lent_book_;

  other.ID_ = 0;
  other.lent_book_ = nullptr;

  return *this;
}

User& User::operator=(const User& other)
{
  this->ID_ = other.ID_;
  this->name_ = other.name_;
  this->last_name_ = other.last_name_;
  this->lent_book_ = other.lent_book_;

  return *this;
}

bool User::operator==(const User& other) const
{
  return this->ID_ == other.ID_;
}

bool User::operator!=(const User& other) const
{
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const User& user)
{
  out << "ID:\t\t\t" << user.ID_ << std::endl
      << "Ime:\t\t\t" << user.name_ << std::endl
      << "Prezime:\t\t" << user.last_name_ << std::endl
      << "Posudjena knjiga:";

  if (user.lent_book_ != nullptr)
  {
    out << std::endl;
    out << std::string(50, '-') << std::endl;
    out << *user.lent_book_;
    out << std::string(50, '-') << std::endl;
  }
  else
    out << "\tnema" << std::endl;

  return out;
}
