#pragma once

#include <iostream>
#include <string>

class AnnotatedString
{
  public:
    std::string value;
    int id;

    AnnotatedString() : id { objectCounter() }
    {
      std::cout << "default ctor (id: " << id << ")" << std::endl;
    }

    AnnotatedString(const char* s) : value { s }, id { objectCounter() }
    {
      std::cout << "value ctor (id: " << id << ")" << std::endl;
    }

    AnnotatedString(std::string s) : value { std::move(s) }, id { objectCounter() }
    {
      std::cout << "value ctor (id: " << id << ")" << std::endl;
    }

    AnnotatedString(const AnnotatedString& as)
      : value { as.value }, id { objectCounter() }
    {
      std::cout << "copy ctor (id: " << id << ")" << std::endl;
    }

    AnnotatedString(AnnotatedString&& as)
      : value { std::move(as.value) }, id { objectCounter() }
    {
      std::cout << "move ctor (id: " << id << ")" << std::endl;
    }

    AnnotatedString& operator=(const AnnotatedString& as)
    {
      value = as.value;
      std::cout << "copy =" << std::endl;
      return *this;
    }
    AnnotatedString& operator=(AnnotatedString&& as)
    {
      value = std::move(as.value);
      std::cout << "move =" << std::endl;
      return *this;
    }
    ~AnnotatedString()
    {
      std::cout << "~dtor (id: " << id << ")" << std::endl;
    }

  private:
    static int objectCounter()
    {
      static int counter = 0;
      return counter++;
    }
};
