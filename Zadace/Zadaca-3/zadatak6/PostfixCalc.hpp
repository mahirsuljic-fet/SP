#pragma once

#include <stack>
#include <string>

class PostfixCalc
{
  public:
    PostfixCalc() = default;
    PostfixCalc(PostfixCalc&&) = delete;
    PostfixCalc(const PostfixCalc&) = delete;
    PostfixCalc& operator=(PostfixCalc&&) = delete;
    PostfixCalc& operator=(const PostfixCalc&) = delete;
    ~PostfixCalc() = default;

    int eval(const std::string&);

  private:
    std::stack<int> values_;
    void add();
    void sub();
    void mul();
    void div();

    std::string trim(const std::string&);
};
